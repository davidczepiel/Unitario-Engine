#pragma once

#ifndef MOTORUNITARIO_H
#define MOTORUNITARIO_H

#include <list>
#include <string>
class GameObject;

class MotorUnitario
{
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>
	MotorUnitario(MotorUnitario& other) = delete;
	/// Initialize everything related to the Graphics, Physics and Audio engines
	/// </summary>
	/// Starts the main loop of the engine
	/// </summary>
	/// Adds component to the gameObject vector of components
	/// <param name="scene">: Contains the file directory where the dats of the next scene is</param>
	/// Includes all the methods related to the GameObjects Update
	/// </summary>
	/// Stops the main loop
	/// </summary>
	/// Frees everything related to the engines (Audio, Physics, Graphics)
	/// </summary>
	/// Calls the Start method of each GameObject in the list
	/// </summary>
	/// Calls the FixedUpdate method of each GameObject in the list
	/// </summary>
	/// Calls the Update method of each GameObject in the list
	/// </summary>
	/// Calls the LateUpdate method of each GameObject in the list
	/// </summary>
	/// Adds a GameObject to the list
	/// </summary>
	/// Removes the first appeareance of a GameObject
	/// <param name="GO">: GameObject to remove</param>
	/// </summary>
	/// Removes the first appearance of a GameObject based on its name
	/// <param name="GOname">: name of the GameObject to remove</param>
	/// </summary>
	/// Searches a GameObject by its name and returns it if found, or null if not
	///<param name="componentId">: id of component</param>
	/// <returns>Returns the GameObject if it is found</returns>
	/// </summary>
	/// <summary>
	/// Contructor of the class
	/// </summary>
	MotorUnitario();

	static MotorUnitario* instance;
	std::list<GameObject*> GOs;

	bool _run;
};

#endif /*MotorUnitario.h*/