#include <iostream>
#include <string>
#include <array>
#include <random>
#include "Ship.h"
#include "Seas.h"

using namespace std;

void MainMenu(Seas& seas) {
	int option;
	
	cout << "Welcome to Battleships!" << endl;
	while (1) {
		cout << "0- EASY" << endl;
		cout << "1- NORMAL" << endl;
		cout << "2- HARD" << endl;
		cin >> option;
		seas.ClearSea();
		if (seas.LoadShips(option))
			break;
	}
}

void Command(Seas& seas) {
	int col, row;
	cout << "Attack location: "; cin >> col >> row;
	system("cls");
	seas.HitLocation(col, row);
}

int main() 
{
	Seas seas;
	string player_input = "";

	MainMenu(seas);

	//loop through game render
	while (1) {
		//TODO: para poder continuar con el juego se deberia cambiar la matriz por chars, ya que ahora mismo estoy pidiendo numeros con cin y ints y si escribo E petara el sistema
		seas.SeaStatus();
		Command(seas);
		getline(cin, player_input);

		if (player_input == "restart") {
			MainMenu(seas);
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
