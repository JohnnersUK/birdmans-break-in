#include "Item.h"

#include <iostream>
#include <fstream>

Item::~Item()
{

}

void Item::init(ASGE::Renderer * renderer, std::string data[])
{
	int i = 0;
	std::ifstream data_file(data[0]);
	std::string line;
	std::string contents[8];
	if (data_file.is_open())
	{
		while (std::getline(data_file, line))
		{
			contents[i] = line;

			if (i < 7)
			{
				i++;
			}
		}
		data_file.close();
	}
	if (!sprite)
	{
		sprite = renderer->createUniqueSprite();
	}
	if (!sprite->loadTexture(contents[0]))
	{
	}

	if (!outline)
	{
		outline = renderer->createUniqueSprite();
	}
	if (!outline->loadTexture(contents[1]))
	{
	}

	label = contents[2];
	combi = contents[3];
	combo = contents[4];

}

void Item::render(ASGE::Renderer * renderer, Player & birdman, POINT cursorPos)
{
	renderer->renderSprite(*sprite, 0.0f);
	if (isActive(birdman))
	{
		renderer->renderSprite(*outline, 0.0f);
	}
}

std::string Item::getLabel()
{
	return label;
}

void Item::setPosition(int new_x, int new_y)
{
	sprite->xPos(new_x);
	sprite->yPos(new_y);

	outline->xPos(new_x);
	outline->yPos(new_y);
}

void Item::setTexture(std::string new_sprite, std::string new_outline)
{
	if (!sprite->loadTexture(new_sprite))
	{

	}
	if (!outline->loadTexture(new_outline))
	{

	}
}

void Item::setLabel(std::string new_label)
{
	label = new_label;
}

void Item::setCombi(std::string new_combi)
{
	combi = new_combi;
}

void Item::setCombo(std::string new_combo)
{
	combo = new_combo;
}
