#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Entity.h"
#include "Seas.h"

using namespace std;

int main() 
{
	Seas seas;
	string player_input = "";

	//fill sea with ships
	seas.LoadShips();

	//loop through game render
	while (1) {
		cout << "----CURRENT SEA---- " << endl;
		seas.SeaStatus();
		getline(cin, player_input);
		system("cls");

		if (player_input == "restart") {
			seas.ClearSea();
			seas.LoadShips();
		} else if (player_input == "exit") {
			cout << "You gave up!" << endl;
			cout << "This is the sea status! Arrrr" << endl;
			seas.SeaStatus();
			break;
		}

	}
	system("pause");
	return 0;
}
