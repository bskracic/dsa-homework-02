#include "game_of_life.h"
#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

bool game_of_life::random_value()
{
	return rand() % 4 == 0;
}

bool game_of_life::cell_taken(int i, int j)
{

	if (0 <= i and i < activeRows)
	{
		if (0 <= j and j < activeCols)
		{
			return _generation[i][j];

		}
	}



	return false;
}

game_of_life::game_of_life()
{
	srand(time(nullptr));

	for (int row = 0; row < activeRows; row++)
	{

		for (int col = 0; col < activeCols; col++)
		{
			_generation[row][col] = random_value();

		}



	}
}

void game_of_life::next_generation()
{

	for (int row = 0; row < activeRows; row++)
	{


		for (int col = 0; col < activeCols; col++)
		{
			int counter = 0;

			for (int i_row = -1; i_row <= 1; i_row++)
			{
				for (int j_col = -1; j_col <= 1; j_col++)
				{
					if (i_row == 0 and j_col == 0)
					{
						continue;
					}
					else if (cell_taken(row + i_row, col + j_col))
					{
						counter++;
					}
				}
			}
			if (_generation[row][col])
			{
				if (counter == 2 or counter == 3)
				{
					_next_generation[row][col] = true;

				}
				else
				{
					_next_generation[row][col] = false;

				}
			}
			else
			{

				if (counter == 3)
				{
					_next_generation[row][col] = true;
				}
				else
				{
					_next_generation[row][col] = false;
				}
			}
		}
	}

	for (int row = 0; row < activeRows; row++)
		for (int col = 0; col < activeCols; col++)
			_generation[row][col] = _next_generation[row][col];


}
void game_of_life::set_window(sf::RenderWindow* window) {
	this->window = window;
}

void game_of_life::set_cell_texture(sf::Texture* texture) {
	cellTexture = texture;
}

void game_of_life::set_dead_cell_texture(sf::Texture* texture) {
	deadCellTexture = texture;
}

void game_of_life::set_alt_cell_texture(sf::Texture* texture) {
	altCellTexture = texture;
}





void game_of_life::toggle_icon_mode() {
	useIcons = !useIcons;

	if (useIcons) {
		cellSize = 60.f;
		activeCols = ICON_MODE_COLS;
		activeRows = ICON_MODE_ROWS;
		std::cout << "Icon mode ON\n";
	}
	else {
		cellSize = 15.f;
		activeCols = COLOR_MODE_COLS;
		activeRows = COLOR_MODE_ROWS;
		std::cout << "Color mode ON\n";
		reset();
	}
}



void game_of_life::draw(bool  paused) {
	if (!window) return;

	float offsetX = (WINDOW_WIDTH - activeCols * cellSize) / 2.f;
	float offsetY = (WINDOW_HEIGHT - activeRows * cellSize) / 2.f;

	for (int row = 0; row < activeRows; ++row) {
		for (int col = 0; col < activeCols; ++col) {
			sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
			cell.setPosition({ col * cellSize + offsetX, row * cellSize + offsetY });
			cell.setOutlineThickness(1);
			cell.setOutlineColor(sf::Color(40, 40, 40, 200));


			if (_generation[row][col]) {
				if (useIcons && cellTexture && altCellTexture) {
					// Alternate between two live cell icons Falcon and TIE Fighter
					sf::Texture* selectedTexture = ((row + col) % 2 == 0) ? cellTexture : altCellTexture;

					sf::Sprite sprite(*selectedTexture);
					sprite.setPosition({ col * cellSize + offsetX, row * cellSize + offsetY });
					sprite.setScale({
						cellSize / selectedTexture->getSize().x,
						cellSize / selectedTexture->getSize().y
						});
					window->draw(sprite);
				}
				else {
					// back to colored square for live cell
					cell.setFillColor(paused ? sf::Color(80, 170, 180) : sf::Color(0, 200, 255));
					window->draw(cell);
				}
			}
			else {
				if (useIcons && deadCellTexture) {
					sf::Sprite deadSprite(*deadCellTexture);
					deadSprite.setPosition({ col * cellSize + offsetX, row * cellSize + offsetY });
					deadSprite.setScale({ cellSize / deadCellTexture->getSize().x, cellSize / deadCellTexture->getSize().y });
					window->draw(deadSprite);
				}
				else {
					cell.setFillColor(sf::Color(15, 15, 20, 100));
					window->draw(cell);
				}
			}

		}
	}
}



void game_of_life::reset() {
	for (int row = 0; row < activeRows; ++row)
		for (int col = 0; col < activeCols; ++col)
			_generation[row][col] = random_value();
}


// Original Draw without SFML for context:
// 
//void game_of_life::draw()
//{
//	Sleep(450);//added delay
//
//	system("cls");//I added for clearing the grid
//
//	for (int row = 0; row < ROWS; row++)
//	{
//
//
//		for (int col = 0; col < COLS; col++)
//		{
//
//			if (_generation[row][col])
//			{
//				cout << " 0 ";
//			}
//			else
//			{
//				cout << " . ";
//
//			}
//
//		}
//		cout << endl;
//
//
//
//	}
//
//}


