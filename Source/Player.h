#pragma once
#include <string.h>
#include <Engine\Renderer.h>

#include <vector>

#include "AnimSprite.h"

class Player
{
public:
	Player();
	~Player();

	void init(ASGE::Renderer* renderer);
	void update(POINT cursorPos);
	void setTargetPos(int new_target_pos);
	void renderPlayer(ASGE::Renderer* renderer);

	int getxPos();

	void setXPos(int new_xPos);
	void setTexture(std::string dir);

private:
	void move();

	//AnimSprite sprite;
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;
	
	int xPos = 0;
	int yPos = 200;

	int xVel = 0;

	int target_pos = 0;
};