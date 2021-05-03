#pragma once
#include "Entity.h"
#include "Platform.h"

struct enemy
{
	int x;		// Coordinata X del nemico
	int y;		// Coordinata Y del nemico
	int type;	// Tipo di nemico ('0' = tipo1...)
	enemy* nextEnemy;
};
typedef enemy* enemyPosition;

class Enemy : public Entity
{
	protected:
		enemyPosition enemies;

	public:
		Enemy (int x = -1, int y = -1, int type = -1, char symbol = 'S');
		void generateEnemies (int enemyNumber, Platform generablePositions);
		void print();
};