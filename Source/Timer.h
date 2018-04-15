#pragma once
#include <string.h>
#include <Engine\Renderer.h>
class Timer
{
public:
	Timer();
	~Timer();

	void convert();
	void setCountdown(int getCountdown);

	void render(ASGE::Renderer* renderer);


private:
	int countdown;
	int min;
	int sec;
	std::string strSec;
	std::string strMin;
	std::string display;
};