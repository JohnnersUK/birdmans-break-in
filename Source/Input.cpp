#include "Input.h"

std::atomic<MouseInput> mouse_input = MouseInput::DEFAULT;
std::atomic<MouseAction> mouse_action = MouseAction::DEFAULT;