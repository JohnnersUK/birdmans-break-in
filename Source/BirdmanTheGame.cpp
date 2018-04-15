#include <Engine\InputEvents.h>

#include "BirdmanTheGame.h"
#include "GameFont.h"

#include "Input.h"
#include "GameStates.h"


std::unique_ptr<ASGE::Sprite> gameOver = nullptr;
std::unique_ptr<ASGE::Sprite> winScreen = nullptr;
BirdmanTheGame::~BirdmanTheGame()
{
	this->inputs->unregisterCallback(key_handler_id);
	LoadedGameFont::loaded_fonts.clear();

	level.clear();

	for (int i = 0; i < inventory.size(); i++)
	{
		delete (inventory[i]);
	}
	inventory.clear();
	ShowCursor(TRUE);
}

bool BirdmanTheGame::init()
{
	game_width = 1280;
	game_height = 720;
	
	if (!initAPI(ASGE::Renderer::WindowMode::WINDOWED))
	{
		return false;
	}

	renderer->setWindowTitle("Birdman's Break-in");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::BACK_TO_FRONT);
	//toggleFPS();

	this->inputs->use_threads = false;
	
	key_handler_id = this->inputs->addCallbackFnc(
		ASGE::EventType::E_KEY, &BirdmanTheGame::keyHandler, this);

	click_handler_id = this->inputs->addCallbackFnc(
		ASGE::EventType::E_MOUSE_CLICK, &BirdmanTheGame::clickHandler, this);

	LoadedGameFont::loaded_fonts.reserve(5);
	
//	LoadedGameFont::loaded_fonts.push_back(LoadedGameFont(renderer->loadFont(".\\Resources\\Fonts\\Fipps-Regular.otf", 32), "Main", 32));
	//if(LoadedGameFont::loaded_fonts[0].id == -1)
	//{
		//return false;
	//}

	backdrop = renderer->createUniqueSprite();
	if (!backdrop->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\Main.png"))
	{
		return false;
	}

	gameOver = renderer->createUniqueSprite();
	if (!gameOver->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\gameOver.png"))
	{
		return false;
	}
	winScreen = renderer->createUniqueSprite();
	if (!winScreen->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\WinScreen.png"))
	{
		return false;
	}

	UI = renderer->createUniqueSprite();
	if (!UI->loadTexture(".\\Resources\\Textures\\Sprites\\Scene Backgrounds\\Border.png"));
	{
	}

	Cursor = renderer->createUniqueSprite();
	if (!Cursor->loadTexture(".\\Resources\\Textures\\Sprites\\Cursor.png"));
	{
	}

	level.reserve(5);

	std::string data[1];
	data[0] = ".\\Resources\\Nothing.txt";
	for (int i = 0; i < 7; i++)
	{
		inventory.push_back(new Item);
		inventory[i]->init(renderer.get(), data);
	}

	birdman.init(renderer.get());

	alleyway.init(renderer.get());
	alleyway2.init(renderer.get());
	smlStreet.init(renderer.get());
	theatre.init(renderer.get());

	if (!initAudioEngine())
	{
		return false;
	}
	Music = audio_engine->addSoundSourceFromFile("../../Resources/Sound/Music/BGMusic.wav");
	Music->setDefaultVolume(0.25f);

	currentLevel = &alleyway;
	ShowCursor(FALSE);
	return true;
}

void BirdmanTheGame::update(const ASGE::GameTime& ms)
{
	ms.delta_time.count();
	switch (current_state)
	{
	case States::MAIN:
		if (mouse_input == MouseInput::LEFT || mouse_input == MouseInput::RIGHT)
		{
			current_state = States::PLAY;
			mouse_input = MouseInput::DEFAULT;
		}
		break;
	case States::PLAY:
		sceneHandler();
		currentLevel->update(birdman, inventory);
		time += ms.delta_time.count();
		countdown = 30 - (time/ 1000);
		timer.setCountdown(countdown);
		timer.convert();
		break;
	case States::GAMEOVER:

		break;
	case States::WIN:

		break;
	}
	
	
	hwnd = GetForegroundWindow();

	GetCursorPos(&cursorPosition);
	ScreenToClient(hwnd, &cursorPosition);

	Cursor->xPos(cursorPosition.x - 32);
	Cursor->yPos(cursorPosition.y - 32);

	if (!music)
	{
		audio_engine->play2D(Music, true);
		music = true;
	}

}

void BirdmanTheGame::render(const ASGE::GameTime& ms)
{
	switch (current_state)
	{
	case States::MAIN:
		renderer->renderSprite(*backdrop);
		break;
	case States::PLAY:
		currentLevel->render(renderer.get(), birdman);
		birdman.renderPlayer(renderer.get());
		renderer->renderSprite(*UI, 0.1f);
		timer.render(renderer.get());
		renderInventory();
		timer.render(renderer.get());

		break;
	case States::GAMEOVER:
		renderer->renderSprite(*gameOver);
		break;
	case States::WIN:
		renderer->renderSprite(*winScreen);
		break;

	}

	renderer->renderSprite(*Cursor, 0.0f);
}

void BirdmanTheGame::renderInventory()
{
	for (int i = 0; i < 7; i++)
	{
		//Goes through the inventory. If theres something to render, render it.
		if (inventory[i]->getLabel() != "Nothing")
		{
			inventory[i]->render(renderer.get(), birdman, cursorPosition);
		}
	}
}

void BirdmanTheGame::keyHandler(const ASGE::SharedEventData data)
{
	const ASGE::KeyEvent* key_event =
		static_cast<const ASGE::KeyEvent*>(data.get());

	auto key = key_event->key;
	auto action = key_event->action;

	if (key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}
}

void BirdmanTheGame::clickHandler(const ASGE::SharedEventData data)
{
	const ASGE::ClickEvent* click_event =
		static_cast<const ASGE::ClickEvent*>(data.get());

	auto button = click_event->button;
	auto mAction = click_event->action;

	switch (button)
	{
	case -1:
		mouse_input = MouseInput::DEFAULT;
		break;
	case 0:
		mouse_input = MouseInput::LEFT;
		audio_engine->play2D("../../Resources/Sound/SFX/Click.wav");
		break;
	case 1:
		mouse_input = MouseInput::RIGHT;
		audio_engine->play2D("../../Resources/Sound/SFX/Click.wav");
		break;
	}

	switch (mAction)
	{
	case -1:
		mouse_action = MouseAction::DEFAULT;
		break;
	case 0:
		mouse_action = MouseAction::RELEASE;
		break;
	case 1:
		mouse_action = MouseAction::PRESS;
		break;
	}
}

void BirdmanTheGame::sceneHandler()
{
	if (current_scene != old_scene)
	{
		switch (current_scene)
		{
		case Scenes::ALLEYWAY:
			birdman.setXPos(0);
			birdman.setTargetPos(0);
			currentLevel = &alleyway;
			break;
		case Scenes::ALLEYWAY2:
			birdman.setXPos(0);
			birdman.setTargetPos(0);
			currentLevel = &alleyway2;
			break;
		case Scenes::SMLSTREET:
			birdman.setXPos(0);
			birdman.setTargetPos(0);
			currentLevel = &smlStreet;
			break;
		case Scenes::TSQUARE:
			//currentLevel = &tsquare;
			break;
		case Scenes::DINER:
			//currentLevel = &diner;
			break;
		case Scenes::THEATER:
			birdman.setXPos(0);
			birdman.setTargetPos(0);
			currentLevel = &theatre;
			break;
		}
		old_scene = current_scene;
	}
}

bool BirdmanTheGame::initAudioEngine()
{
	using namespace irrklang;
	audio_engine.reset(createIrrKlangDevice());
	if (!audio_engine)
	{
		// error starting audio engine
		return false;
	}
	return true;
}


