#include "Player.h"

Player::Player(int x, int y, char symbol, int punti, int vite, bool ammo) : Entity(x, y, symbol)
{
	this->punti = punti;
	this->vite = vite;
	this->ammo = ammo;
	this->prevy = y;
}

void Player::increaseX(int x)
{
	prevy = this->y;
	Entity::increaseX(x);
}

void Player::decreaseX(int x)
{
	prevy = this->y;
	Entity::decreaseX(x);
}

void Player::increaseY(int y)
{
	prevy = this->y;
	Entity::increaseY(y);
}

void Player::decreaseY(int y)
{
	prevy = this->y;
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

void Player::refill()
{
	ammo = true;
}

void Player::increasePunti(int pt)
{
	if (pt > 0)
		punti += pt;
}

bool Player::decreaseVite(int vt)
{
	if(vt > 0)
		vite -= vt;

	return vite > 0;
}

bool Player::fire()
{
	if (ammo)
	{
		ammo = false;
		return true;
	}

	return false;
}

int Player::getPrevy() {
	return this->prevy;
}