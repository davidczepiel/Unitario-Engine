#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <string>

class GameObject;
class GraphicsEngine;
class InputManager;

class Engine
{
public:
	~Engine();

	//WIP
	/// <summary>
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static Engine* getInstance();
	void operator=(const Engine&) = delete;
	Engine(Engine& other) = delete;

	/// <summary>
	/// Initialize everything related to the Graphics, Physics and Audio engines
	/// </summary>
	void init();

	/// <summary>
	/// Starts the main loop of the engine
	/// </summary>
	void run();

	/// <summary>
	/// Adds component to the gameObject vector of components
	/// <param name="scene">: Contains the file directory where the dats of the next scene is</param>
	/// </summary>
	void changeScene(std::string scene);

protected:

	/// <summary>
	/// Includes all the methods related to the GameObjects Update
	/// </summary>
	void tick();

	//WIP
	/// <summary>
	/// Stops the main loop
	/// </summary>
	void stopExecution();

	/// <summary>
	/// Frees everything related to the engines (Audio, Physics, Graphics)
	/// </summary>
	void freeEnginesResources();

	/// <summary>
	/// Calls the Start method of each GameObject in the list
	/// </summary>
	void start();

	/// <summary>
	/// Calls the FixedUpdate method of each GameObject in the list
	/// </summary>
	void fixedUpdate();

	/// <summary>
	/// Calls the Update method of each GameObject in the list
	/// </summary>
	void update();

	/// <summary>
	/// Calls the LateUpdate method of each GameObject in the list
	/// </summary>
	void lateUpdate();

	/// <summary>
	/// Adds a GameObject to the list
	/// </summary>
	GameObject* addGameObject();

	/// <summary>
	/// Removes the first appeareance of a GameObject
	/// <param name="GO">: GameObject to remove</param>
	/// </summary>
	void remGameObject(GameObject* GO);

	/// <summary>
	/// Removes the first appearance of a GameObject based on its name
	/// <param name="GOname">: name of the GameObject to remove</param>
	/// </summary>
	void remGameObjectString(std::string const& GOname);

	/// <summary>
	/// Searches a GameObject by its name and returns it if found, or null if not
	///<param name="componentId">: id of component</param>
	/// <returns>Returns the GameObject if it is found</returns>
	/// </summary>
	GameObject* findGameObject(std::string name);

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	Engine();

	/// <summary>
	/// Process events
	/// </summary>
	void processEvents();

	static Engine* instance;
	GraphicsEngine* _graphicsEngine;
	std::list<GameObject*> _GOs;
	InputManager* _inputManager;

	bool _run;
};

#endif /*Engine.h*/