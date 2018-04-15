#pragma once
#include <string>
#include <atomic>

enum States
{
	MAIN = 0,
	PLAY,
	GAMEOVER,
	WIN
};

enum Scenes
{
	ALLEYWAY,
	ALLEYWAY2,
	SMLSTREET,
	TSQUARE,
	DINER,
	THEATER
};

extern std::atomic<States> current_state;
extern std::atomic<Scenes> current_scene;