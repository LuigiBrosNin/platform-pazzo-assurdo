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

using namespace std;
#define SPACE 32
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

void Cursore(bool visible)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO infoCursore;
	GetConsoleCursorInfo(output, &infoCursore);
	infoCursore.bVisible = visible;
	SetConsoleCursorInfo(output, &infoCursore);
}

void Movement(bool* gameOver, Player& p,Screen& schermo) {		//passo p per riferimento in modo da poterla modificare
	Platform plats = schermo.getPlatforms();
	if (!plats.isThere(p.getX(), p.getY())) {//statement che si occupa di controllare se il giocatore è su una piattaforma
		p.increaseY(2);
	}
	if (_kbhit())
	{
		//salvo il tasto che è stato premuto
		char tastoPremuto = _getch();
		switch (tastoPremuto)
		{
			//movimento a sx
		case 'a':
		case 'A':
		case ARROW_LEFT:
			p.decreaseX(1);
			break;
			//movimento a dx
		case 'd':
		case 'D':
		case ARROW_RIGHT:
			p.increaseX(1);
			break;
			//movimento in su
		case ARROW_UP:
		case SPACE:
		case 'w':
		case 'W':
			p.decreaseY(2);
			break;
			//movimento in giù
		case ARROW_DOWN:
		case 's':
		case 'S':
			p.increaseY(2);
			break;
			//tasto X per terminare il programma
		case 'x':
		case 'X':
			*gameOver = true;
			break;
			//tasto per sparare
		case 'e':
		case 'E':
			if (p.fire()) {
				Bullet b = schermo.getBullet();
				b.fireb(p);
				schermo.setBullet(b);
			}
			break;
		default:
			break;
		}
	}
}

void Handler(int width, int height, bool* gameOver, Player& p, Screen& schermo) {
	//gestione movimento orizzontale
	if (p.getX() >= width) {
		schermo.nextLevel();
		p.setX(0);
		p.refill();
	}
	else if (p.getX() < 0) {
		bool esistePrec = schermo.prevLevel();
		if (esistePrec) {
			p.setX(width - 1);
		}
		else
			p.setX(0);
	}
	//gestione movimento verticale
	if (p.getY() >= height-1)
		p.setY(height - 2);
	if (p.getY() < 0)
		p.setY(0);
	if (p.getVite() <= 0)
		*gameOver = true;
	//gestione movement del bullet
	Bullet b = schermo.getBullet();
	b.increaseX(1, width);
	schermo.setBullet(b);
}

void Clear() {
	system("cls");
}

void WaitScreen() {
	while (!_kbhit()) {
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\tPremi un tasto per iniziare";
		for (int i = 0; i < 3 && !_kbhit(); i++)
		{
			cout << ".";
			Sleep(300);
		}
		Clear();
	}
}

void PrintAt(int x, int y, char what) {
	MoveCursor(x, y);
	cout << what;
}
void MoveCursor(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
void PrintInfo(int width, int height, Player p, Screen schermo) {  //funzione per stampare casella con informazioni di base sulla partita
	MoveCursor(width + 5, 1);
	cout << "Vite: " << p.getVite();
	MoveCursor(width + 5, 2);
	cout << "Punti: " << p.getPunti();
	MoveCursor(width + 5, 3);
	cout << "Livello: " << schermo.getDifficolta();
	MoveCursor(width + 5, 4);
	cout << "Ammo: ";
	if (p.getAmmo()) cout << "1";
	else cout << "0";
	MoveCursor(width + 5, 5);
	cout << "X: " << p.getX() << " Y: "<< p.getY();

}
