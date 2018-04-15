#pragma once
#include <string.h>
#include <vector>

#include <Engine\Renderer.h>
#include <Engine\Sprite.h>

#include "GameStates.h"


class SceneChanger
{
public:
	SceneChanger() = default;
	~SceneChanger() = default;

	void init(ASGE::Renderer* renderer, float rot, Scenes scene, int xPos = 1100);
	void render(ASGE::Renderer* renderer);

	void changeScene();

	bool getActive();
	void setActive(bool new_active);

	bool getMouseOver();
	void setMouseOver(bool new_mouse_over);

	int getXPos();
	int getYPos();

private:
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;
	std::unique_ptr<ASGE::Sprite> outline = nullptr;
	
	bool active;
	bool mouse_over;

	Scenes next_scene;
};