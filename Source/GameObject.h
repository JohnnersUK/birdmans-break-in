#pragma once
#include <Engine\Sprite.h>
#include <string.h>

#include "Player.h"

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject();

	virtual void init(ASGE::Renderer * renderer, std::string data[]) = 0;
	virtual void render(ASGE::Renderer * renderer, Player &birdman, POINT cursorPos) = 0;

	bool isActive(Player & birdman);

	int getXPos();
	int getYPos();

	void setXPos(int newX);
	void setYPos(int newY);

protected:
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;
	std::unique_ptr<ASGE::Sprite> outline = nullptr;

	int xPos;
	int yPos;
};
