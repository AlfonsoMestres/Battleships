#include <iostream>
#include <string>
#include <array>
#include <random>
#include <cctype>
#include <algorithm>
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

///c++ 11 check if its a number style
bool is_number(const std::string& s) {
	return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

///This also checks if the variable is a number
int inputNumberBetween(std::string prompt, int min, int max) {
	int guess = -1;

	do {
		std::cout << prompt;
		std::cin >> guess;
		if (std::cin.fail()) {
			guess = -1;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Not a number" << std::endl;
		} else if (guess < min || guess > max) {
			guess = -1;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Out of Range" << std::endl;
		}
	} while (guess == -1);

	return guess;
}

///Effectively compare two strings
bool Same(const std::string& a, const std::string& b)
{
	return _stricmp(a.c_str(), b.c_str()) == 0;
}

std::string ToLowerCase(std::string strToConvert)
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::tolower);
	return strToConvert;
}

///Split a string into words so we can manage them
std::vector<std::string> ParseAction(std::string args)
{
	int len = args.length();
	std::vector<std::string> subArray;

	for (int j = 0, k = 0; j < len; j++) {
		if (args[j] == ' ') {
			std::string ch = args.substr(k, j - k);
			k = j + 1;
			subArray.push_back(ch);
		}
		if (j == len - 1) {
			std::string ch = args.substr(k, j - k + 1);
			subArray.push_back(ch);
		}
	}

	return subArray;
}