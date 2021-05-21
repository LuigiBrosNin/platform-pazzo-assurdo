#include <stdlib.h>

#include "Enemy.h"
#include "Platform.h"
#include "Funzioni.h"
#include "Bullet.h"

int movementSleepCount = -1, fireSleepCount = -1;
bool directionUp = true;

Enemy::Enemy(int x, int y, int type, char symbol) : Entity (x, y, symbol)
{
	this->enemies = new enemy;
	this->enemies->nextEnemy = NULL;
}

void Enemy::generateEnemies(int enemyNumber, Platform generablePositions)
{
	// - Funzione che genera la lista dei nemici di un livello -

	int x = 0, y = 0;
	bool endOfScreen = false, memorized = false;

	while (enemyNumber > 0)
	{
		// Generazione di coordinate casuali in cui generare i nemici
		x = rand() % generablePositions.getWidth();
		y = 2 * rand() % generablePositions.getHeight();

		// Creazione (o meno) effettiva del nemico
		if (generablePositions.isThere(x, y) && (generablePositions.isThere(x, y + 2) || generablePositions.isThere(x, y - 2) || generablePositions.isThere(x + 2, y) || generablePositions.isThere(x - 2, y)))
		{
			enemyPosition list = new enemy;
			list->x = x;
			list->y = y;
			list->type = rand() % 3;
			if (list->type == 1)
				list->direction = rand() % 4;
			else
				list->direction = -1;
			list->nextEnemy = this->enemies;

			this->enemies = list;

			enemyNumber--;
		}
	}
}

void Enemy::print (Platform generablePositions)
{
	char s = '0';
	enemyPosition list = this->enemies;

	while (list->nextEnemy != NULL)
	{
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

				movementSleepCount++;

				if (movementSleepCount == 5)
				{
					movementSleepCount = -1;

					if (list->direction == 0)	// Movimento verso il basso
					{
						if ((list->y + 2) < generablePositions.getHeight() && generablePositions.isThere(list->x, list->y + 2))
							list->y += 2;
						else
							list->direction = 1;
					}
					else if (list->direction == 1)	// Movimento verso l'alto
					{
						if ((list->y - 2) >= 0 && generablePositions.isThere(list->x, list->y - 2))
							list->y -= 2;
						else
							list->direction = 0;
					}
					else if (list->direction == 2)	// Movimento verso destra
					{
						if ((list->x + 2) < generablePositions.getWidth() && generablePositions.isThere(list->x + 2, list->y))
							list->x += 2;
						else
							list->direction = 3;
					}
					else if (list->direction == 3)	// Movimento verso sinistra
					{
						if ((list->x - 2) >= 0 && generablePositions.isThere(list->x - 2, list->y))
							list->x -= 2;
						else
							list->direction = 2;
					}
				}

				break;
			}

			case 2:		// Nemici che possono sparare
			{
				s = 'C';

				fireSleepCount++;

				if (fireSleepCount == 10)
				{
					fireSleepCount = -1;

					if (list->direction == 0)	// Spara verso il basso
					{
						
					}
					else if (list->direction == 1)	// Spara verso l'alto
					{
						
					}
					else if (list->direction == 2)	// Spara verso destra
					{
						
					}
					else if (list->direction == 3)	// Spara verso sinistra
					{
						
					}
				}

				break;
			}
		}

		PrintAt(list->x + 1, list->y + 1, s);
		list = list->nextEnemy;
	}
}

bool Enemy::enemyHandler(Player player, Bullet bullet)
{
	enemyPosition head = enemies, previousNode = enemies, analyzedNode = enemies;

	while (analyzedNode != NULL)
	{
		if ((player.getX() == analyzedNode->x) && (player.getY() == analyzedNode->y))		// Giocatore colpito da un nemico
			return true;
		else if ((bullet.getX() == analyzedNode->x) && (bullet.getY() == analyzedNode->y))		// Nemico colpito da un proiettile
		{
			if (analyzedNode = head)
			{
				head = head->nextEnemy;
				previousNode = head;
			}
			else
			{
				analyzedNode = analyzedNode->nextEnemy;
				previousNode->nextEnemy = analyzedNode;
			
				if (head == previousNode)
					head->nextEnemy = analyzedNode;
			}
		}
		else
		{
			previousNode = analyzedNode;
			analyzedNode = analyzedNode->nextEnemy;
		}
	}

	enemies = head;
	return false;
}