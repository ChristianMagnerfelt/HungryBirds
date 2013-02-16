
#include <pthread.h>
#include <semaphore.h>

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

const std::size_t g_maxBabybirds = 100;

std::size_t g_numBabyBirds;

int main(int argc, const char * argv[])
{
	
	// Read and store arguments
	if(argc > 1)
	{
		std::vector<std::string> args(argv, argv + argc);
	
		std::istringstream ss (args[1]);
		ss >> g_numBabyBirds;
		if(ss.fail())
			g_numBabyBirds = g_maxBabybirds;
		std::cout << "Number of birds : " << g_numBabyBirds << std::endl;
	}










	return 0;
}
