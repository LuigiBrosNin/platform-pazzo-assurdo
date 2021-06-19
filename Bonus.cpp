#include <stdlib.h>

#include "Bonus.h"
#include "Platform.h"
#include "Funzioni.h"

Bonus::Bonus(int x, int y, char symbol)
{
	this->symbol = '$';
	this->listaBonus = NULL;
	this->num = 0;
}

void Bonus::generateBonus(Platform p, int diff)
{
	/*
	 * - Funzione che genera i bonus di ogni livello -
	 * Vengono generati da 1 a 3 bonus per ogni nuovo livello affrontato dal
	 * giocatore. Per ogni bonus raccolto si ottiene un valore pari alla difficoltà
	 * dell'attuale livello più un valore extra casuale (compreso tra 0 e 5),
	 * il tutto moltiplicato per 10.
	 */

	this->listaBonus = NULL;
	int i = 3;	//int i = (rand() % 2) + 1;			// !! Modifica temporanea (per la visualizzazione costante di tre bonus)
	this->num = i;

	while (i > 0)
	{
		// Generazione di coordinate casuali in cui generare il bonus
		this->x = rand() % p.getWidth();
		this->y = rand() % p.getHeight();

		// Creazione (o meno) effettiva del bonus
		if (p.isThere(x, y) && this->y % 2 == 0)
		{
			BonusList temp = new boon;
			temp->x = x;
			temp->y = y;
			temp->type = rand() % 3;
			if (temp->type == 0) temp->value = ((rand() % 5) + diff) * 10;
			else temp->value = ((rand() % 5) + diff) * 5; //se è un bonus di vite o ammo, il valore è dimezzato
			temp->next = this->listaBonus;
			this->listaBonus= temp;
			i--;
		}
	}
}

int Bonus::getValue(int x, int y)
{
	/*
	 * - Funzione che gestisce la raccolta dei bonus da parte dell'utente -
	 * Se il giocatore raggiunge un dato bonus del livello in cui si trova,
	 * viene memorizzato e restituito come output il valore del suddetto bonus,
	 * rimuovendolo dal livello e quindi dalla lista, creata precedentemente.
	 */

	BonusList papere = NULL, copy = this->listaBonus, tmp =new boon;
	int ret = 0;
	while (copy != NULL) //scorre una copia della lista attuale
	{
		if (copy->x == x && copy->y == y) //se il player si trova nella stessa casella ottiene il valore e non salva le coordinate nella nuova lista
		{
			ret = copy->value;
		}
		else //altrimenti salva il bonus nella nuova lista
		{
			tmp = new boon;
			tmp->value = copy->value;
			tmp->x = copy->x;
			tmp->y = copy->y;
			tmp->type = copy->type;
			tmp->next = papere;
			papere = tmp;
		}
		copy = copy->next;
	}
	this->listaBonus = papere; //assegna la lista di bonus aggiornata alla listaBonus
	return ret;
}

int Bonus::getType(int x, int y) {
	BonusList copy = this->listaBonus;
	int tp = -1;
	while (copy != NULL) //scorre una copia della lista attuale
	{
		if (copy->x == x && copy->y == y) //se il player si trova nella stessa casella ottiene il valore e non salva le coordinate nella nuova lista
		{
			tp = copy->type;
		}
		copy = copy->next;
	}
	return tp;
}

void Bonus::print()
{
	BonusList temp = this->listaBonus;
	
	while (temp != NULL)
	{
		if (temp->type == 0) symbol = '$';
		if (temp->type == 1) symbol = char(3);
		if (temp->type == 2) symbol = '+';
		PrintAt(temp->x + 1, temp->y + 1, symbol);
		temp = temp->next;
	}
}

int Bonus::getNum()
{
	return this->num;
}