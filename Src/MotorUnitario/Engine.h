#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <string>
#include <memory>

class GameObject;
class GraphicsEngine;
class InputManager;
class AudioEngine;
class ComponentsFactory;

#define ADD(className)ComponentsFactory::add(className,classNameFactory);
class Time;

class Engine
{
public:
	~Engine();

	//WIP
	/// <summary>
	/// Returns the instance of Engine, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static Engine* getInstance();
	Engine& operator=(const Engine&) = delete;
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
	void changeScene(const std::string& scene);

	//WIP
	/// <summary>
	/// Stops the main loop
	/// </summary>
	void stopExecution();

	/// <summary>
	/// Sets the resources path
	/// </summary>
	/// <param name="resourcesPath"> Resources.cfg path</param>
	void setResourcesPath(std::string const& resourcesPath);

	//This is a method created for testing purposes and should be deleted as the testing is finished
	void testing();

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

	static Engine* _instance;
	GraphicsEngine* _graphicsEngine;
	AudioEngine* _audioEngine;
	std::list<GameObject*> _GOs;
	static std::unique_ptr<Engine> instance;
	InputManager* _inputManager;
	Time* _time;

	GameObject* jugador;
	GameObject* TEST;

	bool _run;
};

#endif /*Engine.h*/