#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <string>
#include <memory>

class GameObject;
class GraphicsEngine;
class PhysxEngine;
class InputManager;
class AudioEngine;
class ComponentsFactory;

#define ADD(className)ComponentsFactory::add(className,classNameFactory);
class EngineTime;
class LuaParser;

class Engine
{
public:
	~Engine();

	/// <summary>
	/// Returns the instance of Engine, or nullptr if it doesnt exist yet
	/// </summary>
	static Engine* getInstance();

	/// <summary>
	/// Creates the Engine singleton instance if its not already created
	/// </summary>
	static void CreateInstance();

	Engine& operator=(const Engine&) = delete;
	Engine(Engine& other) = delete;

	/// <summary>
	/// Initialize everything related to the Graphics, Physics and Audio engines
	/// </summary>
	/// <param name = "resourcesPath">: Resources path</param>
	bool init(std::string const& resourcesPath);

	/// <summary>
	/// Starts the main loop of the engine
	/// </summary>
	void run();

	/// <summary>
	/// Adds component to the gameObject vector of components
	/// <param name="scene">: Contains the file directory where the dats of the next scene is</param>
	/// </summary>
	void changeScene(const std::string& scene);

	//WIP
	/// <summary>
	/// Stops the main loop
	/// </summary>
	void stopExecution();

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
	void remGameObjectString(const std::string& GOname);

	/// <summary>
	/// Searches a GameObject by its name and returns it if found, or null if not
	///<param name="componentId">: id of component</param>
	/// <returns>Returns the GameObject if it is found</returns>
	/// </summary>
	GameObject* findGameObject(const std::string& name);

protected:

	/// <summary>
	/// Includes all the methods related to the GameObjects Update
	/// </summary>
	void tick();

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
	/// Called before the end of execution (free resources and shutdown engines)
	/// </summary>
	void shutDown();

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	Engine();

	/// <summary>
	/// Process events
	/// </summary>
	void processEvents();

	/// <summary>
	/// Adds all the components factories of the engine and creates componenets.
	///This is for testing the factorires
	/// </summary>
	void initFactories();

	PhysxEngine* _physxEngine;
	GraphicsEngine* _graphicsEngine;
	AudioEngine* _audioEngine;
	std::list<GameObject*> _GOs;
	static std::unique_ptr<Engine> instance;
	InputManager* _inputManager;
	EngineTime* _time;
	LuaParser* _luaParser;

	bool _run;
	bool alredyInitialized;

};

#endif /*Engine.h*/