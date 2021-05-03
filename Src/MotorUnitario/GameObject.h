#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <vector>
#include <string>

class Transformer;
class Component;

class GameObject {

public:

	/// <summary>
	/// Constructs Gameobject initializing vector of componentes with a Transform
	/// </summary>
	GameObject();

	~GameObject();

	/// <summary>
	/// Calls start method of every component and then of every children it has
	/// </summary>
	void start();

	/// <summary>
	/// Calls update method of every component and then of every children it has
	/// </summary>
	void update();

	/// <summary>
	/// Calls fixedUpdate method of every component and then of every children it has
	/// </summary>
	void fixedUpdate();

	/// <summary>
	/// Called after complete the physic simulation (only to set Trabsform)
	/// </summary>
	void postFixedUpdate();

	/// <summary>
	/// Calls lateUpdate method of every component and then of every children it has
	/// </summary>
	void lateUpdate();

	void onCollision(GameObject* other);

	void onTrigger(GameObject* other);

	/// <summary>
	/// Adds component to the gameObject vector of components
	/// <para> If id its bigger than the actual size of the vector of components, it increases the vector size </para>
	/// <exception cref="Component.Exception">Thrown when componentId is less than 0 or component already exists</exception>
	/// </summary>
	void addComponent(Component* component);
	
	/// <summary>
	/// Removes component from gameObject
	/// </summary>
	/// <param name="componentId_">: id of the component to remove</param>
	/// <exception cref="Component.Exception">Thrown when componentId doesnt correspond to any component</exception>
	void removeComponent(unsigned int componentId);

	/// <summary>
	/// Adds gameObject as a child of this gameObject. 
	/// <para> Parent of the child is set to this gameObject. </para>
	/// </summary>
	/// <param name="gameObject_">: child</param>
	void addChild(GameObject* gameObject);

	/// <summary>
	/// Returns a component of the gameObject
	/// </summary>
	/// <param name="componentId_">: id of component</param>
	/// <exception cref="Component.Exception">Thrown when componentId is below zero</exception>
	/// <returns>Component* if it exists, nullptr if it doesn't</returns>
	Component* getComponent(unsigned int componentId) const;

	inline const std::list<GameObject*>& getChildren() const {
		return _children;
	}

	inline const GameObject* getParent() const {
		return _parent;
	}

	inline void setParent(GameObject* gameObject) {
		_parent = gameObject;
	}

	inline const std::string& getName() const {
		return _name;
	}

	inline void setName(const std::string& name) {
		_name = name;
	}

	inline const bool getEnabled() const {
		return _enable;
	}

	void setEnabled(bool enable);

	inline const bool getPersist() const {
		return _persist;
	}

	inline void setPersist(bool persist) {
		_persist = persist;
	}

private:
	/// <summary>
	/// Inserts into active components a component ordered using its id
	/// </summary>
	/// <param name="componentId">: id of component</param>
	/// <param name="component">: component to insert</param>
	void insertInOrder(unsigned int componentId, Component* component);

	/// <summary>
	/// Removes component from active components
	/// </summary>
	/// <param name="componentId">: id of component</param>
	void removeFromActiveComponents(unsigned int componentId);

	std::vector<Component*> _components;

	std::list<std::pair<unsigned int, Component*>> _activeComponents;

	std::list<GameObject*> _children;	

	GameObject* _parent;

	std::string _name;

	bool _enable, _persist;
};

#endif GAMEOBJECT_H /* GameObject.h */