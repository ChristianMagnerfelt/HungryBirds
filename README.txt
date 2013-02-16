The hungry birds problem
------------------------

	Description	: 
	Parent bird and all baby birds are simulated as separate worker 
	threads using pthreads. Syncronization is handled by using semaphores.
	All baby birds eat from dish until the dish of worms is empty. When the dish is empty the parent bird gets a new dish of worms;
 
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
		
	Fairness of program :
		
