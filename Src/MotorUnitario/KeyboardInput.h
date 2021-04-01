#pragma once

#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <bitset>
#include <memory>
#include "SDL_events.h"

#include "KeyCodes.h"

class KeyBoardInput
{
public:
	~KeyBoardInput();

	/// <summary>
	/// Returns the instance of KeyBoardInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static KeyBoardInput* getInstance();
	void operator=(const KeyBoardInput&) = delete;
	KeyBoardInput(KeyBoardInput& other) = delete;

	/// <summary>
	/// Don't call. Resets the key's
	/// </summary>
	void reset();

	/// <summary>
	/// Don't call
	/// </summary>
	void receiveEvent(SDL_Event* event);

	/// <summary>
	/// </summary>
	/// <param name="key"></param>
	/// <returns>true if the specified key is being pressed</returns>
	inline bool isKeyDown(KeyCode key) const {
		return _keyboardState[key] == 1;
	}

	/// <summary>
	/// </summary>
	/// <param name="key"></param>
	/// <returns>true if the specified key is NOT being pressed</returns>
	inline bool isKeyUp(KeyCode key) const {
		return _keyboardState[key] == 0;
	}

	/// <summary>
	/// </summary>
	/// <param name="key"></param>
	/// <returns>true if the specified key was just pressed in this tick</returns>
	inline bool isKeyJustDown(KeyCode key) const {
		return _keyJustDown[key] == 1;
	}

	/// <summary>
	/// </summary>
	/// <param name="key"></param>
	/// <returns>true if the specified key was just released in this tick</returns>
	inline bool isKeyJustUp(KeyCode key) const {
		return _keyJustUp[key] == 1;
	}

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	KeyBoardInput();
	static std::unique_ptr<KeyBoardInput> instance;

	std::bitset<256> _keyJustDown;
	std::bitset<256> _keyJustUp;
	const Uint8* _keyboardState;
};

#endif /*KeyBoardInput.h*/