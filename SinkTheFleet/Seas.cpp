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


std::vector<std::vector<char>> CreateBoard(char fill_value, unsigned int seaSize) {
	std::vector<char> vec (seaSize, fill_value);
	return { seaSize, vec };
}

void Seas::InitNewSeas(unsigned int size) {
	aiSea = CreateBoard('*', size);
	playerSea = CreateBoard('*', size);
	aiGuessSea = CreateBoard('*', size);
	playerGuessSea = CreateBoard('*', size);
}

bool Seas::WinConditionAchieved(std::vector<std::vector<char>>& sea) {
	//TODO: This should check only a new parameter in the ship class regarding if its sunk or not, this is not optimal
	//also the ships should have owners to avoid confusions (maybe)

	//Check if theres more ships on the sea that doesnt belong to a letter
	for (int i = 0; i < sea.size() - 1; i++) {
		for (int j = 0; j < sea.size() - 1; j++) {
			if (sea[i][j] != '*' && sea[i][j] != 'X') {
				return false;
			}
		}
	}

	return true;
}

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

bool Seas::LoadGame(int mode) {
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
	default: //NOPE
		std::cout << "Not an option" << endl;
		return false; //Is this ok?
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
		if (LoadGame(option))
			break;
	}

	cin.clear();
}

bool Seas::HitLocation(std::vector<std::vector<char>>& guessSea, std::vector<std::vector<char>>& enemySea, int col, int row) {
	bool ret = false;
	if (guessSea[col][row] == '*') {
		if (enemySea[col][row] != '*') {
			std::cout << "Hit a ship!" << std::endl;
			guessSea[col][row] = 'X';
		} else {
			std::cout << "Nothing there" << std::endl;
			guessSea[col][row] = 'O';
		}
		//Update the sea so we can see the state of their missile siege and thus, check the win condition
		enemySea[col][row] = 'X';
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
	//For Debug purpouse
	SeaStatus(aiSea, "Solution");
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

void Seas::AITurn() {
	if(lastHitRow != NULL) {
		if (lastDirectionHit == NULL) {
			lastDirectionHit = RandomizeBetween(0, 1);
		}
		if (HitLocation(aiGuessSea, playerSea, lastHitCol, lastHitRow)) {
			if (lastDirectionHit) {
				lastHitCol = lastHitCol + 1;
				lastHitRow = lastHitCol;
			} else {
				lastHitCol = lastHitCol;
				lastHitRow = lastHitCol + 1;
			}
			
		} else {
			lastHitCol = NULL;
			lastHitRow = NULL;
		}
	} else {
		int x = RandomizeBetween(0, aiSea.size() - 1);
		int y = RandomizeBetween(0, aiSea.size() - 1);
		if (HitLocation(aiGuessSea, playerSea, x, y)) {
			lastHitCol = x;
			lastHitRow = y;
		} else {
			lastHitCol = NULL;
			lastHitRow = NULL;
		}
	}
}

bool Seas::DoAction(string action) {
	string lowerAction = ToLowerCase(action);
	if (Same(lowerAction,"r") || Same(lowerAction,"restart")) {
		ReloadGame();
	} else if (Same(lowerAction,"a") || Same(lowerAction,"attack")) {
		LaunchMissile();
		//Maybe here the win condition, we need to recheck this when the AI is ready
		if (WinConditionAchieved(aiSea)) {
			return true; //TODO: Meanwhile we handle other stuff, we request a quit
		};
	} else if (Same(lowerAction,"q")|| Same(lowerAction,"quit")) {
		return true;
	}
}
