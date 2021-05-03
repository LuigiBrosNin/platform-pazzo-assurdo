#pragma once
#include "Entity.h"

struct enemy
{
	int x;
	int y;
	int type;	// Tipo di nemico ('0' = tipo1...)
	enemy* nextEnemy;
};
typedef enemy* enemyPosition;

class Enemy : public Entity
{
	protected:
		int type;
		char displayedSymbol;
		enemyPosition enemies;

	public:
		Enemy(int x, int y, int type, char symbol) : Entity(x, y, symbol);
		//Enemy(int enemyNumber, Platform generablePositions, int screenWidth, int screenHeight, char displayedSymbol = 'S');
};
