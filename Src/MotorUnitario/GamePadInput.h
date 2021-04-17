#pragma once

#ifndef GAMEPAD_INPUT_H
#define GAMEPAD_INPUT_H

#include <memory>
#include <array>
#include <bitset>

#include "SDL_events.h"
#include "SDL_joystick.h"

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
	/// Returns wether a determined button is being pressed or not
	/// </summary>
	/// <param name="buttonCode">: button that we are going to ask about </param>
	/// <param name="gPadID">: id of the gamepad we are going to ask about </param>
	/// <return> True if the button is being pressed/False if not <return>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonDown(GamePadCode buttonCode, int gpadId = 0);

	/// <summary>
	/// Returns wether a determined button is not being pressed or not
	/// </summary>
	/// <param name="buttonCode">: button that we are going to ask about </param>
	/// <param name="gPadID">: id of the gamepad we are going to ask about </param>
	/// <return> True if the button is not being pressed/False if not <return>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonUp(GamePadCode buttonCode, int gPadID = 0);

	/// <summary>
	/// Returns wether a determined button has just been pressed or not
	/// </summary>
	/// <param name="buttonCode">: button that we are going to ask about </param>
	/// <param name="gPadID">: id of the gamepad we are going to ask about </param>
	/// <return> True if the button has just been pressed/False if not <return>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonJustDown(GamePadCode buttonCode, int gPadID = 0);

	/// <summary>
	/// Returns wether a determined button has just been released or not
	/// </summary>
	/// <param name="buttonCode">: button that we are going to ask about </param>
	/// <param name="gPadID">: id of the gamepad we are going to ask about </param>
	/// <return> True if the button has just been released/False if not <return>
	/// <exception cref="GamePadException"> throws if gPadId is not between [0, MAX_NUMBER_GAMEPADS) range </exception>
	const bool isButtonJustUp(GamePadCode buttonCode, int gPadID = 0);

	/// <summary>
	/// Get the actual value of a determined axis
	/// </summary>
	/// <param name="axisCode">: axis that we are going to ask about </param>
	/// <param name="gPadID">: id of the gamepad we are going to ask about </param>
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

	/// <summary>
	/// Returns wether or not a gamepad is connected/avaliable to use
	/// </summary>
	/// <param name="gPadID"> ID of the gamePad</param>
	/// <returns> True if the controller is ready to use, False if the controller is not connected</returns>
	const bool isControllerAvaliable(Uint16 gPadID);

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