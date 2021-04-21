#include "MouseInput.h"
#include "SDL_events.h"

std::unique_ptr<MouseInput> MouseInput::instance = nullptr;

void MouseInput::setMouseRelativeMode(bool relative)
{
	SDL_SetRelativeMouseMode((SDL_bool)relative);
}

MouseInput::MouseInput() : _mousePos({ 0.0, 0.0 }), _mouseButtonState(), _mouseButtonJustDown(), _mouseButtonJustUp(), _mouseWheelDelta()
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
	_mouseButtonJustDown.reset();
	_mouseButtonJustUp.reset();
	_mouseDelta[0] = 0;
	_mouseDelta[1] = 0;
}

void MouseInput::receiveEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_MOUSEMOTION:
		_mousePos[0] = event->motion.x;
		_mousePos[1] = event->motion.y;
		_mouseDelta[0] = event->motion.xrel;
		_mouseDelta[1] = event->motion.yrel;
		break;
	case SDL_MOUSEBUTTONDOWN:
		_mouseButtonState[event->button.button - 1] = 1;
		_mouseButtonJustDown[event->button.button - 1] = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		_mouseButtonState[event->button.button - 1] = 0;
		_mouseButtonJustUp[event->button.button - 1] = 1;
		break;
	case SDL_MOUSEWHEEL:
		_mouseWheelDelta = event->wheel.y;
		break;
	}
}