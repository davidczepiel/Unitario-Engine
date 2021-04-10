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
	ListenerComponent(GameObject* gameObject);
	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ListenerComponent();

	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start();
	/// <summary>
	/// Update the position and rotation of the Listener
	/// </summary>
	virtual void update();
	/// <summary>
	/// Called each frame after update.
	/// </summary>
	virtual void lateUpdate();

	void setListenerNumber(int listenNumber);

private:
	Transform* _tr;
	Listener* _listener;
};

#endif LISTENERCOMPONENT_H