#include "Player.h"

Player::Player(int x, int y, char symbol, int punti, int vite, int ammo) : Entity(x, y, symbol)
{
	this->punti = punti;
	this->vite = vite;
	this->ammo = ammo;
	this->prevy = y;
}

void Player::increaseX(int x)
{
	prevy = this->y;
	prevx = this->x;
	Entity::increaseX(x);
}

void Player::decreaseX(int x)
{
	prevy = this->y;
	prevx = this->x;
	Entity::decreaseX(x);
}

void Player::increaseY(int y)
{
	prevy = this->y;
	prevx = this->x;
	Entity::increaseY(y);
}

void Player::decreaseY(int y)
{
	prevy = this->y;
	prevx = this->x;
	Entity::decreaseY(y);
}

int Player::getPunti()
{
	return punti;
}

void Player::setPunti(int pt)
{
	punti = pt;
}

int Player::getVite()
{
	return vite;
}

void Player::setVite(int vt)
{
	vite = vt;
}

bool Player::getAmmo()
{
	return ammo;
}

void Player::addAmmo(int n)
{
	ammo += n;
}

void Player::increasePunti(int pt)
{
	if (pt > 0)
		punti += pt;
}

void Player::decreaseVite(int vt)
{
	if (vt > 0)
		vite -= vt;
}

bool Player::fire()
{
	if (ammo > 0)
	{
		ammo -= 1;
		return true;
	}

	return false;
}

int Player::getPrevy() {
	return this->prevy;
}