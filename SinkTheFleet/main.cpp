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

		//TODO: Fix this, if you enter another option in the menu, the AI will launch a missile, we need to avoid that
		//maybe we can put the AITurn inside the Seas and make it private so we throw the AI turn before or after the playar turn
		if (playerTurn){
			getline(cin, player_input);
		} else {
			seas.AITurn();
		}

		playerTurn = !playerTurn;

		system("cls");

		if (seas.DoAction(player_input) == true) {
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
