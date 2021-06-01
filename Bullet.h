#pragma once		// Specifica che il compilatore include il file di intestazione una sola volta, durante la compilazione di un file di codice sorgente

#include "Entity.h"
#include "Player.h"

class Bullet : public Entity
{
    protected:
        bool visible;
    public:
        Bullet(int x=0, int y=0, char symbol = ' ', bool visible = false);
        bool isVisible();
        void fireb(Player p);   // "Crea" l'oggetto proiettile 
        void enemyFire(int x, int y);    // "Crea" l'oggetto proiettile per i nemici
        void increaseX(int x,int width);    // Sposta il proiettile
};