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
		seas.SeaStatus(seas.playerSea, "Player");
		getline(cin, player_input); //TODO: Should edit functions to work for the AI and the player
		system("cls");

		if (player_input == "exit") {
			system("cls");
			cout << "You gave up!" << endl;
			cout << "This is the sea status! Arrrr" << endl;
			seas.SeaStatus(seas.playerSea, "Player");
			seas.SeaStatus(seas.aiSea, "AI");
			break;
		}

		if (seas.DoAction(player_input) == false)
			cout << "Not an option" << endl;

	}

	system("pause");
	return 0;
}
