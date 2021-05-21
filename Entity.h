#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

class Entity
{
	protected:
		/*
		 * Le variabili 'deafultX' e 'defaultY' servono per riportare ad una specifica coordinate di default
		 * il giocatore. Ad esempio, durante lo spostamento tra livelli non si sa cosa verrà generato alla
		 * coordinata (X, Y) in cui si trova attualmente il giocatore: se mancasse una piattaforma, tanto
		 * per dire, potrebbe essere utile reimpostarlo alla coordinata di default qui precedentemente definita)
		 */
		int defaultX, defaultY;
		int x, y;
		char symbol;
	public:
		Entity(int x = 0, int y = 0, char symbol='*');
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		void increaseX(int x);
		void increaseY(int y);
		void decreaseX(int x);
		void decreaseY(int y);
		void moveTo(int x, int y);
		void print();	// Sposta il cursore nel punto preciso in cui bisogna stampare un carattere
};