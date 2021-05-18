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
	bool init(std::string const& resourcesPath, std::string const& scenesPath);

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

	/// </sumary>
	/// Gets the window size
	/// </summary>
	std::pair<int, int> getWindowSize();

	/// <summary>
	/// Sets the colour of the shade in the scene
	/// </summary>
	/// <param name="r"> Red color-- [0,1] </param>
	/// <param name="g"> Green color-- [0,1] </param>
	/// <param name="b"> Blue color-- [0,1] </param>
	void setShadowColour(float r, float g, float b);

	/// <summary>
	/// Sets the ambient light
	/// </summary>
	/// <param name="r"> Red color-- [0,1] </param>
	/// <param name="g"> Green color-- [0,1] </param>
	/// <param name="b"> Blue color-- [0,1] </param>
	void setAmbientLight(float r, float g, float b);

	/// <summary>
	/// Sets the colour viewport
	/// </summary>
	/// <param name="r"> Red color-- [0,1] </param>
	/// <param name="g"> Green color-- [0,1] </param>
	/// <param name="b"> Blue color-- [0,1] </param>
	void setViewportColour(float r, float g, float b);

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
	/// Called to start default factories
	/// </summary>
	void initEngineFactories();

	/// <summary>
	/// Deletes the gameObjects setted to be deleted
	/// </summary>
	void cleanUpGameObjects();

	/// <summary>
	/// Changes the scene to currentScene
	/// </summary>
	void changeScene();

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	Engine();

	/// <summary>
	/// Process events
	/// </summary>
	void processEvents();

	PhysxEngine* _physxEngine;
	GraphicsEngine* _graphicsEngine;
	AudioEngine* _audioEngine;
	std::list<GameObject*> _GOs;
	std::list<GameObject*> _deleteGOs;

	static std::unique_ptr<Engine> instance;

	InputManager* _inputManager;
	EngineTime* _time;
	LuaParser* _luaParser;

	bool _run;
	bool alredyInitialized;
	bool _changeScene;

	std::string scenesPath;
	std::string _currentScene;
};

#endif /*Engine.h*/