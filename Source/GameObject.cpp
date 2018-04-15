#include "GameObject.h"

GameObject::~GameObject()
{
}

bool GameObject::isActive(Player &birdman)
{
	if (birdman.getxPos() > sprite->xPos() - 200 && birdman.getxPos() < sprite->xPos() + sprite->width() + 200)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int GameObject::getXPos()
{
	return xPos;
}

int GameObject::getYPos()
{
	return yPos;
}


void GameObject::setXPos(int newX)
{
	xPos = newX;
}

void GameObject::setYPos(int newY)
{
	yPos = newY;
}
