/*
    INFO:
        Gestione dello schermo  -> X incrementano spostandosi a destra, Y incremento spostandosi in basso. Punto in alto a sx ha coordinate (0,0), in realtà sarebbero (1,1) perchè riga 0 e colonna 0 vengono usate per stampare i bordi di gioco

        Entity                  -> classe generica da cui fare ereditare le varie entità presenti nello spazio di gioco (player, enemies, bonus, ...)
                                -> contiene varie funzioni generiche per ridurre la ridondanza nelle classi figlio (es. modifica della posizione delle entità)

        Screen                  -> costruttore accetta altezza e larghezza, genera la prima schermata di gioco con piattaforme e nemici
                                -> contiene la lista di schermate usata per generare dinamicamente il mondo e tenere traccia in memoria degli schermi precedenti
                                -> metodo print che stampa sia i bordi dello schermo, sia le piattaforme



*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Funzioni.h"
#include "Player.h"
#include "Entity.h"
#include "Screen.h"
using namespace std;


//variabili globali
int width = 50, height = 10; // height != dispari
Player p = Player(0, height-2, '@', 0, 1);
Screen schermo = Screen(width, height);
bool gameOver = false;

int main()
{
    Cursore(false);     //toglie la visibilità del cursore
    WaitScreen();       //schermata di attesa

    while (!gameOver) 
    {
        Clear();

        //gestore movimento e input
        Movement(&gameOver, p, schermo);
        Handler(width, height, &gameOver, p, schermo);

        //stampa
        schermo.print();
        p.print();
        PrintInfo(width, height, p, schermo);
        Sleep(50);
    }

    Clear();
    cout << "GAME OVER";
    
}

