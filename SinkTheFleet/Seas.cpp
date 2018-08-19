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

	//Dev 4 directions like the physical game, where you can place the little ship in every direction. NOT NECESSARY, this could work with just vertical or horizontal
	switch (direct) {
	//Second phase probably could be storing the non-possible locations for the ships to increase the efficiency
	case 0: //N
		if (y - ship->size >= 0) { //inbounds?
			for (int i = 0; i < ship->size; i++) {
				if (sea[x][y - i] != '*') { //Is the sea occupied by a ship?
					LoadShip(ship, loops); //reiterate
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x][y - j] = ship->shipLetter; //update sea with ship
			}
			std::cout << "Ship " << ship->shipLetter << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	case 1: //S
		if (y + ship->size <= 9) {
			for (int i = 0; i < ship->size; i++) {
				if (sea[x][y + i] != '*') {
					LoadShip(ship, loops);
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x][y + j] = ship->shipLetter;
			}
			std::cout << "Ship " << ship->shipLetter << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	case 2: //E
		if (x + ship->size <= 9) {
			for (int i = 0; i < ship->size; i++) {
				if (sea[x + i][y] != '*') {
					LoadShip(ship, loops);
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x + j][y] = ship->shipLetter;
			}
			std::cout << "Ship " << ship->shipLetter << " iterated " << loops << " times" << endl;
		}
		else {
			LoadShip(ship, loops);
		}
		break;
	case 3: //W
		if (x - ship->size >= 0) {
			for (int i = 0; i < ship->size; i++) {
				if (sea[x - i][y] != '*') {
					LoadShip(ship, loops);
					return;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[x - j][y] = ship->shipLetter;
			}
			std::cout << "Ship " << ship->shipLetter << " iterated " << loops << " times" << endl;
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
		ship1 = new Ship('A', 4);
		ship2 = new Ship('B', 4);
		ship3 = new Ship('C', 5);
		ship4 = new Ship('D', 6);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	case 1: //NORMAL
		ship1 = new Ship('A', 2);
		ship2 = new Ship('B', 3);
		ship3 = new Ship('C', 4);
		ship4 = new Ship('D', 5);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	case 2: //HARD
		ship1 = new Ship('A', 2);
		ship2 = new Ship('B', 2);
		ship3 = new Ship('C', 3);
		ship4 = new Ship('D', 4);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		ships.push_back(ship4);
		break;
	case 42: //Meaning of life
		std::cout << "Prove worthy of this option" << endl;
		ship1 = new Ship('A', 1);
		ship2 = new Ship('B', 1);
		ship3 = new Ship('C', 1);
		ship4 = new Ship('D', 1);
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
	//TODO: We need to be able to see our see and the enemy sea when finished the game or GaveUp
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
	memset(&sea, '*', sizeof(sea));
	memset(&playerSea, '*', sizeof(playerSea));
}

void Seas::ReloadGame() {
	int option;

	//TODO: Fix this so the difficulty option wont display the "not an option" selection
	while (1) {
		cout << "0- EASY" << endl;
		cout << "1- NORMAL" << endl;
		cout << "2- HARD" << endl;
		cin >> option;
		ClearSea();
		if (LoadShips(option))
			break;
	}

}

void Seas::UpdatePlayerSea(int col, int row) {
	if (sea[col][row] != '*') {
		cout << "You hit a ship!" << endl;
		playerSea[col][row] = 'X';
	} else {
		cout << "Nothing there" << endl;
		playerSea[col][row] = 'O';
	}
}

void Seas::HitLocation(int col, int row) {
	int cols = sizeof(playerSea[0]) / sizeof(playerSea[0][0]);
	int rows = sizeof(playerSea) / sizeof(playerSea[0]);
	
	if (playerSea[col][row] != '*') {
		if(playerSea[col][row] == 'O')
			std::cout << "This spot has been hit before, chose other location" << endl;
	} else if (row < 0 || row > rows) {
		cout << "Row not found!" << endl;
	} else if (col < 0 || col > cols) {
		cout << "Col not found!" << endl;
	} else if (playerSea[col][row] == '*') { 
		UpdatePlayerSea(col,row);
	}
	//Check if the missile sink the last ship to set the Win condition
}

bool Seas::DoAction(string action) {
	bool ret = true;

	vector<string> parsedAction = ParseAction(action);

	switch (parsedAction.size()) {
		case 1:
			if (parsedAction[0] == "restart") {
				ReloadGame();
			}
			else
				ret = false;
			break;
		case 2:
			if (is_number(parsedAction[0]) && is_number(parsedAction[1])) {
				int col = atoi(parsedAction[0].c_str());
				int row = atoi(parsedAction[1].c_str());
				HitLocation(col, row);
			}
			break;
		default:
			ret = false;
			break;
	}

	return ret;
}

///Take the input and split them into parts so we can manage them clearly
vector<string> Seas::ParseAction(string args) //Filling new memory slots with ducplicate content is wasting memory, we should avoid this in next steps and make it directly
{
	int len = args.length();
	vector<string> subArray;

	for (int j = 0, k = 0; j < len; j++) {
		if (args[j] == ' ') {
			string ch = args.substr(k, j - k);
			k = j + 1;
			subArray.push_back(ch);
		}
		if (j == len - 1) {
			string ch = args.substr(k, j - k + 1);
			subArray.push_back(ch);
		}
	}

	return subArray;
}