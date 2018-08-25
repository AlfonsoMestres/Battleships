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
		std::cout << "Locate the ship " << ship->shipLetter << " with size " << ship->size << " in your sea." << std::endl;
		x = inputNumberBetween("Col: ", 0, aiSea.size());
		y = inputNumberBetween("Row: ", 0, aiSea.size());
		direct = inputNumberBetween("Direction (0 Horizontal / 1 Vertical): ", 0, 1);
		shipsPlaced = LoadShip(playerSea, ship, x, y, direct);
		if (!shipsPlaced)
			std::cout << "Position invalid!" << std::endl;
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

	for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
		LoadAIShips((Ship*)*it);

	std::cout << "The AI ships have been placed, your turn!" << endl;

	for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
		LoadPlayerShips((Ship*)*it);

	std::cout << "Your ships has been placed, let's begin!" << endl;

	return true;
}

const void Seas::SeaStatus(std::vector<std::vector<char>>& sea, string seaPrompt) {

	std::cout << "----" << seaPrompt << " Sea----" << std::endl;

	std::cout << ' ';
	for (int l = 0; l < sea.size(); l++) {
		std::cout << ' ' << l;
	}

	std::cout << std::endl;

	for (int j = 0; j < sea.size(); j++)
	{
		std::cout << j << " ";
		for (int i = 0; i < sea.size(); i++)
		{
			std::cout << sea[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Seas::ReloadGame() {
	int option;

	//TODO: Fix this so the difficulty option wont display the "not an option" selection
	while (1) {
		std::cout << "0- EASY" << std::endl;
		std::cout << "1- NORMAL" << std::endl;
		std::cout << "2- HARD" << std::endl;
		std::cin >> option;
		if (LoadShips(option))
			break;
	}

	cin.clear();
}

bool Seas::HitLocation(std::vector<std::vector<char>>& guessSea, std::vector<std::vector<char>>& enemySea, int col, int row) {
	bool ret = false;
	if (guessSea[col][row] == '*') {
		if (enemySea[col][row] != '*') {
			std::cout << "You hit a ship!" << std::endl;
			guessSea[col][row] = 'X';
		} else {
			std::cout << "Nothing there" << std::endl;
			guessSea[col][row] = 'O';
		}
		ret = true;
	} else {
		std::cout << "This spot has been hit before, chose other location" << std::endl;
	}
	return ret;
}

void const Seas::GameState() {
	std::cout << "    GAME  STATE    " << std::endl;
	SeaStatus(playerSea, "Your");
	SeaStatus(playerGuessSea, "Enemy");
	std::cout << "A = Attack | R = Restart | Q = Quit" << std::endl;
}

void Seas::LaunchMissile() {
	bool properMissileLaunched = false;
	
	while (!properMissileLaunched) {
		GameState();
		col = inputNumberBetween("Col: ", 0, aiSea.size());
		row = inputNumberBetween("Row: ", 0, aiSea.size());
		properMissileLaunched = HitLocation(playerGuessSea, aiSea, col, row);
		system("cls"); 
	}
}

bool Seas::DoAction(string action) {
	if (action == "R" || action == "restart") {
		ReloadGame();
	} else if (action == "A" || action == "attack") {
		LaunchMissile();
	}
	else if (action == "Q" || action == "quit") {
		return true;
	}
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