#include <stdlib.h>

#include "Enemy.h"
#include "Platform.h"
#include "Funzioni.h"
#include "Bullet.h"

Enemy::Enemy(int x, int y, int type, char symbol) : Entity (x, y, symbol)
{
	this->enemies = NULL;
	this->movementSleepCount = -1;
	this->fireSleepCount = -1;
	this->directionUp = true;
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

				fireSleepCount++;

				if (fireSleepCount == 10)
				{
					fireSleepCount = -1;

					if (list->direction == 0)	// Spara verso il basso
					{
						//list->b.enemyFire(list->x, list->y);
						//schermo.setBullet(list->b);
					}
					else if (list->direction == 1)	// Spara verso l'alto
					{
						//list->b.enemyFire(list->x, list->y);
						//schermo.setBullet(list->b);
					}
					else if (list->direction == 2)	// Spara verso destra
					{
						//list->b.enemyFire(list->x, list->y);
						//schermo.setBullet(list->b);
					}
					else if (list->direction == 3)	// Spara verso sinistra
					{
						//list->b.enemyFire(list->x, list->y);
						//schermo.setBullet(list->b);
					}
				}

				break;

			default:
				break;
			}
		}

		PrintAt(list->x + 1, list->y + 1, s, prevx+1, prevy+1);
		list = list->nextEnemy;
	}
}

bool Enemy::enemyHandler(Player player, Bullet bullet)
{
	enemyPosition updated = NULL, copy = this->enemies, tmp = NULL;
	bool update = false, touched = false;

	/*
	 * Scorro una copia della lista attuale per vedere cosa sta facendo il giocatore:
	 *	- se tocca un nemico da sopra ("saltandoci") questi viene eliminato;
	 *	- se un proiettile sparato tocca un nemico questi viene eliminato;
	 *	- se tocca un nemico da altre direzioni senza sparargli, rimuove una vita.
	 */
	while (copy != NULL)
	{
		if (copy->x == player.getX() && copy->y == player.getY())
		{
			if (player.getPrevy() >= copy->y)	// Controllo se il giocatore tocca il nemico senza caderci da sopra
				touched = true;
			
			update = true;
			copy->type = -1;
		}
		else if (bullet.getX() == copy->x && bullet.getY() == copy->y)	// Controllo del proiettile
		{
			update = true;
			copy->type = -1;
		}

		copy = copy->nextEnemy;
	}

	if (update)		// Aggiornamento della lista dei nemici
	{
		copy = this->enemies;

		while (copy != NULL)
		{
			if (copy->type != -1)
			{
				tmp = new enemy;
				tmp->type = copy->type;
				tmp->x = copy->x;
				tmp->y = copy->y;
				tmp->nextEnemy = updated;
				updated = tmp;
			}

			copy = copy->nextEnemy;
		}

		this->enemies = updated;
	}

	return touched;
}