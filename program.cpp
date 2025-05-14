#include <iostream>
#include "game_of_life.h"
using namespace std;

int main() {
	game_of_life the_game;
	
	bool again;
	do {
		the_game.next();
		
		cout << "Again (1/0): ";
		cin >> again;
	} while (again);

	return 0;
}