#include "SmlStreet.h"
#include "Input.h"
#include "GameStates.h"

SmlStreet::~SmlStreet()
{
}

bool SmlStreet::init(ASGE::Renderer * renderer)
{
	backdrop = renderer->createUniqueSprite();
	if (!backdrop->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\Scene_3_Background.png"))
	{
		return false;
	}

	std::string data[3];
	data[0] = ".\\Resources\\Drain.txt";
	drain.init(renderer, &data[0]);

	data[1] = ".\\Resources\\Street_Booth.txt";
	stool.init(renderer, &data[1]);

	ttr.init(renderer, 1.5708, Scenes::THEATER);
	aw2.init(renderer, 4.71239, Scenes::ALLEYWAY2, 50);
	ttr.setActive(true);
	aw2.setActive(true);

	rend = renderer;

	return true;
}

void SmlStreet::update(Player & birdman, std::vector<Item*> inventory)
{
	hwnd = GetForegroundWindow();

	GetCursorPos(&cursorPosition);
	ScreenToClient(hwnd, &cursorPosition);

	birdman.update(cursorPosition);
	processInputs(birdman, inventory);
}

void SmlStreet::processInputs(Player & birdman, std::vector<Item*> inventory)
{
	if (cursorPosition.x > ttr.getXPos() && cursorPosition.x < ttr.getXPos() + 128)
	{
		if (cursorPosition.y > ttr.getYPos() && cursorPosition.y < ttr.getYPos() + 128)
		{
			ttr.setMouseOver(true);
		}
	}
	else
	{
		ttr.setMouseOver(false);
	}
	if (cursorPosition.x > aw2.getXPos() && cursorPosition.x < aw2.getXPos() + 128)
	{
		if (cursorPosition.y > aw2.getYPos() && cursorPosition.y < aw2.getYPos() + 128)
		{
			aw2.setMouseOver(true);
		}
	}
	else
	{
		aw2.setMouseOver(false);
	}

	if (mouse_input == MouseInput::RIGHT && mouse_action == MouseAction::RELEASE)
	{
		birdman.setTargetPos(cursorPosition.x - 75);

	}
	if (mouse_input == MouseInput::LEFT && mouse_action == MouseAction::PRESS)
	{
		if (drain.checkCollision(cursorPosition, rend, inventory) && !drain.checkComplete() && drain.isActive(birdman))
		{
			drain.trade(rend, inventory);

		}
		if (stool.checkCollision(cursorPosition, rend, inventory) && !stool.checkComplete() && stool.isActive(birdman))
		{
			stool.trade(rend, inventory);
		}
		
		if (ttr.getMouseOver() && ttr.getActive())
		{
			ttr.changeScene();
		}
		if (aw2.getMouseOver() && aw2.getActive())
		{
			aw2.changeScene();
		}

		mouse_input = MouseInput::DEFAULT;
	}

	if (mouse_action == MouseAction::RELEASE)
	{
		mouse_input = MouseInput::DEFAULT;
	}
}

void SmlStreet::render(ASGE::Renderer * renderer, Player & birdman)
{
	renderer->renderSprite(*backdrop, 2.0f);

	drain.render(renderer, birdman, cursorPosition);
	stool.render(renderer, birdman, cursorPosition);
	ttr.render(renderer);
	aw2.render(renderer);
}
