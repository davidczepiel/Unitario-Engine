#pragma once

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <memory>
#include <array>

#include "SDL_events.h"

class MouseInput
{
public:
	enum MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

public:
	~MouseInput();

	/// <summary>
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static MouseInput* getInstance();
	MouseInput& operator=(const MouseInput&) = delete;
	MouseInput(MouseInput& other) = delete;

	/// <summary>
	/// Don't call. Resets the just keys
	/// </summary>
	void reset();

	/// <summary>
	/// Don't call.
	/// </summary>
	void receiveEvent(SDL_Event* event);

	/// <summary>
	/// </summary>
	/// <returns>Mouse pos {x, y}</returns>
	inline const std::array<double, 2>& getMousePos() { return _mousePos; }

	/// <summary>
	/// </summary>
	/// <param name="b">: button key </param>
	/// <returns>true if the specified button is being pressed</returns>
	inline bool isMouseButtonDown(MOUSEBUTTON b) { return _mouseButtonState[b] == 1; }

	/// <summary>
	/// </summary>
	/// <param name="b">: button key </param>
	/// <returns>true if the specified button is NOT being pressed</returns>
	inline bool isMouseButtonUp(MOUSEBUTTON b) { return _mouseButtonState[b] == 0; }

	/// <summary>
	/// </summary>
	/// <param name="b">: button key</param>
	/// <returns>true if the specified button was just pressed in this tick</returns>
	inline bool isMouseButtonJustDown(MOUSEBUTTON b) { return _mouseButtonJustDown[b]; }

	/// <summary>
	/// </summary>
	/// <param name="b">: button key</param>
	/// <returns>true if the specified button was just released in this tick</returns>
	inline bool isMouseButtonJustUp(MOUSEBUTTON b) { return _mouseButtonJustUp[b]; }

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	MouseInput();
	static std::unique_ptr<MouseInput> instance;

	std::array<double, 2> _mousePos;
	std::array<bool, 3> _mouseButtonState;
	std::array<bool, 3> _mouseButtonJustDown;
	std::array<bool, 3> _mouseButtonJustUp;

	double _mouseWheelDelta;
};

#endif /*MouseInput.h*/