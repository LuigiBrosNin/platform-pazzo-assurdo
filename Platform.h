#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

#include "Entity.h"

class Platform : public Entity
{
	protected:
		int width;
		int height;
		int positions[50][10];	/*
								 * !!! Warning !!!
								 * Credo che la dimensione della matrice dovrebbe essere resa generale, ovvero adattabile allo schermo che si vuole creare
								 */ 

	public:
		Platform(int x = 0, int y = 0, char symbol = char(223), int wh=50, int he=10);
		void generate(int difficulty);	// Riempie la matrice delle posizioni delle piattaforme con '1' o '0' per identificarne la presenza o meno
		void print();	// Stampa la matrice delle piattaforme (sovrascrivendo il metodo già presente nella classe 'Entity')
		bool isThere(int x, int y);	// Informa se l'entità generata in una data coordinata si trova su una piattaforma
		int getWidth();
		int getHeight();
};