debug: hungry_birds.cpp
	g++ -g -Wall -Wextra -O0 -o HungryBirds hungry_birds.cpp -lpthread
	
release: hungry_birds.cpp
	g++ -Wall -Wextra -O3 -o HungryBirds hungry_birds.cpp -lpthread
clean:
	rm Hungrybirds
