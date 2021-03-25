#pragma once
#include <list>

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

	//No se si el componente tendria un "id" para asignarselo al vector o al diccionario
	void addComponent(Component* component_);
	
	//Aqui estaria mejor recibir un "id"
	void removeComponent(Component* component_);

	/// <summary>
	/// Adds gameObject as a child of this gameObject. 
	/// <para> Parent of the child is set to this gameObject. </para>
	/// </summary>
	/// <param name="gameObject_">: child</param>
	void addChild(GameObject* gameObject_);

	//Aqui estaria mejor recibir un "id"
	inline Component* getComponent(Component* component_) const {
		return nullptr;
	}

	inline const std::list<GameObject*>& getChildren() const {
		return children;
	}

	inline const GameObject* getParent() const {
		return parent;
	}

	inline void setParent(GameObject* gameObject_) {
		parent = gameObject_;
	}

	inline const bool getEnable() const {
		return enable;
	}

	inline void setEnable(bool enable_) {
		enable = enable_;
	}

	inline const bool getPersist() const {
		return persist;
	}

	inline void setPersist(bool persist_) {
		persist = persist_;
	}

private:
	std::list<GameObject*> children;

	//Si se usa un id, la lista de componentes podria pasar a un vector, o un diccionario (un vector seria mas rapido)
	//Si se usa un id, el component Transform se podria meter junto a los otros componentes, con id = 0 por ejemplo
	std::list<Component*> components;
	Transform* transform;

	GameObject* parent;

	bool enable, persist;
};