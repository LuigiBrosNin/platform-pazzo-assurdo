#pragma once
#include "Entity.h"
class Platform : public Entity
{
protected:
	int width;
	int height;
	int positions[50][10];
public:
	Platform(int x = 0, int y = 0, char symbol = char(223), int wh=50, int he=10);
	void generate(int difficulty);
	void print();
	bool isThere(int x, int y);
};

