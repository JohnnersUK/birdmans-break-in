#pragma once
#include <vector>

#include <Engine\OGLGame.h>
#include <Engine\Sprite.h>
#include <irrKlang.h>

#include "Alleyway.h"
#include "Alleyway2.h"
#include "SmlStreet.h"
#include "Theatre.h"
#include "Levels.h"
#include "Item.h"
#include "Timer.h"
namespace ASGE {
	struct GameTime;
}
namespace irrklang {
	class ISoundEngine;
}
/**
*  BirdmanTheGame is the main entrypoint into the game.
*  It is based on the ASGE framework and makes use of
*  the OGLGame class. This allows the rendering and
*  input initialisation to be handled easily and without
*  fuss. The game logic responsible for updating and
*  rendering the game starts here.
*/
class BirdmanTheGame 
	: public ASGE::OGLGame
{
public:
	
	/**
	*  Default constructor for game.
	*/
	BirdmanTheGame() = default;
	
	/**
	*  Destructor for game.
	*  Make sure to clean up any dynamically allocated
	*  memory inside the game's destructor. For example
	*  game fonts need to be deallocated.
	*/ 
	~BirdmanTheGame();

	/**
	*  The initialisation of the game.
	*  Both the game's initialisation and the API setup
	*  should be performed inside this function. Once the
	*  API is up and running the input system can register
	*  callback functions when certain events happen.
	*/ 
	virtual bool init() override;
	
private:
	/**
	*  The simulation for the game.
	*  The objects in the game need to updated or simulated
	*  over time. Use this function to decouple the render
	*  phases from the simulation.
	*  @param us The ms time between frames and running time
	*  @see GameTime
	*/
	virtual void update(const ASGE::GameTime& ms) override;
	
	/**
	*  The rendering of the game.
	*  This function gets called after the game world has
	*  been updated. Ensure all your objects are in a sane
	*  simulated state before calling this function.
	*  @param us The delta time between frames and running time
	*  @see GameTime
	*/
	virtual void render(const ASGE::GameTime& ms) override;

	void renderInventory();
	/**
	*  The key handling function for the game.
	*  Key inputs will be delivered and handled within this function.
	*  Make a decision whether to process the input immediately
	*  or whether to generate a queue of actions that are then
	*  processed at the beginning of the game update loop.
	*  @param data They key event and its related data.
	*  @see SharedEventData
	*/
	void keyHandler(const ASGE::SharedEventData data);

	void clickHandler(const ASGE::SharedEventData data);

	void sceneHandler();

	bool initAudioEngine();
	

private:
	int click_handler_id = -1;
	int key_handler_id = -1;  /**< Input Callback ID.
							  The callback ID assigned by the game engine. */
	int currentScene = 1;
	int x;
	int returnCode;
	int countdown;
	int time;

	float count = 0;

	bool hasClicked = false;
	bool music = false;

	std::unique_ptr<irrklang::ISoundEngine> audio_engine =
		nullptr;
	irrklang::ISoundSource *Music;
	irrklang::ISoundSource *Click;

	std::unique_ptr<ASGE::Sprite> backdrop = nullptr;
	
	std::unique_ptr<ASGE::Sprite> UI = nullptr;
	std::unique_ptr<ASGE::Sprite> Cursor = nullptr;

	std::vector<Level*> level;
	std::vector<Item*> inventory;

	Level *currentLevel;
	Timer timer;
	Player birdman;
	Alleyway alleyway;
	Alleyway2 alleyway2;
	SmlStreet smlStreet;
	Theatre theatre;
	Scenes old_scene = Scenes::ALLEYWAY;

	POINT cursorPosition;
	HWND hwnd;

};