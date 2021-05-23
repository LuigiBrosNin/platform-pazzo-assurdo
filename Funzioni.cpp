#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Entity.h"
#include "Funzioni.h"
#include "Player.h"
#include "Screen.h"
#include "Platform.h"
#include "Bonus.h"

using namespace std;

#define SPACE 32
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

void Cursore(bool visible)		// Rende invisibile il cursore durante l'esecuzione del programma
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO infoCursore;
	GetConsoleCursorInfo(output, &infoCursore);
	infoCursore.bVisible = visible;
	SetConsoleCursorInfo(output, &infoCursore);
}

void WaitScreen()
{
	while (!_kbhit())		// '_kbhit()' controlla la console per l'input da tastiera
	{
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\tPremi un tasto per iniziare";
		for (int i = 0; i < 3 && !_kbhit(); i++)		// Visualizza i tre puntini fin quando l'utente non preme un tasto
		{
			cout << ".";
			Sleep(300);
		}
		Clear();
	}
}

void Movement(bool* gameOver, Player& p, Screen& schermo)
{
	/*
	 * - Funzione che controlla i tasti premuti dall'utente nell'attuale partita -
	 * Il giocatore 'p' viene passato per riferimento e quindi viene mosso 
	 * all'interno dello 'schermo' grazie a '_kbhit()', che si occupa proprio
	 * di gestire la console per gli input utente.
	 */
	
	Platform plats = schermo.getPlatforms();

	if (!plats.isThere(p.getX(), p.getY()))		// Se il giocatore è su una piattaforma, incrementa la coordinata 'Y' di 2
		p.increaseY(2);

	if (_kbhit())
	{
		char tastoPremuto = _getch();
		
		switch (tastoPremuto)
		{
			// Spostamento a sinistra
			case 'a':
			case 'A':
			case ARROW_LEFT:
				p.decreaseX(1);
			break;
			
			// Spostamento a destra
			case 'd':
			case 'D':
			case ARROW_RIGHT:
				p.increaseX(1);
			break;
			
			// Spostamento in alto
			case ARROW_UP:
			case SPACE:
			case 'w':
			case 'W':
				p.decreaseY(2);
			break;
			
			// Spostamento in basso
			case ARROW_DOWN:
			case 's':
			case 'S':
				p.increaseY(2);
			break;
			
			// Spara proiettile
			case 'e':
			case 'E':
				if (p.fire())	// Se ci sono munizioni, spara
				{
					Bullet b = schermo.getBullet();
					b.fireb(p);
					schermo.setBullet(b);
				}
			break;

			// Uscita dal gioco
			case 'x':
			case 'X':
				*gameOver = true;
			break;
		
			default:
			break;
		}
	}
}

void Handler(int width, int height, bool* gameOver, Player& p, Screen& schermo)
{
	// - Funzione che controlla la "leggittimità" delle azioni del giocatore -

	// Gestione dei limiti orizzontali dello spazio di gioco
	if (p.getX() >= width)
	{
		schermo.nextLevel();
		p.setX(0);
		p.refill();
	}
	else if (p.getX() < 0)
	{
		if (schermo.prevLevel())
			p.setX(width - 1);
		else
			p.setX(0);
	}

	// Gestione dei limiti verticali dello spazio di gioco
	if (p.getY() >= height-1)
		p.setY(height - 2);
	if (p.getY() < 0)
		p.setY(0);

	if (p.getVite() <= 0)
		*gameOver = true;

	// Gestione dei proiettili
	Bullet b = schermo.getBullet();
	b.increaseX(1, width);
	schermo.setBullet(b);

	// Gestione dei nemici
	Enemy e = schermo.getEnemy();
	*gameOver = e.enemyHandler(p, b);
	schermo.setEnemy(e);

	// Gestione dei bonus
	Bonus money = schermo.getBonus();
	p.setPunti(p.getPunti() + money.getValue(p.getX(), p.getY()));
	schermo.setBonus(money);
}

void Clear()		// Pulisce lo schermo
{
	system("cls");
}

void PrintAt(int x, int y, char what)
{
	MoveCursor(x, y);
	cout << what;
}

void MoveCursor(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void PrintInfo(int width, int height, Player p, Screen schermo)
{  
	// - Funzione che stampa le informazioni della partita

	MoveCursor(width + 5, 1);
	cout << "Vite: " << p.getVite();

	MoveCursor(width + 5, 2);
	cout << "Punti: " << p.getPunti();

	MoveCursor(width + 5, 3);
	cout << "Livello: " << schermo.getDifficolta();

	MoveCursor(width + 5, 4);
	cout << "Proiettili: ";
	if (p.getAmmo())
		cout << "1";
	else
		cout << "0";
	
	MoveCursor(width + 5, 5);
	cout << "X: " << p.getX() << " Y: "<< p.getY();
}