#include "game_of_life.h"
#include <ctime>

game_of_life::game_of_life() {
    srand(time(nullptr));
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            _generation[i][j] = random_value();
            _next_generation[i][j] = false;
        }
    }
}

bool game_of_life::random_value() {
    return rand() % 4 == 0;
}

bool game_of_life::cell_taken(int i, int j) {
    if (i < 0 || i >= ROWS || j < 0 || j >= COLS) {
        return false;
    }
    return _generation[i][j];
}

void game_of_life::next_generation() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;
                    if (cell_taken(i + di, j + dj)) neighbors++;
                }
            }
            
            if (_generation[i][j]) {
                _next_generation[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                _next_generation[i][j] = (neighbors == 3);
            }
        }
    }
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            _generation[i][j] = _next_generation[i][j];
        }
    }
}

void game_of_life::draw() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << (_generation[i][j] ? "*" : "_");
        }
        cout << endl;
    }
    cout << endl;
}