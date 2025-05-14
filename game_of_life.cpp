#include "game_of_life.h"

bool game_of_life::get_cell(int i, int j)
{
    if (i < 0 || i >= ROWS || j < 0 || j >= COLS)
        return false;
    else
        return _grid[i][j];
}

int game_of_life::living_neighbours(int i, int j)
{
    int living_count = get_cell(i - 1, j - 1);
    living_count += get_cell(i - 1, j);
    living_count += get_cell(i - 1, j + 1);
    living_count += get_cell(i, j - 1);
    living_count += get_cell(i, j + 1);
    living_count += get_cell(i + 1, j - 1);
    living_count += get_cell(i + 1, j);
    living_count += get_cell(i + 1, j + 1);
    return living_count;
}

void game_of_life::next()
{
    queue<int> changes;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int living_count = living_neighbours(i, j);
            if (get_cell(i, j))
            {
                cout << '*';
                if (living_count < 2 || living_count > 3)
                {
                    changes.push(i * COLS + j);
                }
            }
            else
            {
                cout << '.';
                if (living_count == 3)
                {
                    changes.push(i * COLS + j);
                }
            }
        }
        cout << endl;
    }

    while (!changes.empty())
    {
        int current = changes.front();
        _grid[current / COLS][current % COLS] = !_grid[current / COLS][current % COLS];
        changes.pop();
    }
}

game_of_life::game_of_life()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            _grid[i][j] = rand() % 2;
        }
    }
}