#include <array>
#include <random>
#include "Helpers.h"

///c++ 11 Randomizer style
int RandomizeBetween(int min, int max) {
	//the random device that will seed the generator
	std::random_device seeder;
	//then make a mersenne twister engine
	std::mt19937 engine(seeder());
	//then the easy part... the distribution
	std::uniform_int_distribution<int> dist(min, max);
	//then just generate the integer like this:
	return dist(engine);
}
