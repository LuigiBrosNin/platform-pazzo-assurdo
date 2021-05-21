#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Entity.h"
#include "Funzioni.h"

using namespace std;

Entity::Entity(int x, int y, char symbol)
{
	defaultX = x;
	defaultY = y;

	this->x = x;
	this->y = y;
	this->symbol = symbol;
}

int Entity::getX()
{
	return x;
}

int Entity::getY()
{
	return y;
}

void Entity::setX(int x)
{
	this->x = x;
}

void Entity::setY(int y)
{
	if (y % 2 == 0)
		this->y = y;
	else
		this->y = y - 1;
}

void Entity::increaseX(int x)
{
	if (x > 0)
		this->x += x;
}

void Entity::increaseY(int y)
{
	if (y > 0)
		this->y += y;
}

void Entity::decreaseX(int x)
{
	if (x > 0)
		this->x -= x;
}

void Entity::decreaseY(int y)
{
	if (y > 0)
		this->y -= y;
}

void Entity::moveTo(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Entity::print()	// Sposta il cursore nel punto preciso in cui bisogna stampare un carattere
{		
	PrintAt(x+1, y+1, symbol);	// Stampa alla cordinata 'X + 1' o 'Y + 1' perchè la riga 0 e la colonna 0 sono usate per stampare i bordi di gioco
}