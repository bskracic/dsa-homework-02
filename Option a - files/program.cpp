#include <iostream>
#include <string>
#include <fstream>
#include "game_of_life.h"
using namespace std;

int main() {
	game_of_life the_game;
	
	bool again;
	do {
		system("cls");
		the_game.draw();
		the_game.next_generation();
		
		cout << "Again (1/0): ";
		cin >> again;
	} while (again);

	return 0;
}