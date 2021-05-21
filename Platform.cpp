#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Platform.h"
#include "Funzioni.h"

Platform::Platform(int x, int y, char symbol, int wh, int he) : Entity(x, y, symbol)
{
	this->height = int(he/2);		// Le piattaforme possono essere generate solo in righe alternate
	this->width = wh;

	for (int i = 0; i < height; i++)	// Inizializzazione della matrice contenente le piattaforme generate
		for (int j = 0; j < width; j++)
			this->positions[j][i] = 0;
}

void Platform::generate(int difficulty)
{
	// - Funzione che genera le piattaforme di una riga secondo la difficoltà del livello -

	srand((int)time(0));
	difficulty = int(difficulty / 3);		// ?
	int count = 0;

	for (int i = 0; i < width; i++)
		positions[i][height - 1] = 1;		// Genera una "piattaforma unica" per il pavimento

	for (int he = 0; he < this->height-1; he++)
	{
		while (count < width)
		{
			for (int i = 0; i < (rand() % 50) - difficulty;i++)		// Genera una piattaforma di lunghezza casuale
			{
				if (count < width)
				{
					positions[count][he] = 1;
					count++;
				}
			}

			for (int i = 0; i < (rand() % 2) + difficulty + 1; i++)		// Genera uno spazio vuoto di lunghezza casuale
			{
				if (count < width)
				{
					positions[count][he] = 0;
					count++;
				}
			}
		}

		count = 0;		// Finita la riga, azzero il contatore
	}
}

void Platform::print() 
{
	for (int he = 0; he < height; he++) 
		for (int wh = 0; wh < width; wh++)
			if (positions[wh][he] == 1)
				PrintAt(wh+1, (he*2+1)+1, this->symbol);	// Il '[...] + 1' è il già citato offset per adattare la matrice allo schermo
}

bool Platform::isThere(int x, int y)	// Informa se l'entità generata in una data coordinata si trova su una piattaforma
{
	if (positions[x][y / 2] == 1)
		return true;
	else
		return false;
}

int Platform::getWidth()
{
	return this->width;
}

int Platform::getHeight()
{
	return this->height*2;
}