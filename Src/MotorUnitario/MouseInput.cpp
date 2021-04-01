#include "MouseInput.h"

std::unique_ptr<MouseInput> MouseInput::instance = nullptr;

MouseInput::MouseInput()
{
}

MouseInput::~MouseInput()
{
}

MouseInput* MouseInput::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new MouseInput());
	}
	return instance.get();
}

void MouseInput::reset()
{
	for (int i = 0; i < 3; i++) {
		_mouseButtonJustUp[i] = false;
		_mouseButtonJustDown[i] = false;
	}
}

void MouseInput::receiveEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_MOUSEMOTION:
		_mousePos[0] = event->motion.x;
		_mousePos[1] = event->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT) {
			_mouseButtonJustDown[LEFT] = true;
			_mouseButtonState[LEFT] = true;
		}
		else if (event->button.button == SDL_BUTTON_MIDDLE) {
			_mouseButtonJustDown[MIDDLE] = true;
			_mouseButtonState[MIDDLE] = true;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT) {
			_mouseButtonJustDown[RIGHT] = true;
			_mouseButtonState[RIGHT] = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == SDL_BUTTON_LEFT) {
			_mouseButtonJustUp[LEFT] = true;
			_mouseButtonState[LEFT] = false;
		}
		else if (event->button.button == SDL_BUTTON_MIDDLE) {
			_mouseButtonJustUp[MIDDLE] = true;
			_mouseButtonState[MIDDLE] = false;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT) {
			_mouseButtonJustUp[RIGHT] = true;
			_mouseButtonState[RIGHT] = false;
		}
		break;
	case SDL_MOUSEWHEEL:
		_mouseWheelDelta = event->wheel.y;
		break;
	}
}
