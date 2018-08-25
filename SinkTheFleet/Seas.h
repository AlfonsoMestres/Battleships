#pragma once
#include <vector>
#include <string>
#include "Ship.h"

class Seas
{
public:
	Seas();
	virtual ~Seas();

	void InitNewSeas(unsigned int size);
	//void InitSea(std::vector<std::vector<char>>& playingBoard, int rows);
	bool LoadShip(std::vector<std::vector<char>>& sea, Ship* ship, int col, int row, bool direct);
	void LoadAIShips(Ship* ship);
	void LoadPlayerShips(Ship* ship);
	bool LoadShips(int mode);
	const void SeaStatus(std::vector<std::vector<char>>& sea, string seaPrompt);
	bool DoAction(string action);
	void ReloadGame();
	void LaunchMissile();

	std::vector<std::vector<char>> aiSea;
	std::vector<std::vector<char>> playerSea;
	std::vector<std::vector<char>> aiGuessSea;
	std::vector<std::vector<char>> playerGuessSea;

	int lastColHit, col, row, lastRowHit;

private:
	bool HitLocation(std::vector<std::vector<char>>& guessSea, std::vector<std::vector<char>>& enemySea, int col, int row);
	vector<string> ParseAction(string args);

};

