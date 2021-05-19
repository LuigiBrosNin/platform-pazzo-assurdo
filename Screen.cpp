#include "Screen.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Entity.h"
#include "Player.h"
#include "Funzioni.h"
#include "Bullet.h"

using namespace std;

Screen::Screen(int width, int height, int difficolta) {
	this->width = width;
	this->height = height;
	this->difficolta = difficolta-1;	// -1 perchè quando genera il livello incrementa la difficoltà di 1
	level = generateLevel(difficolta);
	srand((int)time(0));
}
void Screen::nextLevel() {
	if (level->next != NULL) {	//va al livello successivo
		level = level->next;
	}
	else {		//crea un nuovo livello e lo accoda alla lista
		p_livello tmp = generateLevel(difficolta);
		tmp->prev = level;
		level->next = tmp;
		level = level->next;
	}
}
bool Screen::prevLevel() {
	if (level->prev != NULL) {
		level = level->prev;
		return true;
	}
	else {		//arriva al primo livello generato, più in dietro di così non si va
		return false;
	}
}
p_livello Screen::generateLevel(int difficolta) {
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
	ret->enemiesList.generateEnemies(5, ret->p);
	ret->money = Bonus();
	ret->money.generateBonus(ret->p, difficolta);
	//ret->e = Entity();

	this->difficolta++;
	return ret;
}
void Screen::print() {
	//stampa bordi dello schermo
	cout << (char)201;
	for (int i = 0; i < width; i++)
		cout << char(205);
	cout << (char)187 << endl;
	for (int i = 0; i < height; i++) {
		PrintAt(0, i+1, (char)186);
		PrintAt(width+1, i + 1, (char)186);
	}
	cout << endl << (char)200;
	for (int i = 0; i < width; i++)
		cout << char(205);
	cout << (char)188;

	//stampa contenuto dello schermo
	level->b.print();
	level->p.print();
	level->enemiesList.print();
	if (level->money.getNum() > 0) level->money.print();
}
int Screen::getDifficolta() {
	return difficolta;
}
void Screen::setDifficolta(int diff) {
	difficolta = diff;
}
Platform Screen::getPlatforms() {
	return level->p;
}

Bullet Screen::getBullet() {
	return level->b;
}

void Screen::setBullet(Bullet b) 
{
	this->level->b = b;
}

Bonus Screen::getBonus() {
	return level->money;
}

void Screen::setBonus(Bonus b)
{
	this->level->money = b;
}