#pragma once

#ifndef GAMEPAD_INPUT_H
#define GAMEPAD_INPUT_H

#include "SDL_events.h"

class GamePadInput
{
public:
	~GamePadInput();

	//WIP
	/// <summary>
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GamePadInput* getInstance();
	void operator=(const GamePadInput&) = delete;
	GamePadInput(GamePadInput& other) = delete;

	/// <summary>
	/// Calls the Update method of each GameObject in the list
	/// </summary>
	void reset();

	void receiveEvent(SDL_Event* event);

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	GamePadInput();
	static GamePadInput* instance;
};

#endif /*GamePadInput.h*/