#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Ship.h"
#include "Seas.h"

using namespace std;

int main() 
{
	Seas seas;
	string player_input = "";

	cout << "Welcome to Battleships!" << endl;

	seas.DoAction("restart");

	//loop through game render
	while (1) {
		seas.SeaStatus();
		getline(cin, player_input);
		system("cls");

		if (player_input == "exit") {
			system("cls");
			cout << "You gave up!" << endl;
			cout << "This is the sea status! Arrrr" << endl;
			seas.SeaStatus();
			break;
		}

		if (seas.DoAction(player_input) == false)
			cout << "Not an option" << endl;

	}
	system("pause");
	return 0;
}
