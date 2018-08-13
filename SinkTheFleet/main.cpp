#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Entity.h"
#include "Seas.h"

using namespace std;

//size of our sea
int sea[10][10] = {};
int playerSea[10][10] = {};

void SeaStatus() {
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

///c++ 11 Randomizer style
int RandomizeBetween(int min, int max) {
	//the random device that will seed the generator
	random_device seeder;
	//then make a mersenne twister engine
	mt19937 engine(seeder());
	//then the easy part... the distribution
	uniform_int_distribution<int> dist(min, max);
	//then just generate the integer like this:
	return dist(engine);
}

void LoadShip(Entity* ship, int loops) {
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

void LoadShips() {
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

void ClearSea() {
	memset(sea, 0, sizeof(sea));
}

int main() 
{
	Seas seas;
	string player_input = "";

	//fill sea with ships
	LoadShips();

	//loop through game render
	while (1) {
		cout << "----CURRENT SEA---- " << endl;
		SeaStatus();
		getline(cin, player_input);
		system("cls");

		if (player_input == "restart") {
			ClearSea();
			LoadShips();
		} else if (player_input == "exit") {
			cout << "You gave up!" << endl;
			cout << "This is the sea status! Arrrr" << endl;
			SeaStatus();
			break;
		}

	}
	system("pause");
	return 0;
}
