#pragma once
#include "Entity.h"
#include "Player.h"
class Bullet :
    public Entity
{
protected:
    bool visible;
public:
    Bullet(int x=0, int y=0, char symbol = ' ', bool visible = false);
    bool isVisible();
    void fireb(Player p);
    void increaseX(int x,int width);
};

