#pragma once
#include "Entity.h"
struct livello{
	livello *next;
	livello *prev;
	Entity e;
	//TODO: array di Platform, array di Enemy, array di Bonus (Enemy e Bonus vanno generati sulle coordinate dove c'è già una platform, in modo da renderli raggiungibili dal player)
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
};


