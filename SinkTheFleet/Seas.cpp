#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Ship.h"
#include "Helpers.h"
#include "Seas.h"

Seas::Seas()
{
}

Seas::~Seas()
{
}

void Seas::LoadShip(Ship* ship, int loops) {
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
			std::cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
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
			std::cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
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
			std::cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
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
			std::cout << "Ship " << ship->shipNumber << " iterated " << loops << " times" << endl;
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

bool Seas::LoadShips(int mode) {
	vector<Ship*> ships;
	Ship* ship1;
	Ship* ship2;
	Ship* ship3;
	Ship* ship4;

	switch (mode) {
	case 0: //EASY
		ship1 = new Ship(2, 4);
		ship2 = new Ship(3, 4);
		ship3 = new Ship(4, 5);
		ship4 = new Ship(5, 6);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	case 1: //NORMAL
		ship1 = new Ship(2, 2);
		ship2 = new Ship(3, 3);
		ship3 = new Ship(4, 4);
		ship4 = new Ship(5, 5);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	case 2: //HARD
		ship1 = new Ship(2, 2);
		ship2 = new Ship(3, 2);
		ship3 = new Ship(4, 3);
		ship4 = new Ship(5, 4);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	case 42: //Meaning of life
		std::cout << "Prove worthy of this option" << endl;
		ship1 = new Ship(1, 1);
		ship2 = new Ship(2, 1);
		ship3 = new Ship(3, 1);
		ship4 = new Ship(4, 1);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	default: //NOPE
		std::cout << "Not an option" << endl;
		return false;//Is this ok?
	}

	//Debug info
	std::cout << "Iterations to find a spot -------------------" << endl;

	for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
		LoadShip((Ship*)*it, 0);

	std::cout << "The ships have been placed" << endl;
	return true;
}

void Seas::SeaStatus() {
	int rows = sizeof(playerSea) / sizeof(playerSea[0]);
	int cols = sizeof(playerSea[0]) / sizeof(playerSea[0][0]);

	string rowOut;
	cout << "----CURRENT SEA---- " << endl;
	std::cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	for (int j = 0; j < cols; j++)
	{
		std::cout << j << " ";
		for (int i = 0; i < rows; i++)
		{
			std::cout << playerSea[i][j] << " ";
		}
		std::cout << endl;
	}
	std::cout << endl;
}

void Seas::ClearSea() {
	memset(sea, 0, sizeof(sea));
}

void Seas::UpdatePlayerSea(int col, int row) {
	if (sea[col][row] != 0) {
		cout << "You hit a ship!" << endl;
		playerSea[col][row] = sea[col][row];
	} else {
		cout << "Nothing there" << endl;
		playerSea[col][row] = 8;
	}
}

void Seas::HitLocation(int col, int row) {
	int cols = sizeof(playerSea[0]) / sizeof(playerSea[0][0]);
	int rows = sizeof(playerSea) / sizeof(playerSea[0]);
	
	if (playerSea[col][row] == 8 && playerSea[col][row] != 0) {
		std::cout << "This spot has been hit before, chose other location" << endl;
	} else if (row < 0 || row > rows) {
		cout << "Row not found!" << endl;
	} else if (col < 0 || col > cols) {
		cout << "Col not found!" << endl;
	} else if (playerSea[col][row] == 0) { 
		UpdatePlayerSea(col,row);
	}
}