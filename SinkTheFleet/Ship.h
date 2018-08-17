#pragma once

#include <string>
#include <list>

using namespace std;

class Ship
{

public:
	Ship(char shipLetter, int size);
	virtual ~Ship();

	char shipLetter;
	int size;

};

