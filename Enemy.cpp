#include <stdlib.h>

#include "Enemy.h"
#include "Platform.h"
#include "Funzioni.h"

Enemy::Enemy(int x, int y, int type, char symbol) : Entity (x, y, symbol)
{
}

void Enemy::generateEnemies (int enemyNumber, Platform generablePositions)
{
	int x = 0, y = 0;
	bool endOfScreen = false, memorized = false;
	enemyPosition enemies = new enemy;

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
					enemies->x = x;
					enemies->y = y;
					enemies->type = rand() % 3;
					enemies->nextEnemy = new enemy;

					/*
						!!!!!!!!!!!!!!!!
						Istruzione sottostante presente solo per visualizzare temporaneamente
						i nemici generati dalla funzione.
						La visualizzazione vera e propria dovrebbe avvenire nella funzione 'print()'
						poco più sotto, ma la lista 'enemies' istanziata alla riga 15 sembra
						apparentemente scomparire alla fine di questa funzione
					*/
					PrintAt(enemies->x + 1, enemies->y + 1, 'B');

					enemies = enemies->nextEnemy;

					memorized = true;
				}
			}
		}
	}
}

void Enemy::print ()
{
	char s = '0';
	
	while (enemies->nextEnemy != NULL)
	{
		switch (enemies->type)
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

		PrintAt(enemies->x + 1, enemies->y + 1, s);
		enemies = enemies->nextEnemy;
	}
}