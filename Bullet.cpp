#include "Bullet.h"

using namespace std;

Bullet::Bullet(int x, int y, char symbol, bool visible) : Entity(x, y, symbol) {
	this->visible = visible;
}

void Bullet::fireB(Player p) {
	this->x = p.getX() + 1;
	this->y = p.getY();
	visible = true;
}

bool Bullet::isVisible() {
	return visible;
}