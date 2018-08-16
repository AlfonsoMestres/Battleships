#pragma once
#include <vector>


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
	void HitLocation(int row, int col);

	int sea[10][10] = {};
	int playerSea[10][10] = {};
};

