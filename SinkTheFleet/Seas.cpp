#include <iostream>
#include <string>
#include <array>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Helpers.h"
#include "Seas.h"


Seas::Seas()
{
}

Seas::~Seas()
{
}


std::vector<std::vector<char>> CreateBoard(char fill_value, unsigned int seaSize)
{
	std::vector<char> vec (seaSize, fill_value);
	return { seaSize, vec };
}

void Seas::InitNewSeas(unsigned int size) {
	aiSea = CreateBoard('*', size);
	playerSea = CreateBoard('*', size);
	aiGuessSea = CreateBoard('*', size);
	playerGuessSea = CreateBoard('*', size);
}

//New method, using vector vector chars instead of wrong stuff
bool Seas::LoadShip(std::vector<std::vector<char>>& sea, Ship* ship, int col, int row, bool direct) {
	if (direct) {
		//Vertical
		if (col + ship->size < sea.size()) { //inbounds?
			for (int i = 0; i < ship->size; i++) {
				if (sea[row][col + i] != '*') { //Is the sea occupied by a ship?
					return false;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[row][col + j] = ship->shipLetter; //update sea with ship
			}
		}
		else {
			return false;
		}
	}
	else {
		//Horizontal
		if (row + ship->size <= sea.size()) { //inbounds?
			for (int i = 0; i < ship->size; i++) {
				if (sea[row + i][col] != '*') { //Is the sea occupied by a ship?
					return false;
				}
			}
			for (int j = 0; j < ship->size; j++) {
				sea[row + j][col] = ship->shipLetter; //update sea with ship
			}
		}
		else {
			return false;
		}
	}
	return true;
}

void Seas::LoadAIShips(Ship* ship) {
	int x, y;
	bool direct, shipsPlaced = false;
	while (!shipsPlaced) {
		x = RandomizeBetween(0, aiSea.size() - 1);
		y = RandomizeBetween(0, aiSea.size() - 1);
		direct = RandomizeBetween(0, 1);
		shipsPlaced = LoadShip(aiSea, ship, x, y, direct);
	}
}

void Seas::LoadPlayerShips(Ship* ship) {
	int x, y;
	bool direct, shipsPlaced = false;

	while (!shipsPlaced) {
		SeaStatus(playerSea, "Player");
		cout << "Locate the ship " << ship->shipLetter << " with size " << ship->size << " in your sea." << endl;
		cout << "Col: ", cin >> x, cout << "Row: ", cin >> y;
		cout << "Now introduce the direction (0 Vertical, 1 Horizontal): ", cin >> direct;  //TODO: If wrong option selected, bugs happens
		shipsPlaced = LoadShip(playerSea, ship, x, y, direct);
		if (!shipsPlaced)
			std::cout << "Position invalid!" << endl; 
	}

	
}

bool Seas::LoadShips(int mode) {
	vector<Ship*> ships;
	Ship* ship1;
	Ship* ship2;
	Ship* ship3;
	Ship* ship4;
	unsigned int size;

	switch (mode) {
	case 0: //EASY
		ship1 = new Ship('A', 2);
		ship2 = new Ship('B', 2);
		ship3 = new Ship('C', 3);
		ships.push_back(ship1);
		ships.push_back(ship2);
		ships.push_back(ship3);
		size = 5;
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
		size = 10;
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
		size = 10;
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
		size = 20;
		break;
	default: //NOPE
		std::cout << "Not an option" << endl;
		return false;//Is this ok?
	}

	InitNewSeas(size);

	//Debug info
	std::cout << "Iterations to find a spot -------------------" << endl;

	for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
		LoadAIShips((Ship*)*it);

	std::cout << "The AI ships have been placed, your turn!" << endl;

	for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
		LoadPlayerShips((Ship*)*it);

	std::cout << "Your ships has been placed, let's begin!" << endl;

	return true;
}

const void Seas::SeaStatus(std::vector<std::vector<char>>& sea, string seaPrompt) {

	cout << "----" << seaPrompt << " Sea ----" << endl;

	std::cout << ' ';
	for (int l = 0; l < sea.size(); l++) {
		std::cout << ' ' << l;
	}

	std::cout << endl;

	for (int j = 0; j < sea.size(); j++)
	{
		std::cout << j << " ";
		for (int i = 0; i < sea.size(); i++)
		{
			std::cout << sea[i][j] << " ";
		}
		std::cout << endl;
	}
	std::cout << endl;
}

//void Seas::ClearSea() {
//	memset(&aiSea, '*', sizeof(aiSea));
//	memset(&playerSea, '*', sizeof(playerSea));
//	memset(&playerGuessSea, '*', sizeof(playerGuessSea));
//	memset(&aiGuessSea, '*', sizeof(aiGuessSea));
//}

void Seas::ReloadGame() {
	int option;

	//TODO: Fix this so the difficulty option wont display the "not an option" selection
	while (1) {
		cout << "0- EASY" << endl;
		cout << "1- NORMAL" << endl;
		cout << "2- HARD" << endl;
		cin >> option;
		/*ClearSea();*/
		if (LoadShips(option))
			break;
	}

	cin.clear();
}

void Seas::UpdatePlayerSea(int col, int row) {
	if (aiSea[col][row] != '*') {
		cout << "You hit a ship!" << endl;
		playerGuessSea[col][row] = 'X';
	} else {
		cout << "Nothing there" << endl;
		playerGuessSea[col][row] = 'O';
	}
}

//TOOD: FUTURE change '*' to an enum like seaState::WATER
void Seas::HitLocation(int col, int row) {
	if (playerGuessSea[col][row] == '*')  
		UpdatePlayerSea(col, row);
	else
		std::cout << "This spot has been hit before, chose other location" << endl;
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
			col = inputNumberBetween("Col: ", 0, aiSea.size());
			row = inputNumberBetween("Row: ", 0, aiSea.size());
			HitLocation(col, row);
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