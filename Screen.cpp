#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Screen.h"
#include "Entity.h"
#include "Player.h"
#include "Funzioni.h"
#include "Bullet.h"

using namespace std;

Screen::Screen(int width, int height, int difficolta)
{
	this->width = width;
	this->height = height;
	this->difficolta = difficolta-1;	// ('-1' perchè quando viene generato il livello la difficoltà viene incrementata di 1)
	level = generateLevel(difficolta);
	srand((int)time(0));
}

p_livello Screen::generateLevel(int difficolta)
{
	// - Funzione che genera i contenuti del livello attuale -

	p_livello ret = new livello;
	ret->next = NULL;
	ret->prev = NULL;

	/*
		qua in mezzo ci va tutta la generazione dell'array di nemici, bonus e piattaforme
		va implementata anche la generazione basata sulla difficoltà
	*/
	//ret->e = Entity(rand() % width, rand() % height, 'U');
	ret->p = Platform();
	ret->p.generate(difficolta);
	ret->b = Bullet();
	ret->enemiesList = Enemy();
	ret->enemiesList.generateEnemies((difficolta / 2) + 1, ret->p);
	ret->money = Bonus();
	ret->money.generateBonus(ret->p, difficolta);
	//ret->e = Entity();

	this->difficolta++;
	return ret;
}

void Screen::nextLevel()
{
	// - Funzione che permette la visualizzazione "in avanti" di un livello precedentemente generato -
	Clear();
	if (level->next != NULL)
		level = level->next;
	else
	{
		p_livello tmp = generateLevel(difficolta);
		tmp->prev = level;
		level->next = tmp;
		level = level->next;
	}
}

bool Screen::prevLevel()
{
	// - Funzione che permette la visualizzazione "all'indietro" di un livello precedentemente generato -
	Clear();
	if (level->prev != NULL)
	{
		level = level->prev;
		return true;
	}
	else
		return false;
}

void Screen::print()
{
	// - Funzione che stampa lo spazio di gioco

	PrintAt(0, 0, (char)201);

	for (int i = 0; i < width; i++)
		PrintAt(i+1, 0, (char)205);

	PrintAt(width+1, 0, (char)187);

	for (int i = 0; i < height; i++)
	{
		PrintAt(0, i+1, (char)186);
		PrintAt(width+1, i+1, (char)186);
	}

	cout << endl << (char)200;

	for (int i = 0; i < width; i++)
		cout << char(205);

	cout << (char)188;

	level->money.print();

	level->p.print();
	level->enemiesList.print(level->p);
	level->b.print();
}

int Screen::getDifficolta()
{
	return difficolta;
}

void Screen::setDifficolta(int diff)
{
	difficolta = diff;
}

Platform Screen::getPlatforms()
{
	return level->p;
}

Bullet Screen::getBullet()
{
	return level->b;
}

void Screen::setBullet(Bullet b) 
{
	this->level->b = b;
}

Bonus Screen::getBonus()
{
	return level->money;
}

void Screen::setBonus(Bonus b)
{
	this->level->money = b;
}

Enemy Screen::getEnemy()
{
	return level->enemiesList;
}

void Screen::setEnemy(Enemy e)
{
	this->level->enemiesList = e;
}