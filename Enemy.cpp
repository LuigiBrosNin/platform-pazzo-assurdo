#include "Enemy.h"
#include "Platform.h"

Enemy::Enemy(int x = 0, int y = 0, int type = 0, char symbol = 'S') : Entity(x, y, symbol)
{
	this->type = type;
	enemies = NULL;
}

/*
void saas (int enemyNumber, Platform generablePositions)
{
	int x = 0, y = 0;
	bool endOfScreen = false, memorized = false;
	enemyPosition enemyList = new enemy;

	// TODO: enemyNumber da generare automaticamente
	for (int i = 0; i < enemyNumber && !endOfScreen; i++)
	{
		memorized = false;

		// Scelta di possibili X e Y in cui generare un nemico
		while (x < screenWidth && !memorized)
		{
			x++;

			while (y < screenHeight && !memorized)
			{
				y++;

				// isThere prende il valore (x, y) in cui si vorrebbe generare il nemico
				if (generablePositions.isThere(x, y) && (rand() % 2) == 1)		// Memorizzo il nemico nella lista
				{
					enemyList->x = 0;
					enemyList->y = 0;
					enemyList->nextEnemy = new enemy;
					enemyList = enemyList->nextEnemy;

					memorized = true;
					PrintAt(x, y, this->displayedSymbol);
				}
			}
		}
	}
}*/