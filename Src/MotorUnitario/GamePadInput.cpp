#include "GamePadInput.h"
#include "Exceptions.h"

#define MAX_RUMBLE_TIME 1000
#define DEFAULT_DEADZONE 0.02

std::unique_ptr<GamePadInput> GamePadInput::instance = nullptr;

GamePadInput::GamePadInput() : _joystickDeadZone(DEFAULT_DEADZONE), _gamePads(), _buttonJustDown(), _buttonJustUp()
{
}

GamePadInput::~GamePadInput()
{
	for (int i = 0; i < MAX_NUMBER_GAMEPADS; ++i) {
		if (_gamePads[i] != nullptr) {
			SDL_GameControllerClose(_gamePads[i]);
			_gamePads[i] = nullptr;
		}
	}
}

GamePadInput* GamePadInput::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new GamePadInput());
	}
	return instance.get();
}

const bool GamePadInput::isButtonDown(GamePadCode buttonCode, int gPadID)
{
	if (gPadID < 0 || gPadID >= MAX_NUMBER_GAMEPADS)
		throw GamePadException("gpadId must be between [0, MAX_NUMBER_GAMEPADS)");
	if (_gamePads[gPadID] == nullptr)
		throw GamePadException("gpad not accesible or it doesn't exist");

	return SDL_GameControllerGetButton(_gamePads[gPadID], (SDL_GameControllerButton)buttonCode) == 1;
}

const bool GamePadInput::isButtonUp(GamePadCode buttonCode, int gPadID)
{
	if (gPadID < 0 || gPadID >= MAX_NUMBER_GAMEPADS)
		throw GamePadException("gpadId must be between [0, MAX_NUMBER_GAMEPADS)");
	if (_gamePads[gPadID] == nullptr)
		throw GamePadException("gpad not accesible or it doesn't exist");

	return SDL_GameControllerGetButton(_gamePads[gPadID], (SDL_GameControllerButton)buttonCode) == 0;
}

const bool GamePadInput::isButtonJustDown(GamePadCode buttonCode, int gPadID)
{
	if (gPadID < 0 || gPadID >= MAX_NUMBER_GAMEPADS)
		throw GamePadException("gpadId must be between [0, MAX_NUMBER_GAMEPADS)");
	if (_gamePads[gPadID] == nullptr)
		throw GamePadException("gpad not accesible or it doesn't exist");

	return _buttonJustDown[gPadID][buttonCode];
}

const bool GamePadInput::isButtonJustUp(GamePadCode buttonCode, int gPadID)
{
	if (gPadID < 0 || gPadID >= MAX_NUMBER_GAMEPADS)
		throw GamePadException("gpadId must be between [0, MAX_NUMBER_GAMEPADS)");
	if (_gamePads[gPadID] == nullptr)
		throw GamePadException("gpad not accesible or it doesn't exist");

	return _buttonJustUp[gPadID][buttonCode];
}

const double GamePadInput::getAxisValue(GamePadAxis axis, int gPadID) {
	if (gPadID < 0 || gPadID >= MAX_NUMBER_GAMEPADS)
		throw GamePadException("gpadId must be between [0, MAX_NUMBER_GAMEPADS)");
	if (_gamePads[gPadID] == nullptr)
		throw GamePadException("gpad not accesible or it doesn't exist");

	double value = SDL_GameControllerGetAxis(_gamePads[gPadID], (SDL_GameControllerAxis)axis) / 32678.0;

	return (abs(value) < _joystickDeadZone) ? 0 : value;
}

void GamePadInput::setJoystickDeadZone(double deadZone)
{
	_joystickDeadZone = std::min(1.0, std::max(0.0, deadZone));
}

void GamePadInput::rumbleGamePad(Uint16 low_frequency_rumble, Uint16 high_frequency_rumble, Uint32 duration_ms, int gPadID)
{
	if (gPadID < 0 || gPadID >= MAX_NUMBER_GAMEPADS)
		throw GamePadException("gpadId must be between [0, MAX_NUMBER_GAMEPADS)");
	if (_gamePads[gPadID] == nullptr)
		throw GamePadException("gpad not accesible or it doesn't exist");

	if (duration_ms < 0 || duration_ms > MAX_RUMBLE_TIME)
		throw GamePadException("rumble time duration is either less than 0 or greater than 1000ms");

	//TODO: better to rather launch a log message than an exception
	if (SDL_GameControllerRumble(_gamePads[gPadID], low_frequency_rumble, high_frequency_rumble, duration_ms) < 0)
		throw GamePadException("gpad is unable to rumble");
}

void GamePadInput::reset()
{
	for (int i = 0; i < MAX_NUMBER_GAMEPADS; ++i) {
		_buttonJustDown[i].reset();
		_buttonJustUp[i].reset();
	}
}

void GamePadInput::receiveEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_CONTROLLERDEVICEADDED:
		addController(event->cdevice.which);
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		removeController(event->cdevice.which);
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		processButtonDown(event);
		break;
	case SDL_CONTROLLERBUTTONUP:
		processButtonUp(event);
		break;
	}
}

void GamePadInput::addController(Sint32 which)
{
	int index = 0;
	while (index < MAX_NUMBER_GAMEPADS && _gamePads[index] != nullptr)
		++index;

	if (index < MAX_NUMBER_GAMEPADS)
		_gamePads[index] = SDL_GameControllerOpen(which);
}

void GamePadInput::removeController(SDL_JoystickID instanceID)
{
	int index = findIndexOfGameController(instanceID);

	if (index < MAX_NUMBER_GAMEPADS) {
		SDL_GameControllerClose(_gamePads[index]);
		_gamePads[index] = nullptr;
	}
}

void GamePadInput::processButtonDown(SDL_Event* event)
{
	int index = findIndexOfGameController(event->cdevice.which);

	if (index < MAX_NUMBER_GAMEPADS)
		_buttonJustDown[index][event->button.button] = 1;
}

void GamePadInput::processButtonUp(SDL_Event* event)
{
	int index = findIndexOfGameController(event->cdevice.which);

	if (index < MAX_NUMBER_GAMEPADS)
		_buttonJustUp[index][event->button.button] = 1;
}

int GamePadInput::findIndexOfGameController(SDL_JoystickID instanceID)
{
	int index = 0;
	while (index < MAX_NUMBER_GAMEPADS && SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_gamePads[index])) != instanceID)
		++index;

	return index;
}