#pragma once

#include <string>
#include <list>

using namespace std;

class Entity
{

public:
	Entity(int shipNumber, int size);
	virtual ~Entity();

	int shipNumber;
	int size;

};

