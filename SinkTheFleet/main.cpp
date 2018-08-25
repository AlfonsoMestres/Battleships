#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Helpers.h"
#include "Seas.h"

int main() 
{
	Seas seas;
	bool playerTurn;
	string player_input = "";

	cout << "Welcome to Battleships!" << endl;

	playerTurn = RandomizeBetween(0, 1);

	seas.DoAction("restart");

	//Loop through game render
	while (1) {
		seas.GameState();
		getline(cin, player_input);
		system("cls");

		if (seas.DoAction(player_input)) {
			system("cls");
			cout << "You gave up!" << endl;
			cout << "This is the sea status! Arrrr" << endl;
			seas.SeaStatus(seas.playerSea, "Player");
			seas.SeaStatus(seas.aiSea, "AI");
			break;
		}

	}

	system("pause");
	return 0;
}
