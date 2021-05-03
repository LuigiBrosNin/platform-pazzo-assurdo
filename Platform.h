#pragma once
#include "Entity.h"
class Platform : public Entity
{
protected:
	int width;
	int height;
	int positions[50][10];
public:
	Platform(int x = 0, int y = 0, char symbol = char(223), int wh=50, int he=10);
	void generate(int difficulty); //riempie la matrice delle posizioni con 0 e 1 per segnare piattaforme
	void print(); //stampa il vettore piattaforme nello schermo, metodo di entity sovrascritto
	bool isThere(int x, int y); //ritorna un bool che date le coordinate x e y, ritorna true se sotto quelle coordinate c'è una piattaforma
};

