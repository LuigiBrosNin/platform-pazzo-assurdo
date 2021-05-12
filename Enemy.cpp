#include <stdlib.h>

#include "Enemy.h"
#include "Platform.h"
#include "Funzioni.h"

Enemy::Enemy(int x, int y, int type, char symbol) : Entity (x, y, symbol)
{
	this->enemies = new enemy;
	this->enemies->nextEnemy = NULL;
}

void Enemy::generateEnemies (int enemyNumber, Platform generablePositions)
{
	int x = 0, y = 0;
	bool endOfScreen = false, memorized = false;

	for (int i = 0; i < enemyNumber && !endOfScreen; i++)
	{
		memorized = false;

		// Scelta di possibili X e Y in cui generare un nemico
		while (x < generablePositions.getWidth() && !memorized)
		{
			x++;

			while (y < generablePositions.getHeight() && !memorized)
			{
				y++;

				if (generablePositions.isThere(x, y) && (rand() % 2) == 0)		// Memorizzo il nemico nella lista
				{
					enemyPosition list = new enemy;
					list->x = x;
					list->y = y;
					list->type = rand() % 3;
					list->nextEnemy = this->enemies;

					this->enemies = list;
					/*
						!!!!!!!!!!!!!!!!
						Istruzione sottostante presente solo per visualizzare temporaneamente
						i nemici generati dalla funzione.
						La visualizzazione vera e propria dovrebbe avvenire nella funzione 'print()'
						poco più sotto, ma la lista 'enemies' istanziata alla riga 15 sembra
						apparentemente scomparire alla fine di questa funzione
					*/
					//PrintAt(enemies->x + 1, enemies->y + 1, 'B');

					memorized = true;
				}
			}
		}
	}
}

void Enemy::print ()
{
	char s = '0';
	enemyPosition list = this->enemies;

	while (list->nextEnemy != NULL)
	{
		switch (list->type)
		{
			case 0:
			{
				s = 'A';
				break;
			}

			case 1:
			{
				s = 'B';
				break;
			}

			case 2:
			{
				s = 'C';
				break;
			}
		}

		PrintAt(list->x, list->y, s);
		list = list->nextEnemy;
	}
}