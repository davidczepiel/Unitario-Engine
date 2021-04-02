#pragma once

#ifndef GAMEPAD_INPUT_H
#define GAMEPAD_INPUT_H

#include <memory>

#include "SDL_events.h"

class GamePadInput
{
public:
	~GamePadInput();

	//WIP
	/// <summary>
	/// Returns the instance of GamePadInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GamePadInput* getInstance();
	GamePadInput& operator=(const GamePadInput&) = delete;
	GamePadInput(GamePadInput& other) = delete;

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	GamePadInput();
	static std::unique_ptr<GamePadInput> instance;

	/// <summary>
	/// Resets the key's. Called by InputManager
	/// </summary>
	void reset();

	/// <summary>
	/// Called by InputManager
	/// </summary>
	void receiveEvent(SDL_Event* event);

	friend class InputManager;

};

#endif /*GamePadInput.h*/