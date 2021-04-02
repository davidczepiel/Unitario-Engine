#include "GamePadInput.h"

std::unique_ptr<GamePadInput> GamePadInput::instance = nullptr;

GamePadInput::GamePadInput()
{
}

GamePadInput::~GamePadInput()
{
}

GamePadInput* GamePadInput::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new GamePadInput());
	}
	return instance.get();
}

void GamePadInput::reset()
{
}

void GamePadInput::receiveEvent(SDL_Event* event)
{
}