#pragma once
#include <vector>
#include <string>

class Seas
{
public:
	Seas();
	virtual ~Seas();

	void LoadShip(Ship* ship, int loops);
	bool LoadShips(int mode);
	void SeaStatus();
	void ClearSea();
	void UpdatePlayerSea(int row, int col);
	bool DoAction(string action);
	void ReloadGame();

	char sea[10][10] = {};
	char playerSea[10][10] = {};

private:
	void HitLocation(int row, int col);
	vector<string> ParseAction(string args);

};

