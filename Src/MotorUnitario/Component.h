#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"
class GameObject;

class Component
{
public:

	Component(unsigned int id, GameObject* gameObject);
	virtual ~Component();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef &data) {}

	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start() {}

	/// <summary>
	/// Called each frame to update non-physical information
	/// </summary>
	virtual void update() {}

	/// <summary>
	/// Called each pshyical step to update physiscal information
	/// </summary>
	virtual void fixedUpdate() {}

	/// <summary>
	/// Called each frame after update
	/// </summary>
	virtual void lateUpdate() {}

	/// <summary>
	/// Called when the owner is not a trigger and collides with another GameObject
	/// </summary>
	/// <param name="other">Pointer to Gameobject owner collided with</param>
	virtual void onCollision(GameObject* other) {}

	/// <summary>
	/// Called when the owner is a trigger and collides with another GameObject
	/// </summary>
	/// <param name="other">Pointer to Gameobject owner collided with</param>
	virtual void onTrigger(GameObject* other) {}

	/// <summary>
	/// Returns a pointer to the GameObject that own the component
	/// </summary>
	/// <returns>Pointer to the GameObject that own the component</returns>
	inline GameObject* getGameObject() const { return _gameObject; }

	/// <summary>
	/// Sets the owner pointer to the given gameObject
	/// </summary>
	/// <param name="gameObject">Pointer to the new component's owner</param>
	void setGameObject(GameObject* gameObject);

	/// <summary>
	/// Returns component's id
	/// </summary>
	/// <returns>Component's id</returns>
	inline unsigned int getId() const { return _id; }

	/// <summary>
	/// Set the component to a new state (true=enabled, false=disabled)
	/// </summary>
	/// <param name="newState">New component's state (true=enabled/false=disabled)</param>
	inline void setEnabled(bool newState) { _enabled = newState; }

	/// <summary>
	/// Returns true if the component is enabled or false if it is not enabled
	/// </summary>
	/// <returns></returns>
	inline bool getEnabled() { return _enabled; }

protected:

	GameObject* _gameObject;

private:

	unsigned int _id;
	bool _enabled;
};

#endif COMPONENT_H