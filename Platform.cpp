#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Platform.h"
#include "Funzioni.h"
Platform::Platform(int x, int y, char symbol, int wh, int he) : Entity(x, y, symbol) {
	this->height = int(he/2);//perché solo metà dello schermo è occupato dalle piattaforme
	this->width = wh;
}
void Platform::generate(int difficulty) {
	srand((int)time(0));
	difficulty = int(difficulty / 3);
	int count = 0; //tiene conto di a che punto siamo con la generazione delle piattaforme in una singola riga
	for (int he = 0; he < this->height-1; he++)
	{
		while (count < width)
		{
			for (int i = 0; i < (rand() % 50) - difficulty;i++) { //genera 1 piattaforma lunga random
				if (count < width)
				{
					positions[count][he] = 1;
					count++;
				}
			}
			for (int i = 0; i < (rand() % 2) + difficulty + 1; i++) //genera 1 spazio vuoto lungo random
			{
				if (count < width)
				{
					positions[count][he] = 0;
					count++;
				}
			}
		}
		count = 0; //nuova riga, azzero il count
	}
	for (int i = 0; i < width; i++) positions[i][height-1] = 1; //setto il pavimento come 1
}
void Platform::print() 
{
	for (int he = 0; he < height; he++) 
	{
		for (int wh = 0; wh < width; wh++)
		{
			if (positions[wh][he] == 1) {
				PrintAt(wh+1, (he*2+1)+1, this->symbol); //offset per adattare la matrice allo schermo
			}
		}
	}
}

bool Platform::isThere(int x, int y) {
	if (positions[x][y / 2] == 1) return true;//date delle coordinate x e y, controlla se l'entità che si trova in x e y ha una piattaforma sotto
	else return false;
}

int Platform::getWidth()
{
	return this->width;
}

int Platform::getHeight()
{
	return this->height*2;
}