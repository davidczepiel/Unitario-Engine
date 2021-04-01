#include "GamePadInput.h"

GamePadInput* GamePadInput::instance = nullptr;

GamePadInput::GamePadInput()
{
}

GamePadInput::~GamePadInput()
{
}

GamePadInput* GamePadInput::getInstance()
{
	if (instance == nullptr) {
		instance = new GamePadInput();
	}
	return instance;
}

void GamePadInput::reset()
{
}

void GamePadInput::receiveEvent(SDL_Event* event)
{
}