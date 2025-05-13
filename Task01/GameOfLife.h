#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class GameOfLife {
public:
	GameOfLife(sf::RenderWindow* window);
	void draw();
private:
	int rows = 40, columns = 60;
	vector<vector<sf::RectangleShape>> currentGeneration;
	vector<vector<sf::RectangleShape>> nextGeneration;
	bool cellTaken(int i, int j);
	int getNeighbors(int i, int j);
	sf::RenderWindow* window;
	void setGeneration();
};