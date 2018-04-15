#pragma once
#include <string>
#include <atomic>

enum class MouseInput
{
	INVALID = -1,
	DEFAULT = 0,
	LEFT,
	RIGHT,
};

enum class MouseAction
{
	INVALID = -1,
	DEFAULT,
	PRESS,
	RELEASE
};

extern std::atomic<MouseInput> mouse_input;
extern std::atomic<MouseAction> mouse_action;