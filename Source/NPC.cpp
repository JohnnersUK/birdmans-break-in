#include "NPC.h"

#include <iostream>
#include <fstream>
#include <string>

NPC::~NPC()
{

}

void NPC::init(ASGE::Renderer * renderer, std::string data[])
{
	int i = 0;

	//Read in from the data fle passed into this function in data[0]
	std::ifstream data_file(data[0]);
	std::string line;
	std::string contents[10];

	if (data_file.is_open())
	{
		while (std::getline(data_file, line))
		{
			contents[i] = line;

			if (i < 9)
			{
				i++;
			}
		}
		data_file.close();
	}

	//Use said data to initialize the class
	sprite = renderer->createUniqueSprite();
	if (!sprite->loadTexture(contents[0]))
	{

	}

	float width = std::stof(contents[2]);
	float height = std::stof(contents[3]);

	sprite->dimensions(width, height);
	sprite->xPos(std::stoi(contents[8]));
	sprite->yPos(std::stoi(contents[9]));

	outline = renderer->createUniqueSprite();
	if (!outline->loadTexture(contents[1]))
	{

	}
	outline->xPos(std::stoi(contents[8]) - 5);
	outline->yPos(std::stoi(contents[9]) - 5);
	outline->dimensions(width, height);

	text = contents[4];
	clue = contents[5];
	take = contents[6];
	give = contents[7];

	setXPos(std::stoi(contents[8]));
	setYPos(std::stoi(contents[9]));
}

void NPC::render(ASGE::Renderer * renderer, Player & birdman, POINT cursorPos)
{
	//Render the sprite
	renderer->renderSprite(*sprite, 1.5f);
	if (isActive(birdman) && !checkComplete())
	{
		//If the player is close render the outline
		renderer->renderSprite(*outline, 1.4f);
	}

	if (cursorPos.x > sprite->xPos() && cursorPos.x < sprite->xPos() + sprite->width() && isActive(birdman))
	{

		//If the players mouse is hovering over then print the text

		renderer->renderText(text, sprite->xPos() - (text.length()*2.5), sprite->yPos() - 10, 1.25, ASGE::COLOURS::BLACK);

	}
}

void NPC::trade(ASGE::Renderer* renderer, std::vector<Item*> inventory)
{
	bool traded = false;

	for (int i = 0; i < 6; i++)
	{
		/*	Cycle through the players inventory
		*	If they have the item of interest take it
		*	Replace it with the five item
		*/
		if (inventory[i]->getLabel() == take)
		{
			if (give == "Nothing")
			{
				text = "Thanks Birdman!";
			}
			else
			{
				text = "You gained a " + give + "!";
			}
			std::string data[1];
			data[0] = ".\\Resources\\" + give + ".txt";

			//	Add/take item
			inventory[i]->init(renderer, data);
			inventory[i]->setPosition(70 + i * 64, 600);
			complete = true;
			traded = true;
			return;
		}
	}

	if (traded == false)
	{
		/* If the trade failed the player is doing something wrong
		*	Give them a helpful clue
		*/
		text = clue;
	}
}

bool NPC::checkCollision(POINT cursorPos, ASGE::Renderer * renderer, std::vector<Item*> inventory)
{
	if (cursorPos.x > sprite->xPos() - 200 && cursorPos.x < sprite->xPos() + 200)
	{
		return true;
	}
	return false;
}

bool NPC::checkComplete()
{
	return complete;
}

void NPC::setTexture(std::string dir)
{
	if (sprite->loadTexture(dir))
	{

	}
}
