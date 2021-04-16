#include "InputManager.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamePadInput.h"
#include "SDL_events.h"
#include "Engine.h"

std::unique_ptr<InputManager> InputManager::instance = nullptr;

InputManager::InputManager() : _keyBoardInput(KeyBoardInput::getInstance()),
_mouseInput(MouseInput::getInstance()),
_gamepadInput(GamePadInput::getInstance())
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new InputManager());
	}
	return instance.get();
}

void InputManager::update()
{
	_keyBoardInput->reset();
	_mouseInput->reset();
	_gamepadInput->reset();

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			_keyBoardInput->receiveEvent(&event);
			break;
		case SDL_KEYUP:
			_keyBoardInput->receiveEvent(&event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_mouseInput->receiveEvent(&event);
			break;
		case SDL_MOUSEBUTTONUP:
			_mouseInput->receiveEvent(&event);
			break;
		case SDL_MOUSEMOTION:
			_mouseInput->receiveEvent(&event);
			break;
		case SDL_MOUSEWHEEL:
			_mouseInput->receiveEvent(&event);
			break;
		case SDL_QUIT:
			Engine::getInstance()->stopExecution();
			break;
		}
	}
}