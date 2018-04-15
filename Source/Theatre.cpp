#include "Theatre.h"
#include "Input.h"
#include "GameStates.h"

Theatre::~Theatre()
{
}

bool Theatre::init(ASGE::Renderer * renderer)
{
	backdrop = renderer->createUniqueSprite();
	if (!backdrop->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\Scene_2_Background.png"))
	{
		return false;
	}

	std::string data[3];

	data[1] = ".\\Resources\\Poster.txt";
	poster.init(renderer, &data[1]);

	data[2] = ".\\Resources\\Bodyguard.txt";
	bodyguard.init(renderer, &data[2]);

	ss.init(renderer, 4.71239, Scenes::SMLSTREET, 50);

	ss.setActive(true);

	rend = renderer;

	return true;
}

void Theatre::update(Player & birdman, std::vector<Item*> inventory)
{
	hwnd = GetForegroundWindow();

	GetCursorPos(&cursorPosition);
	ScreenToClient(hwnd, &cursorPosition);

	birdman.update(cursorPosition);
	processInputs(birdman, inventory);

	if (bodyguard.checkComplete())
	{
		current_state = States::WIN;
	}
}

void Theatre::processInputs(Player & birdman, std::vector<Item*> inventory)
{
	if (cursorPosition.x > ss.getXPos() && cursorPosition.x < ss.getXPos() + 128)
	{
		if (cursorPosition.y > ss.getYPos() && cursorPosition.y < ss.getYPos() + 128)
		{
			ss.setMouseOver(true);
		}
	}
	else
	{
		ss.setMouseOver(false);
	}


	if (mouse_input == MouseInput::RIGHT && mouse_action == MouseAction::RELEASE)
	{
		birdman.setTargetPos(cursorPosition.x - 75);

	}
	if (mouse_input == MouseInput::LEFT && mouse_action == MouseAction::PRESS)
	{
		if (poster.checkCollision(cursorPosition, rend, inventory) && !poster.checkComplete() && poster.isActive(birdman))
		{
			poster.trade(rend, inventory);
		}

		if (bodyguard.checkCollision(cursorPosition, rend, inventory) && !bodyguard.checkComplete() && bodyguard.isActive(birdman))
		{
			bodyguard.trade(rend, inventory);
		}

		mouse_input = MouseInput::DEFAULT;
		if (ss.getMouseOver() && ss.getActive())
		{
			ss.changeScene();
		}
	}

	if (mouse_action == MouseAction::RELEASE)
	{
		mouse_input = MouseInput::DEFAULT;
	}
}

void Theatre::render(ASGE::Renderer * renderer, Player & birdman)
{
	renderer->renderSprite(*backdrop, 2.0f);

	poster.render(renderer, birdman, cursorPosition);
	bodyguard.render(renderer, birdman, cursorPosition);
	ss.render(renderer);
}
