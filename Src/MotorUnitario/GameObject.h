#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <vector>

class Transform;
class Component;

class GameObject {

public:

	GameObject();

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
	/// Calls lateUpdate method of every component and then of every children it has
	/// </summary>
	void lateUpdate();

	/// <summary>
	/// Add a full component to the gameObject vector of component
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
	/// <param name="componentId_"></param>
	/// <exception cref="Component.Exception">Thrown when componentId doesnt correspond to any component</exception>
	/// <returns>Component* if it exists, nullptr if it doesn't</returns>
	inline Component* getComponent(unsigned int componentId) const;

	inline const std::list<GameObject*>& getChildren() const {
		return _children;
	}

	inline const GameObject* getParent() const {
		return _parent;
	}

	inline void setParent(GameObject* gameObject) {
		_parent = gameObject;
	}

	inline const bool getEnable() const {
		return _enable;
	}

	inline void setEnable(bool enable) {
		_enable = enable;
	}

	inline const bool getPersist() const {
		return _persist;
	}

	inline void setPersist(bool persist) {
		_persist = persist;
	}

private:
	std::list<GameObject*> _children;

	//Si se usa un id, la lista de componentes podria pasar a un vector, o un diccionario (un vector seria mas rapido)
	//Si se usa un id, el component Transform se podria meter junto a los otros componentes, con id = 0 por ejemplo
	std::vector<Component*> _components;

	GameObject* _parent;

	bool _enable, _persist;
};


#endif GAMEOBJECT_H