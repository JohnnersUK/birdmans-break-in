#include "Alleyway2.h"
#include "Input.h"
#include "GameStates.h"

Alleyway2::~Alleyway2()
{
}

bool Alleyway2::init(ASGE::Renderer* renderer)
{
	backdrop = renderer->createUniqueSprite();
	if (!backdrop->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\Scene_3_Background.png"))
	{
		return false;
	}

	std::string data[4];
	data[0] = ".\\Resources\\Bin_2.txt";
	bin.init(renderer, &data[0]);

	data[1] = ".\\Resources\\Fan.txt";
	fan.init(renderer, &data[1]);

	data[2] = ".\\Resources\\Fire_Escape.txt";
	fire_escape.init(renderer, &data[2]);

	data[3] = ".\\Resources\\hobo.txt";
	hobo.init(renderer, &data[3]);

	ss.init(renderer, 1.5708, Scenes::SMLSTREET);
	aw.init(renderer, 4.71239, Scenes::ALLEYWAY, 50);
	aw.setActive(true);

	rend = renderer;

	return true;
}

void Alleyway2::update(Player &birdman, std::vector<Item*> inventory)
{
	hwnd = GetForegroundWindow();

	GetCursorPos(&cursorPosition);
	ScreenToClient(hwnd, &cursorPosition);

	birdman.update(cursorPosition);
	processInputs(birdman, inventory);

	if (fan.checkComplete())
	{
		ss.setActive(true);
	}

	if (hobo.checkComplete())
	{
		birdman.setTexture(".\\Resources\\Textures\\Sprites\\Characters\\Birdman_Sprite_Clothed.png");
		hobo.setTexture(".\\Resources\\Textures\\Sprites\\Characters\\Homeless_Guy_Naked.png");
	}
}

void Alleyway2::processInputs(Player &birdman, std::vector<Item*> inventory)
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
	if (cursorPosition.x > aw.getXPos() && cursorPosition.x < aw.getXPos() + 128)
	{
		if (cursorPosition.y > aw.getYPos() && cursorPosition.y < aw.getYPos() + 128)
		{
			aw.setMouseOver(true);
		}
	}
	else
	{
		aw.setMouseOver(false);
	}

	if (mouse_input == MouseInput::RIGHT && mouse_action == MouseAction::RELEASE)
	{
		birdman.setTargetPos(cursorPosition.x - 75);

	}
	if (mouse_input == MouseInput::LEFT && mouse_action == MouseAction::PRESS)
	{
		mouse_input = MouseInput::DEFAULT;
		if (bin.checkCollision(cursorPosition, rend, inventory) && !bin.checkComplete() && bin.isActive(birdman))
		{
			bin.trade(rend, inventory);
		}
		if (fan.checkCollision(cursorPosition, rend, inventory) && !fan.checkComplete() && fan.isActive(birdman))
		{
			fan.trade(rend, inventory);
		}
		if (bin.checkCollision(cursorPosition, rend, inventory) && !bin.checkComplete() && bin.isActive(birdman))
		{
			bin.trade(rend, inventory);
		}
		if (hobo.checkCollision(cursorPosition, rend, inventory) && !hobo.checkComplete() && hobo.isActive(birdman))
		{
			hobo.trade(rend, inventory);
		}

		if (ss.getMouseOver() && ss.getActive())
		{
			ss.changeScene();
		}
		if (aw.getMouseOver() && aw.getActive())
		{
			aw.changeScene();
		}
	}

	if (mouse_action == MouseAction::RELEASE)
	{
		mouse_input = MouseInput::DEFAULT;
	}
}

void Alleyway2::render(ASGE::Renderer* renderer, Player &birdman)
{
	renderer->renderSprite(*backdrop, 2.0f);

	bin.render(renderer, birdman, cursorPosition);
	fan.render(renderer, birdman, cursorPosition);
	fire_escape.render(renderer, birdman, cursorPosition);
	hobo.render(renderer, birdman, cursorPosition);
	ss.render(renderer);
	aw.render(renderer);
}
