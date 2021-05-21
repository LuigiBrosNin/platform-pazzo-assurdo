#include "Bullet.h"

Bullet::Bullet(int x, int y, char symbol, bool visible) : Entity(x, y, symbol)
{
	this->visible = visible;
}

bool Bullet::isVisible()
{
	return visible;
}

void Bullet::fireb(Player p) 
{
	visible = true;
	this->x = p.getX() + 1;
	this->y = p.getY();
	this->symbol = 'O';
}

void Bullet::increaseX(int x, int width)
{
	if (x > 0 && this->x + x < width && visible)
		this->x += x;
	else
	{
		visible = false;
		symbol = ' ';
	}
}