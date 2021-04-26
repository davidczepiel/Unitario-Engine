#pragma once
#ifndef LISTENERCOMPONENT_H
#define LISTENERCOMPONENT_H

#include "Component.h"
#include <string>

class Listener;
class Transform;

class ListenerComponent : public Component
{
public:

	/// <summary>
	/// Default constructor of the class
	/// </summary>
	ListenerComponent();

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ListenerComponent();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start() override;
	/// <summary>
	/// Update the position and rotation of the Listener
	/// </summary>
	virtual void update() override;
	/// <summary>
	/// Called each frame after update.
	/// </summary>
	virtual void lateUpdate() override;

	void setListenerNumber(int listenNumber);

private:
	Transform* _tr;
	Listener* _listener;
};



#endif LISTENERCOMPONENT_H