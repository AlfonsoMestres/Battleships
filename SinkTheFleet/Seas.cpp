#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Entity.h"
#include "Helpers.h"
#include "Seas.h"

Seas::Seas()
{
}

Seas::~Seas()
{
}

void Seas::LoadShip(Entity* ship, int loops) {
	int x = RandomizeBetween(0, 9);
	int y = RandomizeBetween(0, 9);
	int direct = RandomizeBetween(0, 3);
	loops = loops + 1;

	switch (direct) {
		//Second phase probably could be storing the non-possible locations for the ships to increase the efficiency
	case 0: //N
		if (y - ship->size >= 0) { //inbounds?
			for (int i = 0; i < ship->size; i++) {
				if (sea[x][y - i] != 0) { //Is the sea occupied by a ship?
					LoadShip(ship, loops); //reiterate
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x][y - j] = ship->shipNumber; //update sea with ship
			}
			cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	case 1: //S
		if (y + ship->size <= 9) {
			for (int i = 0; i < ship->size; i++) {
				if (sea[x][y + i] != 0) {
					LoadShip(ship, loops);
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x][y + j] = ship->shipNumber;
			}
			cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	case 2: //E
		if (x + ship->size <= 9) {
			for (int i = 0; i < ship->size; i++) {
				if (sea[x + i][y] != 0) {
					LoadShip(ship, loops);
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x + j][y] = ship->shipNumber;
			}
			cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	case 3: //W
		if (x - ship->size >= 0) {
			for (int i = 0; i < ship->size; i++) {
				if (sea[x - i][y] != 0) {
					LoadShip(ship, loops);
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x - j][y] = ship->shipNumber;
			}
			cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	default:
		//error?
		break;
	}
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

void Seas::SeaStatus() {
	int rows = sizeof(sea) / sizeof(sea[0]);
	int cols = sizeof(sea[0]) / sizeof(sea[0][0]);

	string rowOut;

	for (int j = 0; j < cols; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			cout << sea[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Seas::ClearSea() {
	memset(sea, 0, sizeof(sea));
}
