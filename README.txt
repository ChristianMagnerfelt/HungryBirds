The hungry birds problem
------------------------

	Description	: 
	Given are n baby birds and one parent bird. The baby birds eat out of a common dish that 
	initially contains W worms. Each baby bird repeatedly takes a worm, eats it, sleeps for a while, 
	takes another worm, and so on. If the dish is empty, the baby bird who discovers the empty dish chirps 
	real loud to awaken the parent bird. The parent bird flies off and gathers W more worms, puts them in the dish, 
	and then waits for the dish to be empty again. This pattern repeats forever.
	Syncronization is handled by semaphores and bear and honeybees are simulated with worker threads using the 
	pthread library.

 	Author : 
 	Christian Magnerfelt

	Email :
	magnerf@kth.se
	
	Usage :
		./HungryBirds	{number of baby birds} {number of worms}
	
	Compiler:
		requires gcc 4.4.7
	
	Build :
		make debug
		make release
		
