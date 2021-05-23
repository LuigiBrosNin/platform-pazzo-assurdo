#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

#include "Entity.h"

class Player : public Entity
{
	protected:
		int punti, vite, prevy;
		bool ammo;

	public:
		Player(int x, int y, char symbol = '@', int punti = 0, int vite = 10, bool ammo = true);
		void increaseX(int x);
		void increaseY(int y);
		void decreaseX(int x);
		void decreaseY(int y);
		int getPunti();
		void setPunti(int pt);
		int getVite();
		void setVite(int vt);
		bool getAmmo();	// Restituisce la quantità di munizioni rimasta
		void refill();	// Aumenta la quantità di munizioni disponibili
		void increasePunti(int pt);
		bool decreaseVite(int vt);
		bool fire();	// Riduce la quantità di munizioni disponibili
		int getPrevy();
};