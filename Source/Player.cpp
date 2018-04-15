#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::init(ASGE::Renderer* renderer)
{
	/*
	*	Non-functional code for the animated sprite
	*	TODO:: fix this
	std::string dir[4];

	dir[0] = ".\\Resources\\Textures\\Sprites\\Birdman_Sprite1.png";
	dir[1] = ".\\Resources\\Textures\\Sprites\\Birdman_Sprite.png";
	dir[2] = ".\\Resources\\Textures\\Sprites\\Birdman_Sprite2.png";

	sprite.init(renderer, 3, dir);
	*/
	sprite = renderer->createUniqueSprite();
	if (sprite->loadTexture(".\\Resources\\Textures\\Sprites\\Birdman_Sprite.png"))
	{

	}
	sprite->xPos(0);
	sprite->yPos(200);
}

void Player::update(POINT cursorPos)
{
	//Calculate where to go
	int diff_pos = xPos - target_pos;

	//Set the velocity of birdman depending on wether the target is to the left or right
	if (diff_pos > 0)
	{
		xVel = -1;
		sprite->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
	}
	else if (diff_pos < 0)
	{
		xVel = 1;
		sprite->setFlipFlags(ASGE::Sprite::FlipFlags::NORMAL);
	}
	else
	{
		xVel = 0;
		//Flip the sprite to follow the mouse
		if (cursorPos.x < xPos)
		{
			sprite->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
		}
		else if (cursorPos.x > xPos)
		{
			sprite->setFlipFlags(ASGE::Sprite::FlipFlags::NORMAL);
		}
	}

	//Change the players position and move them
	xPos += xVel;
	sprite->xPos(xPos);

	/*
	*	More redundant code for the animated sprite
	*	TODO: Fix this too
	sprite.updatePosition(xPos, yPos);
	sprite.updateFrame();
	*/
}

void Player::move()
{

}

void Player::setTargetPos(int new_target_pos)
{
	target_pos = new_target_pos;
}

void Player::renderPlayer(ASGE::Renderer * renderer)
{
	/*
	*	Even more of this stuff
	*	TODO: Fix this three
	sprite.renderSprite(renderer);
	sprite.updateFrame();
	*/
	renderer->renderSprite(*sprite, 1.0f);
}

int Player::getxPos()
{
	return xPos;
}

void Player::setXPos(int new_xPos)
{
	xPos = new_xPos;
}

void Player::setTexture(std::string dir)
{
	if(sprite->loadTexture(dir))
	{

	}
}
