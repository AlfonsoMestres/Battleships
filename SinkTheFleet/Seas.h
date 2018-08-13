#pragma once
#include <vector>


class Seas
{
public:
	Seas();
	virtual ~Seas();

	void LoadShip(Entity* ship, int loops);
	void LoadShips();
	void SeaStatus();
	void ClearSea();

	int sea[10][10] = {};
	int playerSea[10][10] = {};
};

