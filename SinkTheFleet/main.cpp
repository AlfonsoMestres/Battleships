#include <iostream>
#include <string>
#include "Seas.h"

int main() 
{
	Seas seas;
	string player_input = "";

	cout << "Welcome to Battleships!" << endl;

	seas.DoAction("restart");

	//Loop through game render
	while (1) {
		seas.GameState();

		getline(cin, player_input);

		system("cls");

		if (seas.DoAction(player_input) == true) {
			std::cout << "Game finished!" << std::endl;
			system("cls");
			break;
		}

	}

	system("pause");
	return 0;
}
