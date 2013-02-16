/*!
 *	\brief			A simulator of the 'The hungry birds problem'
 *	\description	Parent bird and all baby birds are simulated as separate worker threads using pthreads. Syncronization is handled by using semaphores.
 *					All baby birds eat from dish until the dish of worms is empty. When the dish is empty the parent bird gets a new dish of worms;
 *	\author			Christian Magnerfelt
 *	\email			magnerf@kth.se
 */
#include <cstdlib>

#include <pthread.h>
#include <semaphore.h>

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

const bool IS_SHARED = 1;
const std::size_t MAX_BABY_BIRDS = 100;
const std::size_t MAX_WORMS = 100;
const std::size_t BABY_BIRD_SLEEP_TIME = 20;

std::size_t g_numBabyBirds;
std::size_t g_numWorms;

sem_t full;			// Semaphore counter for number of worms in dish
sem_t empty;		// Semaphore flag if dish is empty

void * babyBird(void * param);
void * parentBird(void * param);

std::vector<int> g_dish;
sem_t mutex;

/*
 *	\params	argv	{ program name } { number of baby birds } { number of worms }
 */
int main(int argc, const char * argv[])
{
	
	// Read and store arguments
	g_numBabyBirds = MAX_BABY_BIRDS;
	g_numWorms = MAX_WORMS;
	if(argc > 1)
	{
		// Store arguments in a vector
		std::vector<std::string> args(argv, argv + argc);
	
		std::istringstream ss (args[1]);
		ss >> g_numBabyBirds;
		if(ss.fail())
			g_numBabyBirds = MAX_BABY_BIRDS; // If input fails set to max
			
		if(argc > 2)
		{
			std::istringstream ss (args[2]);
			ss >> g_numWorms;
			if(ss.fail())
				g_numWorms = MAX_WORMS;	// If input fails set to max
		}
			
		std::cout << "Number of birds : " << g_numBabyBirds << std::endl;
		std::cout << "Number of worms : " << g_numWorms << std::endl;
	}
	
	// Initialize threads attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	
	// Initialize semaphores
	sem_init(&full, IS_SHARED, g_numWorms + 1);
	sem_init(&empty, IS_SHARED, 0);
	sem_init(&mutex, IS_SHARED, 1);
	
	// Fills dish with worms
	for(std::size_t i = 0; i < g_numWorms; ++i)
	{
		g_dish.push_back(rand() % 10);	// symbolic random integer for each worm
	}
	
	// Init workers
	std::vector<pthread_t> workers(g_numBabyBirds + 1);
	
	// Create parent bird worker thread
	pthread_create(&workers[0], &attr, parentBird, reinterpret_cast<void*>(0));
	
	// Create baby bird worker threads
	for(std::size_t i = 1; i < workers.size(); ++i)
	{
		pthread_create(&workers[i], &attr, babyBird, reinterpret_cast<void*>(i));
	}
	
	// join all workers
	for(std::size_t i = 0; i < workers.size(); ++i)
	{
		pthread_join(workers[i], NULL);
	}
	return 0;
}
/*
 *	\brief	Fills dish with worms
 */
void * parentBird(void * param)
{
	std::size_t id = reinterpret_cast<std::size_t>(param);
	while(true)
	{
		// Sleep until dish is empty
		sem_wait(&empty);
		
		// Mutal exclusion on shared resource dish
		sem_wait(&mutex);
		for(std::size_t i = 0; i < g_numWorms; ++i)
		{
			g_dish.push_back(rand() % 10);
		}
		std::cout << "Parent " << id << " : Fetched " << g_numWorms << " worms" << std::endl; 	
		sem_post(&mutex);
		
		// Signal baby birds that dish is ready
		for(std::size_t i = 0; i < g_numWorms + 1; ++i)
		{
			sem_post(&full);
		}
	}
	return 0;
}
/*
 *	\brief	Eats worms from dish
 */
void * babyBird(void * param)
{
	std::size_t id = reinterpret_cast<std::size_t>(param);
	while(true)	
	{
		// Wait until dish have at least 1 worm
		sem_wait(&full);
		
		// Mutal exclusion on shared resource dish
		sem_wait(&mutex);
		if(g_dish.size() == 0)
		{
			std::cout << "BabyBird " << id << " : Give me more food!!!" << std::endl;		
			sem_post(&empty);	// Signal parent
		}
		else
		{
			std::cout << "BabyBird " << id << " : Ate worm from dish" << std::endl;
			g_dish.pop_back();	// Eat from dish
		}
		sem_post(&mutex);
		
		sleep(rand() % BABY_BIRD_SLEEP_TIME);	
	}
	return 0;
}
