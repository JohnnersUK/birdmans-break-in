#pragma once
#include "Levels.h"

#include <Engine\Sprite.h>
#include <vector>

#include "SceneChanger.h"

class Theatre :
	public Level
{
public:
	Theatre() = default;
	~Theatre();

	virtual bool init(ASGE::Renderer* renderer) override;
	virtual void update(Player &birdman, std::vector<Item*> inventory) override;
	virtual void processInputs(Player &birdman, std::vector<Item*> inventory) override;
	virtual void render(ASGE::Renderer* renderer, Player &birdman) override;

private:
	std::unique_ptr<ASGE::Sprite> backdrop = nullptr;
	std::vector<GameObject*> objects;

	ASGE::Renderer* rend;

	POINT cursorPosition;
	HWND hwnd;

	NPC poster;
	NPC bodyguard;
	SceneChanger ss;

	float count = 0.0f;
};

