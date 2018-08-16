#pragma once

#include <string>
#include <list>

using namespace std;

class Ship
{

public:
	Ship(int shipNumber, int size);
	virtual ~Ship();

	int shipNumber;
	int size;

};

