#pragma once

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <memory>
#include <array>
#include <bitset>
#include "KeyCodes.h"

union SDL_Event;

class MouseInput
{
public:
	~MouseInput();

	/// <summary>
	/// Returns the instance of MouseInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static MouseInput* getInstance();
	MouseInput& operator=(const MouseInput&) = delete;
	MouseInput(MouseInput& other) = delete;

	/// <summary>
	/// Returns the mouse position
	/// </summary>
	/// <returns>Mouse pos {x, y}</returns>
	inline const std::array<int, 2>& getMousePos() { return _mousePos; }

	/// <summary>
	/// Return the delta motion of the mouse
	/// </summary>
	/// <returns>Mouse delta {x, y}</returns>
	inline const std::array<double, 2>& getMouseDelta() { return _mouseDelta; }

	/// <summary>
	/// Returns wether a button is being pressed or not
	/// </summary>
	/// <param name="b">: button key </param>
	/// <returns>true if the specified button is being pressed</returns>
	inline bool isMouseButtonDown(MouseButton b) { return _mouseButtonState[b] == 1; }

	/// <summary>
	/// Returns Returns wether a buttin is being pressed or not
	/// </summary>
	/// <param name="b">: button key </param>
	/// <returns>true if the specified button is NOT being pressed</returns>
	inline bool isMouseButtonUp(MouseButton b) { return _mouseButtonState[b] == 0; }

	/// <summary>
	/// Returns wether a button has just been pressed or not
	/// </summary>
	/// <param name="b">: button key</param>
	/// <returns>true if the specified button was just pressed in this tick</returns>
	inline bool isMouseButtonJustDown(MouseButton b) { return _mouseButtonJustDown[b]; }

	/// <summary>
	/// Returns wether a buttin is being released or not
	/// </summary>
	/// <param name="b">: button key</param>
	/// <returns>true if the specified button was just released in this tick</returns>
	inline bool isMouseButtonJustUp(MouseButton b) { return _mouseButtonJustUp[b]; }

	/// <summary>
	/// While relative mode is true, the mouse will be hidden and will not change its position
	/// </summary>
	/// <param name="relative">: If true relative mode is activated, else its is disabled </param>
	void setMouseRelativeMode(bool relative);

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

	std::array<double, 2> _mousePos;
	std::array<double, 2> _mouseDelta;
	std::bitset<5> _mouseButtonState;
	std::bitset<5> _mouseButtonJustDown;
	std::bitset<5> _mouseButtonJustUp;

	double _mouseWheelDelta;

	friend class InputManager;
};

#endif /*MouseInput.h*/