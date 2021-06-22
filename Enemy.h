#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

#include "Entity.h"
#include "Platform.h"
#include "Player.h"
#include "Bullet.h"

struct enemy
{
	int x;
	int y;
	int type;
	int direction;	// Direzione verso cui si muovera' il nemico ('0' = basso; '1' = alto; '2' =  destra; '3' = sinistra)
	int movementSleepCount_UpDown = -1;
	int movementSleepCount_RightLeft = -1;
	int fireBallX;
	int fireBallY;
	enemy* nextEnemy;
};
typedef enemy* enemyPosition;

class Enemy : public Entity
{
	protected:
		enemyPosition enemies;
		bool directionUp, touched;

	public:
		Enemy (int x = -1, int y = -1, int type = -1, char symbol = 'S');
		void generateEnemies (int enemyNumber, Platform generablePositions);	// Genera i nemici
		void print(Platform generablePositions);
		bool enemyHandler(Player player, Bullet bullet);	// Gestisce le azioni riguardanti i nemici
};