#pragma once

#ifndef GAMEPAD_INPUT_H
#define GAMEPAD_INPUT_H

#include <memory>
#include <array>
#include <bitset>

union SDL_Event;
struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

typedef int32_t;
typedef int32_t Sint32;
typedef uint32_t;
typedef uint32_t Uint32;

typedef Sint32 SDL_JoystickID;

typedef uint16_t;
typedef uint16_t Uint16;

#include "GamePadCodes.h"

#define MAX_NUMBER_GAMEPADS 4

class GamePadInput
{
public:
	~GamePadInput();

	/// <summary>
	/// Returns the instance of GamePadInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GamePadInput* getInstance();
	GamePadInput& operator=(const GamePadInput&) = delete;
	GamePadInput(GamePadInput& other) = delete;

	/// <summary>
	/// </summary>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonDown(GamePadCode buttonCode, int gpadId = 0);

	/// <summary>
	/// </summary>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonUp(GamePadCode buttonCode, int gPadID = 0);

	/// <summary>
	/// </summary>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonJustDown(GamePadCode buttonCode, int gPadID = 0);

	/// <summary>
	/// </summary>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonJustUp(GamePadCode buttonCode, int gPadID = 0);

	/// <summary>
	/// </summary>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	/// <returns> axis value between -1 and 1 </returns>
	const double getAxisValue(GamePadAxis axisCode, int gPadID = 0);

	/// <summary>
	/// Percentage of deadzone, clamped between 0 (no deadzone) and 1 (value of any axis will always be 0)
	/// </summary>
	void setJoystickDeadZone(double deadZone);

	/// <summary>
	/// Makes gamePad rumble
	/// </summary>
	/// <param name="low_frequency_rumble">: The intensity of the low frequency (left) rumble motor, from 0 to 0xFFFF </param>
	/// <param name="high_frequency_rumble">: The intensity of the high frequency(right) rumble motor, from 0 to 0xFFFF </param>
	/// <param name="duration_ms">: The duration of the rumble effect, in milliseconds (between 0 and 1000) </param>
	/// <param name="gPadID">: ID of the controller</param>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	/// <exception cref="GamePadException"> throws if duration time is less than 0 or greater than 1000 </exception>
	void rumbleGamePad(Uint16 low_frequency_rumble, Uint16 high_frequency_rumble, Uint32 duration_ms, int gPadID = 0);

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

	/// <summary>
	/// Removes a controller specified by the given ID
	/// </summary>
	void addController(Sint32 which);

	/// <summary>
	/// Removes a controller specified by the given ID
	/// </summary>
	/// <param name = "instanceId">: ID of the controller to be removed </param>
	void removeController(SDL_JoystickID instanceId);

	/// <summary>
	/// Finds the controller whose button has been pressed and processes it
	/// </summary>
	/// <param name = "event">: event triggered </param>
	void processButtonDown(SDL_Event* event);

	/// <summary>
	/// Finds the controller whose button has been released and processes it
	/// </summary>
	/// <param name = "event">: event triggered </param>
	void processButtonUp(SDL_Event* event);

	/// <summary>
	/// Searches the index of a controller in the array given a Joystick index
	/// </summary>
	/// <param name="gameController"> ID of the controller to identify </param>
	/// <returns>the index of the controller we are searching in the array "_gamePads"</returns>
	int findIndexOfGameController(SDL_JoystickID gameController);

	double _joystickDeadZone;

	std::array<SDL_GameController*, MAX_NUMBER_GAMEPADS> _gamePads;

	std::array<std::bitset<22>, MAX_NUMBER_GAMEPADS> _buttonJustDown;
	std::array<std::bitset<22>, MAX_NUMBER_GAMEPADS> _buttonJustUp;

	friend class InputManager;
};

#endif /*GamePadInput.h*/