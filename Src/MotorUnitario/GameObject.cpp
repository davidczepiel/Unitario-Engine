#include "GameObject.h"
#include "Component.h"
#include "Exceptions.h"

GameObject::GameObject() : _children(), _components(), _parent(nullptr), _enable(true), _persist(false)
{
	//transform = new Transform();
	//components->add(0, tranform);		???
}

void GameObject::start()
{
	for (Component* comp : _components)
		if(comp->getEnable()) 
			comp->start();

	for (GameObject* go : _children)
		if(go->getEnable()) 
			go->start();
}

void GameObject::update()
{
	for (Component* comp : _components)
		if (comp->getEnable()) 
			comp->update();

	for (GameObject* go : _children)
		if (go->getEnable()) 
			go->update();
}

void GameObject::fixedUpdate()
{
	for (Component* comp : _components)
		if (comp->getEnable()) 
			comp->fixedUpdate();

	for (GameObject* go : _children)
		if (go->getEnable()) 
			go->fixedUpdate();
}

void GameObject::lateUpdate()
{
	for (Component* comp : _components)
		if (comp->getEnable()) 
			comp->fixedUpdate();

	for (GameObject* go : _children)
		if (go->getEnable()) 
			go->lateUpdate();
}

void GameObject::addComponent(Component* component)
{
	int id = component->getId();

	if (id < 0 || id > _components.size())
		throw "Id of component doesnt correspond to any component";

	_components[id] = component;
}

void GameObject::removeComponent(unsigned int componentId)
{
	if (componentId < 0 || componentId > _components.size())
		throw "Id of component doesnt correspond to any component";

	delete _components[componentId];
	_components[componentId] = nullptr;
}


void GameObject::addChild(GameObject* gameObject)
{
	gameObject->setParent(this);
	_children.push_back(gameObject);
}

inline Component* GameObject::getComponent(unsigned int componentId) const
{
	if (componentId < 0 || componentId > _components.size())
		throw "Id of component doesnt correspond to any component";

	return _components[componentId];
}
