#include "game_of_life.h"

//Private:

bool game_of_life::slucajna_vrijednost() {
	return rand() % 4 == 1;
}

bool game_of_life::celija_zauzeta(int i, int j) {
	return _generacija[i][j];
}



//Public:

game_of_life::game_of_life() {
	srand(time(nullptr));
	for (size_t i = 0; i < REDAKA; i++)
	{
		for (size_t j = 0; j < STUPACA; j++)
		{
			_generacija[i][j] = slucajna_vrijednost();
		}
	}

}
void game_of_life::sljedeca_generacija() {
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			int susjedi = 0;
			for (int m = -1; m <= 1; m++)
			{
				for (int n = -1; n <= 1; n++)
				{
					int red = i + m;
					int stupac = j + n;

					if (m == 0 && n == 0)
					{
						continue;
					}
					else if (red >= 0 && red < REDAKA && stupac >= 0 && stupac < STUPACA && celija_zauzeta(red, stupac))
					{
						susjedi++;
					}
				}
			}

			if (celija_zauzeta(i, j))
			{
				if (susjedi < 2 || susjedi > 3)
				{
					_generacija[i][j] = false;
				}
				else
				{
					_generacija[i][j] = true;
				}
			}
			else
			{
				if (susjedi == 3)
				{
					_generacija[i][j] = true;
				}
				else
				{
					_generacija[i][j] = false;
				}
			}
		}
	}


}
void game_of_life::iscrtaj() {
	for (size_t i = 0; i < REDAKA; i++)
	{
		for (size_t j = 0; j < STUPACA; j++)
		{
			if (_generacija[i][j])
			{
				cout << 'O';
			}
			else
				cout << ".";
		}
		cout << endl;
	}
}


