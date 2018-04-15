#include "GameStates.h"
std::atomic<States> current_state = States::MAIN;
std::atomic<Scenes> current_scene = Scenes::ALLEYWAY;