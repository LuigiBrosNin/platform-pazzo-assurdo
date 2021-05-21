#include <stdlib.h>

#include "Bonus.h"
#include "Platform.h"
#include "Funzioni.h"

Bonus::Bonus(int x, int y, char symbol)
{
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
	int i = 2;	//int i = (rand() % 2) + 1;			// !! Modifica temporanea (per la visualizzazione costante di tre bonus)
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
			temp->value = ((rand() % 5) + diff) * 10;
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

	BonusList head = this->listaBonus, prev = this->listaBonus;
	int ret = 0;

	while (this->listaBonus != NULL)
	{
		/*
		 *	!! Problemi riscontrati:
		 *		1) La testa rimane un problema. Ancora. Pur creando una nuova lista, il bonus rimane al suo posto e, anzi, continua perennemente
		 *         ad incrementare il punteggio. Ho provato con dei flag su ogni condizione (per fare in modo che ad ogni livello venisse ripetuta
		 *		   la cancellazione del primo, del secondo e del terzo bonus solo una volta per ognuna delle ipotesi) e ho provato ad iterare il while
		 *		   per il numero di bonus creati ma non c'è stato nulla da fare (anzi, in quest'ultimo caso sembrava addirittura che 'listaBonus'
		 *		   decidesse di non esistere prima ancora di vivere);
		 *		2) Il terzo caso (eliminazione della coda) non sempre si verifica, non ho capito perché. Spesso capita che esista la testa e "due
		 *		   elementi intermedi" (puoi vederlo dal 'ret' modificato), poche volte che esistano tre elementi distinti
		 * 
		 *		I casi che si verificano sempre sono quelli del 'ret' uguale a uno (costantemente), o almeno in ogni esecuzione che ho testato quello
		 *		c'era sempre (e puoi verificarlo settando 'i = 1', ovviamente), e del 'ret' uguale a due... 
		 */

		if (this->listaBonus->x == x && this->listaBonus->y == y && num != 0)
		{
			//ret = this->listaBonus->value;		// !! Modifica temporanea (istruzione originale)
			this->num--;

			BonusList newList = new boon;

			if (this->listaBonus == head)
			{
				ret = 1;	// !! Modifica temporanea (per la visualizzazione del "tipo" di bonus che si vuole cancellare)
				newList = this->listaBonus->next;
				this->listaBonus = newList;
			}
			else if (prev == head)
			{
				ret = 2;	// !! Modifica temporanea (per la visualizzazione del "tipo" di bonus che si vuole cancellare)
				newList = head;
				newList->next = this->listaBonus->next;
				this->listaBonus = newList;
			}
			else
			{
				ret = 3;	// !! Modifica temporanea (per la visualizzazione del "tipo" di bonus che si vuole cancellare)
				newList = head;
				newList = newList->next;
				newList->next = NULL;
			}
		}
		else
		{
			prev = this->listaBonus;
			this->listaBonus = this->listaBonus->next;
		}
	}

	return ret;
}

void Bonus::print()
{
	BonusList temp = this->listaBonus;
	
	while (temp != NULL)
	{
		PrintAt(temp->x + 1, temp->y + 1, '$');
		temp = temp->next;
	}
}

int Bonus::getNum()
{
	return this->num;
}