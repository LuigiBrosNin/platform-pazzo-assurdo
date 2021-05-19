#include <stdlib.h>
#include "Bonus.h"
#include "Platform.h"
#include "Funzioni.h"

Bonus::Bonus(int x, int y, char symbol) {
	this->listaBonus = NULL;
	this->num = 0;
}

void Bonus::generateBonus(Platform p, int diff) {
	this->listaBonus = NULL;
	int i = (rand() % 2) + 1;
	this->num = i;
	while (i > 0) //genera da 1 a 3 bonus per livello
	{
		this->x = rand() % p.getWidth();
		this->y = rand() % p.getHeight();
		if (p.isThere(x, y) && this->y % 2 == 0) {
			BonusList temp = new boon;
			temp->x = x;
			temp->y = y;
			temp->value = ((rand() % 5) + diff) * 10; //ogni bonus ottiene un valore pari alla difficoltà + un valore extra random tra 0 e 5, tutto moltiplicato per 10 cuz why not
			temp->next = this->listaBonus;
			this->listaBonus= temp;
			i--;
		}
	}
}

int Bonus::getValue(int x, int y) { //ritorna il valore del bonus che si trova nelle coordinate date in input e elimina il bonus dalla lista poiché è stato preso dal player
	BonusList head = this->listaBonus, prev = this->listaBonus, tmp;
	int ret = 0;
	while (this->listaBonus != NULL) {
		if (this->listaBonus->x == x && this->listaBonus->y == y) {
			ret = this->listaBonus->value;
			this->num--;
			if (this->listaBonus == head) {
				head = this->listaBonus->next;
				delete this->listaBonus;
				this->listaBonus = head;
			}
			else {
				tmp = this->listaBonus->next;
				delete this->listaBonus;
				this->listaBonus = tmp;
				prev->next = tmp;
			}
		}
		else {
			prev = this->listaBonus;
			this->listaBonus = this->listaBonus->next;
		}
	}
	this->listaBonus = head;
	return ret;
}

void Bonus::print() {
		BonusList temp = this->listaBonus;
		while (temp->next != NULL) //se la lista è/diventa vuota, rompe tutto il programma, need to fix asap but dunno how
		{
			PrintAt(temp->x + 1, temp->y + 1, '$');
			temp = temp->next;
		}
}

int Bonus::getNum() {
	return this->num;
}