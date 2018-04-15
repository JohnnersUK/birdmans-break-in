#include <iostream>
#include "Timer.h"
#include "GameStates.h"

Timer::Timer()
{

}
Timer::~Timer()
{

}

void Timer::setCountdown(int getCountdown)
{
	countdown = getCountdown;
}

void Timer::convert()
{
	if (countdown == 0)
	{
		current_state = States::GAMEOVER;
	}
	min = (int)countdown / 60;
	sec = countdown % 60;
	strSec = std::to_string(sec);
	strMin = std::to_string(min);
	if (sec < 10)
	{
		display = "0" + strMin + ":0" + strSec;
	}
	else
	{
		display = "0" + strMin + ":" + strSec;
	}
	
	
}

void Timer::render(ASGE::Renderer* renderer)
{
	renderer->renderText(display.c_str(), 630, 18);
}
