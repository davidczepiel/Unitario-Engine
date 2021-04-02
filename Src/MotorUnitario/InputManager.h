#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <memory>

#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamePadInput.h"

class InputManager
{
public:
	~InputManager();

	/// <summary>
	/// Returns the instance of InputManager, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static InputManager* getInstance();
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager& other) = delete;

	/// <summary>
	/// Calls the Update method of each GameObject in the list
	/// </summary>
	void update();

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	InputManager();
	static std::unique_ptr<InputManager> instance;

	KeyBoardInput* _keyBoardInput;
	MouseInput* _mouseInput;
	GamePadInput* _gamepadInput;
};

#endif /*Engine.h*/