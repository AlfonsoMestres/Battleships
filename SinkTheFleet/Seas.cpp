#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Entity.h"
#include "Seas.h"


Seas::Seas()
{
}


Seas::~Seas()
{
}

void Seas::LoadShips() {
	vector<Entity*> ships;
	Entity* ship1 = new Entity(2, 2);
	Entity* ship2 = new Entity(3, 3);
	Entity* ship3 = new Entity(4, 4);
	Entity* ship4 = new Entity(5, 5);
	ships.push_back(ship1);
	ships.push_back(ship2);
	ships.push_back(ship3);
	ships.push_back(ship4);

	cout << "Iterations to find a spot -------------------" << endl;

	for (std::vector<Entity*>::iterator it = ships.begin(); it != ships.end(); ++it)
		LoadShip((Entity*)*it, 0);

	cout << "The ships have been placed" << endl;
}