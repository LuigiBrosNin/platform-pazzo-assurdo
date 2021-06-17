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
	prevx = -1;
	prevy = -1;
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
	prevx = this->x;
	this->x = x;
}

void Entity::setY(int y)
{
	prevy = this->y;
	if (y % 2 == 0)
		this->y = y;
	else
		this->y = y - 1;
}

void Entity::increaseX(int x)
{
	prevx = this->x;
	if (x > 0)
		this->x += x;
}

void Entity::increaseY(int y)
{
	prevy = this->y;
	if (y > 0)
		this->y += y;
}

void Entity::decreaseX(int x)
{
	prevx = this->x;
	if (x > 0)
		this->x -= x;
}

void Entity::decreaseY(int y)
{
	prevy = this->y;
	if (y > 0)
		this->y -= y;
}

void Entity::moveTo(int x, int y)
{
	prevy = this->y;
	prevx = this->x;
	this->x = x;
	this->y = y;
}

void Entity::print()	// Sposta il cursore nel punto preciso in cui bisogna stampare un carattere
{		
	PrintAt(x+1, y+1, symbol,prevx+1,prevy+1);	// Stampa alla cordinata 'X + 1' o 'Y + 1' perchè la riga 0 e la colonna 0 sono usate per stampare i bordi di gioco
}