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
	this->height = int(he/2);
	this->width = wh;
}
void Platform::generate(int difficulty) {
	srand((int)time(0));
	int count = 0;
	for (int he = 0; he < this->height-1; he++)
	{
		while (count < width)
		{
			for (int i = 0; i < (rand() % 50) - difficulty;i++) {
				if (count < width)
				{
					positions[count][he] = 1;
					count++;
				}
			}
			for (int i = 0; i < (rand() % 2) + difficulty + 1; i++)
			{
				if (count < width)
				{
					positions[count][he] = 0;
					count++;
				}
			}
		}
		count = 0;
	}
	for (int i = 0; i < width; i++) positions[i][height-1] = 1;
}
void Platform::print() 
{
	for (int he = 0; he < height; he++) 
	{
		for (int wh = 0; wh < width; wh++)
		{
			if (positions[wh][he] == 1) {
				PrintAt(wh+1, (he*2+1)+1, this->symbol);
			}
		}
	}
}

bool Platform::isThere(int x, int y) {
	if (positions[x - 1][y / 2 + 1] == 1) return true;
	else return false;
}