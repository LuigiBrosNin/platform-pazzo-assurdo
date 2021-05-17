#pragma once
#include "Entity.h"
#include "Platform.h"
#include "Enemy.h"
#include "Bullet.h"

struct livello
{
	livello *next;
	livello *prev;
	Platform p;
	Bullet b;
	//Entity e;
	Enemy enemiesList;
	//TODO: array di Bonus (Enemy e Bonus vanno generati sulle coordinate dove c'è già una platform, in modo da renderli raggiungibili dal player)
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
		void nextLevel();
		bool prevLevel();	//true se esiste un livello precedente, false se non esiste (1° livello)
		p_livello generateLevel(int difficolta);		//genera un livello e lo restituisce
		void print();
		int getDifficolta();
		void setDifficolta(int diff);
		Platform getPlatforms();
		Bullet getBullet();
		void setBullet(Bullet b);
};