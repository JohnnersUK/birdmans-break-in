#pragma once
#include <Engine\Renderer.h>

#include "NPC.h"
#include "Player.h"
#include "Item.h"

class Level
{
public:

	Level() = default;
	virtual ~Level() = default;

	virtual bool init(ASGE::Renderer* renderer) = 0;
	virtual void update(Player &birdman, std::vector<Item*> inventory) = 0;
	virtual void processInputs(Player &birdman, std::vector<Item*> inventory) = 0;
	virtual void render(ASGE::Renderer* renderer, Player &birdman) = 0;

private:

};
