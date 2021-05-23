#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

#include "Entity.h"
#include "Platform.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Bonus.h"

struct livello
{
	livello *next;
	livello *prev;
	Platform p;
	Bullet b;
	Bonus money;
	Enemy enemiesList;
};
typedef livello *p_livello;

class Screen
{
	protected:
		p_livello level;
		int width, height;
		int difficolta;
	public:
		Screen(int width, int height, int difficolta=1);
		p_livello generateLevel(int difficolta);	// Genera i contenuti del livello attuale
		void nextLevel();	// Avanza al livello successivo
		bool prevLevel();	// Ritorna al livello precedente
		void print();	// Stampa il livello
		int getDifficolta();
		void setDifficolta(int diff);
		Platform getPlatforms();
		Bullet getBullet();
		void setBullet(Bullet b);
		Bonus getBonus();
		void setBonus(Bonus b);
		Enemy getEnemy();
		void setEnemy(Enemy e);
};