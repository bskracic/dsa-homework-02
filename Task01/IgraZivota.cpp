#include "IgraZivota.h"
#include <cstdlib>
#include <ctime>

IgraZivota::IgraZivota(sf::RenderWindow* window, int sirina, int visina, int velicina_celija)
    : window_(window), sirina_(sirina), visina_(visina), velicina_celija_(velicina_celija)
{
    celije_.resize(sirina_);
    for (int x = 0; x < sirina_; x++)
    {
        celije_[x].resize(visina_);
        for (int y = 0; y < visina_; y++)
        {
            celije_[x][y] = rand() % 4 == 0;
        }
    }
}

void IgraZivota::draw()
{
    for (int x = 0; x < sirina_; x++)
    {
        for (int y = 0; y < visina_; y++)
        {
            sf::RectangleShape celija(sf::Vector2f(velicina_celija_, velicina_celija_));
            celija.setPosition(sf::Vector2f(x * velicina_celija_, y * velicina_celija_));
            if (celije_[x][y])
            {
                celija.setFillColor(sf::Color::Green);
            }
            else
            {
                celija.setFillColor(sf::Color::Black);
            }
            window_->draw(celija);
        }
    }

    std::vector<std::vector<bool>> slj_celija = celije_;

    for (int x = 0; x < sirina_; x++)
    {
        for (int y = 0; y < visina_; y++)
        {
            int ziv_susjed = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }
                    int susjedX = x + i;
                    int susjedY = y + j;
                    if (susjedX >= 0 && susjedX < sirina_ && susjedY >= 0 && susjedY < visina_ && celije_[susjedX][susjedY])
                    {
                        ziv_susjed++;
                    }
                }
            }
            if (celije_[x][y])
            {
                if (ziv_susjed < 2 || ziv_susjed > 3)
                {
                    slj_celija[x][y] = false;
                }
            }
            else
            {
                if (ziv_susjed == 3)
                {
                    slj_celija[x][y] = true;
                }
            }
        }
    }
    celije_ = slj_celija;
}