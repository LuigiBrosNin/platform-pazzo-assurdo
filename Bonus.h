#pragma once
#include "Entity.h"
#include "Platform.h"

struct boon
{
	int x;
	int y;
	int value;	// valore in punteggio del bonus
	boon* next;
};

typedef boon* BonusList;

class Bonus : public Entity
{
protected:
	BonusList listaBonus;
	int num;
public:
	Bonus(int x = 0, int y = 0, char symbol = '$');
	void generateBonus(Platform p, int diff);
	int getValue(int x, int y);//ritorna il valore del bonus che si trova nelle coordinate date in input e elimina il bonus dalla lista poiché è stato preso dal player
	void print();
	int getNum();
};

