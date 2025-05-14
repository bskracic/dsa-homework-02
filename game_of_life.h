#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <queue>

using namespace std;

class game_of_life {
private:
	static const unsigned int COLS = 40;
	static const unsigned int ROWS = 20;
	bool _grid[ROWS][COLS];
	bool get_cell(int i, int j);
	int living_neighbours(int i, int j);

public:
	game_of_life();
	void next();
};

#endif
