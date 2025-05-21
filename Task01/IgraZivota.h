#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class IgraZivota
{
public:
    IgraZivota(sf::RenderWindow* window, int sirina, int visina, int velicina_celija);
    void draw();

private:
    sf::RenderWindow* window_;
    int sirina_;
    int visina_;
    int velicina_celija_;
    std::vector<std::vector<bool>> celije_;
};