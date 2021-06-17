#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

#include "Entity.h"
#include "Player.h"
#include "Screen.h"

void Cursore(bool visible);	// Imposta la visibilità del cursore
void Movement(bool* gameOver, Player& p,Screen& schermo);	// Gestisce gli input da tastiera
void Handler(int width, int height, bool* gameOver, Player& p, Screen& schermo);	// Gestisce il movimento tra livelli
void PrintInfo(int width, int height, Player p, Screen schermo);	//stampa casella con informazioni di base sulla partita
void Clear();	// Pulisce lo schermo
void WaitScreen();	// Schermata di attesa ad inizio partita
void PrintAt(int x, int y, char what, int prevx=-1, int prevy=-1);
void MoveCursor(int x, int y);