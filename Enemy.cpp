#include <stdlib.h>

#include "Enemy.h"
#include "Platform.h"
#include "Funzioni.h"
#include "Bullet.h"

Enemy::Enemy(int x, int y, int type, char symbol) : Entity(x, y, symbol)
{
	this->enemies = NULL;
	this->directionUp = true;
	this->touched = false;
}

void Enemy::generateEnemies(int enemyNumber, Platform generablePositions)
{
	// - Funzione che genera la lista dei nemici di un livello -

	int x = 0, y = 0;
	bool endOfScreen = false, memorized = false;

	while (enemyNumber > 0)
	{
		// Generazione di coordinate casuali in cui generare i nemici
		x = rand() % generablePositions.getWidth() + 1;
		y = 2 * rand() % generablePositions.getHeight();

		// Creazione (o meno) effettiva del nemico
		if (generablePositions.isThere(x, y) && (generablePositions.isThere(x, y + 2) || generablePositions.isThere(x, y - 2) || generablePositions.isThere(x + 2, y) || generablePositions.isThere(x - 2, y)))
		{
			enemyPosition list = new enemy;
			list->x = x;
			list->y = y;
			//list->type = rand() % 3;
			list->type = 2;

			if (list->type == 0)
				list->direction = -1;
			else
			{
				if (list->type == 2)
				{
					list->fireBallX = x;
					list->fireBallY = y;
				}

				list->direction = rand() % 4;
			}

			list->nextEnemy = this->enemies;

			this->enemies = list;

			enemyNumber--;
		}
	}
}

void Enemy::print (Platform generablePositions)
{
	char s = '0', fireBallChar = '*';
	enemyPosition list = this->enemies;
	
	while (list != NULL)
	{
		prevx = list->x;
		prevy = list->y;
		switch (list->type)
		{
			case 0:		// Nemici statici
			{
				s = 'A';
				break;
			}

			case 1:		// Nemici che possono muoversi
			{
				s = 'B';

				list->movementSleepCount_UpDown++;
				list->movementSleepCount_RightLeft++;

				if (list->movementSleepCount_UpDown == 5 && (list->direction == 0 || list->direction == 1))
				{
					list->movementSleepCount_UpDown = -1;

					if (list->direction == 0)	// Movimento verso il basso
					{
						if ((list->y + 2) < generablePositions.getHeight())// && generablePositions.isThere(list->x, list->y + 2))
							list->y += 2;
						else
							list->direction = 1;
					}
					else if (list->direction == 1)	// Movimento verso l'alto
					{
						if ((list->y - 2) >= 0)// && generablePositions.isThere(list->x, list->y - 2))
							list->y -= 2;
						else
							list->direction = 0;
					}
				}
				else if (list->movementSleepCount_RightLeft == 4 && (list->direction == 2 || list->direction == 3))
				{
					list->movementSleepCount_RightLeft = -1;

					if (list->direction == 2)	// Movimento verso destra
					{
						if ((list->x + 1) < generablePositions.getWidth() && generablePositions.isThere(list->x + 1, list->y))
							list->x += 1;
						else
							list->direction = 3;
					}
					else if (list->direction == 3)	// Movimento verso sinistra
					{
						if ((list->x - 1) >= 0 && generablePositions.isThere(list->x - 1, list->y))
							list->x -= 1;
						else
							list->direction = 2;
					}
				}

				break;
			}

			case 2:		// Nemici che possono sparare
			{
				s = 'C';

				list->movementSleepCount_UpDown++;
				list->movementSleepCount_RightLeft++;

				if (list->movementSleepCount_UpDown == 3 && (list->direction == 0 || list->direction == 1))
				{
					list->movementSleepCount_UpDown = -1;

					if (list->direction == 0)	// Spara verso il basso
					{
						if (list->fireBallY < generablePositions.getHeight() - 1)
						{
							PrintAt(list->fireBallX + 1, list->fireBallY + 1, fireBallChar, prevx + 1, prevy + 1);
							PrintAt(list->fireBallX + 1, list->fireBallY, ' ', prevx + 1, prevy + 1);
							list->fireBallY += 1;
						}
						else if (list->fireBallY >= generablePositions.getHeight() - 1)
						{
							if (!(generablePositions.isThere(list->x, list->y + 2)))
								list->direction = 1;
							else
							{
								PrintAt(list->fireBallX + 1, list->fireBallY, ' ', prevx + 1, prevy + 1);
								list->fireBallX = list->x;
								list->fireBallY = list->y;
							}
						}
					}
					else if (list->direction == 1)	// Spara verso l'alto
					{
						if (list->fireBallY > 0)
						{
							PrintAt(list->fireBallX + 1, list->fireBallY, fireBallChar, prevx + 1, prevy + 1);
							PrintAt(list->fireBallX + 1, list->fireBallY + 1, ' ', prevx + 1, prevy + 1);
							list->fireBallY -= 1;
						}
						else if (list->fireBallY <= 0)
						{
							if (!(generablePositions.isThere(list->x, list->y - 2)))
								list->direction = 0;
							else
							{
								PrintAt(list->fireBallX + 1, list->fireBallY + 1, ' ', prevx + 1, prevy + 1);
								list->fireBallX = list->x;
								list->fireBallY = list->y;
							}
						}
					}
				}
				else if (list->movementSleepCount_RightLeft == 1 && (list->direction == 2 || list->direction == 3))
				{
					list->movementSleepCount_RightLeft = -1;

					if (list->direction == 2)	// Spara verso destra
					{
						if (list->fireBallX < generablePositions.getWidth())
						{
							PrintAt(list->fireBallX + 1, list->fireBallY + 1, fireBallChar, prevx + 1, prevy + 1);
							PrintAt(list->fireBallX, list->fireBallY + 1, ' ', prevx + 1, prevy + 1);
							list->fireBallX += 1;
						}
						else if (list->fireBallX >= generablePositions.getWidth())
						{
							PrintAt(list->fireBallX, list->fireBallY + 1, ' ', prevx + 1, prevy + 1);
							list->fireBallX = list->x;
							list->fireBallY = list->y;
						}
					}
					else if (list->direction == 3)	// Spara verso sinistra
					{
						if (list->fireBallX > 0)
						{
							PrintAt(list->fireBallX, list->fireBallY + 1, fireBallChar, prevx + 1, prevy + 1);
							PrintAt(list->fireBallX + 1, list->fireBallY + 1, ' ', prevx + 1, prevy + 1);
							list->fireBallX -= 1;
						}
						else if (list->fireBallX <= 0)
						{
							PrintAt(list->fireBallX + 1, list->fireBallY + 1, ' ', prevx + 1, prevy + 1);
							list->fireBallX = list->x;
							list->fireBallY = list->y;
						}
					}
				}

				break;
			}

			default:
				break;
		}

		PrintAt(list->x + 1, list->y + 1, s, prevx+1, prevy+1);
		list = list->nextEnemy;
	}
}

bool Enemy::enemyHandler(Player player, Bullet bullet)
{
	enemyPosition copy = this->enemies, newEnemiesList, previousNode;
	bool update = false, touched = false;

	/*
	 * Scorro una copia della lista attuale per vedere cosa sta facendo il giocatore:
	 *	- se tocca un nemico da sopra ("saltandoci") questi viene eliminato;
	 *	- se un proiettile sparato tocca un nemico questi viene eliminato;
	 *	- se tocca un nemico da altre direzioni senza sparargli, rimuove una vita.
	 */

	while (copy != NULL)
	{
		if ((copy->x == player.getX() && copy->y == player.getY()) || (bullet.getX() == copy->x && bullet.getY() == copy->y))
		{
			if (player.getPrevy() >= copy->y)	// Controllo se il giocatore tocca il nemico senza caderci da sopra
				touched = true;

			update = true;
			copy->type = -1;	// Nemico da eliminare o a causa di un proiettile o perché il giocatore ci è passato sopra
		}
		else if (copy->fireBallX == player.getX() && copy->fireBallY == player.getY())
			touched = true;

		if (update || touched)
		{
			if (copy->direction == 0)
			{
				PrintAt(copy->fireBallX + 1, copy->fireBallY, ' ', prevx + 1, prevy + 1);
				copy->fireBallX = -2;
			}
			else if (copy->direction == 1)
			{
				PrintAt(copy->fireBallX + 1, copy->fireBallY + 1, ' ', prevx + 1, prevy + 1);
				copy->fireBallX = -2;				
			}
			else if (copy->direction == 2)
			{
				PrintAt(copy->fireBallX, copy->fireBallY + 1, ' ', prevx + 1, prevy + 1);
				copy->fireBallY = -2;
			}
			else if (copy->direction == 3)
			{
				PrintAt(copy->fireBallX + 1, copy->fireBallY + 1, ' ', prevx + 1, prevy + 1);
				copy->fireBallY = -2;
			}
		}

		copy = copy->nextEnemy;
	}

	if (update)
	{
		copy = this->enemies;
		newEnemiesList = copy;
		previousNode = newEnemiesList;

		while (copy != NULL)
		{
			if (copy->type != -1)
			{
				if (copy != previousNode)
					previousNode = previousNode->nextEnemy;

				copy = copy->nextEnemy;
			}
			else
			{
				if (newEnemiesList == copy)
				{
					newEnemiesList = newEnemiesList->nextEnemy;
					copy = copy->nextEnemy;
				}
				else
				{
					copy = copy->nextEnemy;
					previousNode->nextEnemy = copy;
				}
			}
		}

		this->enemies = newEnemiesList;
	}

	return touched;
}