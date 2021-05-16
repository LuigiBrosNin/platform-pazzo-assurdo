#pragma once
#include "Entity.h"
#include "Player.h"

class Bullet : public Entity
{
protected:
	bool visible;
public:
	Bullet(int x, int y, char symbol = 'O', bool visible= false);
	void fireB(Player p);
	bool isVisible();
};