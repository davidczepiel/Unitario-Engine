#pragma once

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <memory>
#include <array>
#include <bitset>

#include "SDL_events.h"

class MouseInput
{
public:

	/// <summary>
	/// Posible mouse buttons. 
	/// <para> X1 and X2 are optional additional mouse buttons the user might have </para>
	/// </summary>
	enum MOUSEBUTTON : Uint8 {
		LEFT, MIDDLE, RIGHT, X1, X2
	};

public:
	~MouseInput();

	/// <summary>
	/// Returns the instance of MouseInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static MouseInput* getInstance();
	MouseInput& operator=(const MouseInput&) = delete;
	MouseInput(MouseInput& other) = delete;

	/// <summary>
	/// </summary>
	/// <returns>Mouse pos {x, y}</returns>
	inline const std::array<int, 2>& getMousePos() { return _mousePos; }

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

	/// <summary>
	/// Resets the key's. Called by InputManager
	/// </summary>
	void reset();

	/// <summary>
	/// Called by InputManager
	/// </summary>
	void receiveEvent(SDL_Event* event);

	static std::unique_ptr<MouseInput> instance;

	std::array<int, 2> _mousePos;
	std::bitset<5> _mouseButtonState;
	std::bitset<5> _mouseButtonJustDown;
	std::bitset<5> _mouseButtonJustUp;

	double _mouseWheelDelta;

	friend class InputManager;
};

#endif /*MouseInput.h*/