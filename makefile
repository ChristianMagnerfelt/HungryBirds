debug: hungry_birds.cpp
	g++ -g -Wall -Wextra -O0 -o HungryBirds hungry_birds.cpp -lpthread -std=c++0x
	
release: hungry_birds.cpp
	g++ -Wall -Wextra -O3 -o HungryBirds hungry_birds.cpp -lpthread -std=c++0x
clean:
	rm HungryBirds
