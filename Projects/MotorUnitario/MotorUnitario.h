#pragma once

#ifndef MOTORUNITARIO_H
#define MOTORUNITARIO_H

#include <list>
#include <string>
class GameObject;

class MotorUnitario
{public:	~MotorUnitario();	//WIP	/// <summary>
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>	static MotorUnitario* getInstance();	void operator=(const MotorUnitario&) = delete;
	MotorUnitario(MotorUnitario& other) = delete;	/// <summary>
	/// Initialize everything related to the Graphics, Physics and Audio engines
	/// </summary>	void Init();	/// <summary>
	/// Starts the main loop of the engine
	/// </summary>	void Run();	/// <summary>
	/// Adds component to the gameObject vector of components
	/// <param name="scene">: Contains the file directory where the dats of the next scene is</param>	/// </summary>	void ChangeScene(std::string scene);protected:	/// <summary>
	/// Includes all the methods related to the GameObjects Update
	/// </summary>	void Tick();	//WIP	/// <summary>
	/// Stops the main loop
	/// </summary>	void StopExecution();	/// <summary>
	/// Frees everything related to the engines (Audio, Physics, Graphics)
	/// </summary>	void FreeEnginesResources();	/// <summary>
	/// Calls the Start method of each GameObject in the list
	/// </summary>	void Start();	/// <summary>
	/// Calls the FixedUpdate method of each GameObject in the list
	/// </summary>	void FixedUpdate();	/// <summary>
	/// Calls the Update method of each GameObject in the list
	/// </summary>	void Update();	/// <summary>
	/// Calls the LateUpdate method of each GameObject in the list
	/// </summary>	void LateUpdate();	/// <summary>
	/// Adds a GameObject to the list
	/// </summary>	GameObject * addGameObject();	/// <summary>
	/// Removes the first appeareance of a GameObject
	/// <param name="GO">: GameObject to remove</param>
	/// </summary>	void remGameObject(GameObject* GO);	/// <summary>
	/// Removes the first appearance of a GameObject based on its name
	/// <param name="GOname">: name of the GameObject to remove</param>
	/// </summary>	void remGameObjectString(std::string const& GOname);	/// <summary>
	/// Searches a GameObject by its name and returns it if found, or null if not
	///<param name="componentId">: id of component</param>
	/// <returns>Returns the GameObject if it is found</returns>
	/// </summary>	GameObject* findGameObject(std::string name);private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	MotorUnitario();

	static MotorUnitario* instance;
	std::list<GameObject*> GOs;

	bool _run;
};

#endif /*MotorUnitario.h*/