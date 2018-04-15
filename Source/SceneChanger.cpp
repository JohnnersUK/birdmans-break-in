#include "SceneChanger.h"

void SceneChanger::init(ASGE::Renderer* renderer, float rot, Scenes scene, int xpos)
{
	float width = 128;
	float height = 128;
	sprite = renderer->createUniqueSprite();
	if (!sprite->loadTexture(".\\Resources\\Textures\\Sprites\\Arrow.png"))
	{
	}

	sprite->dimensions(width, height);
	sprite->xPos(xpos);
	sprite->yPos(200);
	sprite->rotationInRadians(rot);

	outline = renderer->createUniqueSprite();
	if (!outline->loadTexture(".\\Resources\\Textures\\Sprites\\Arrow_Outline.png"))
	{
	}

	outline->dimensions(width, height);
	outline->xPos(xpos);
	outline->yPos(200);
	outline->rotationInRadians(rot);

	next_scene = scene;
}

void SceneChanger::render(ASGE::Renderer * renderer)
{
	if (active)
	{
		renderer->renderSprite(*sprite, 0.5f);
		if (mouse_over)
		{
			renderer->renderSprite(*outline, 0.4f);
		}
	}
}

void SceneChanger::changeScene()
{
	//Sets the global current scene to the scene passed during initalization
	current_scene = next_scene;
}

bool SceneChanger::getActive()
{
	return active;
}

void SceneChanger::setActive(bool new_active)
{
	active = new_active;
}

bool SceneChanger::getMouseOver()
{
	return mouse_over;
}

void SceneChanger::setMouseOver(bool new_mouse_over)
{
	mouse_over = new_mouse_over;
}

int SceneChanger::getXPos()
{
	return sprite->xPos();
}

int SceneChanger::getYPos()
{
	return sprite->yPos();
}
