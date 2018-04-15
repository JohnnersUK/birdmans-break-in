#include "Alleyway.h"
#include "Input.h"
#include "GameStates.h"

Alleyway::~Alleyway()
{

}

bool Alleyway::init(ASGE::Renderer* renderer)
{
	backdrop = renderer->createUniqueSprite();
	if (!backdrop->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\Scene_1_Background.png"))
	{
		return false;
	}

	std::string data[3];
	data[0] = ".\\Resources\\Bin.txt";
	bin.init(renderer, &data[0]);

	data[1] = ".\\Resources\\Door_1.txt";
	door.init(renderer, &data[1]);

	data[2] = ".\\Resources\\Keypad.txt";
	keypad.init(renderer, &data[2]);
	
	aw2.init(renderer, 1.5708, Scenes::ALLEYWAY2);
	aw2.setActive(true);

	rend = renderer;

	return true;
}

void Alleyway::update(Player &birdman, std::vector<Item*> inventory)
{
	hwnd = GetForegroundWindow();

	GetCursorPos(&cursorPosition);
	ScreenToClient(hwnd, &cursorPosition);

	birdman.update(cursorPosition);
	processInputs(birdman, inventory);
}

void Alleyway::processInputs(Player &birdman, std::vector<Item*> inventory)
{
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
		mouse_input = MouseInput::DEFAULT;
		if (bin.checkCollision(cursorPosition, rend, inventory) && !bin.checkComplete() && bin.isActive(birdman))
		{
			bin.trade(rend, inventory);
		}
		if (aw2.getMouseOver() && aw2.getActive())
		{
			aw2.changeScene();
		}
	}

	if (mouse_action == MouseAction::RELEASE)
	{
		mouse_input = MouseInput::DEFAULT;
	}
}

void Alleyway::render(ASGE::Renderer* renderer, Player &birdman)
{
	renderer->renderSprite(*backdrop, 2.0f);

	bin.render(renderer, birdman, cursorPosition);
	door.render(renderer, birdman, cursorPosition);
	keypad.render(renderer, birdman, cursorPosition);
	aw2.render(renderer);
}