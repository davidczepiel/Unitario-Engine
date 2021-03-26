#include "GameObject.h"
#include "Component.h"
#include "Exceptions.h"

GameObject::GameObject() : _children(), _components(10, nullptr), _parent(nullptr), _enable(true), _persist(false)
{
	//TODO: Tranform
	/*Transform* tranform = new Transform();
	tranform->setId(0);
	_components[0] = tranform;	
	_activeComponents.pushback(transform);
	*/
}

void GameObject::start()
{
	for (auto& comp : _activeComponents)
		if(comp.second->getEnable()) 
			comp.second->start();

	for (GameObject* go : _children)
		if(go->getEnable()) 
			go->start();
}

void GameObject::update()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnable())
			comp.second->update();

	for (GameObject* go : _children)
		if (go->getEnable()) 
			go->update();
}

void GameObject::fixedUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnable())
			comp.second->fixedUpdate();

	for (GameObject* go : _children)
		if (go->getEnable()) 
			go->fixedUpdate();
}

void GameObject::lateUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnable())
			comp.second->lateUpdate();

	for (GameObject* go : _children)
		if (go->getEnable()) 
			go->lateUpdate();
}

void GameObject::addComponent(Component* component)
{
	unsigned int id = component->getId();

	if (id < 0 || id >= _components.size())
		throw "Id of component doesnt correspond to any component";

	if (_components[id] != nullptr)
		throw "Component already exists";

	_components[id] = component;

	insertInOrder(id, component);
}

void GameObject::removeComponent(unsigned int componentId)
{
	if (componentId < 0 || componentId >= _components.size())
		throw "Id of component doesnt correspond to any component";

	removeFromActiveComponents(componentId);

	delete _components[componentId];
	_components[componentId] = nullptr;
}

void GameObject::addChild(GameObject* gameObject)
{
	gameObject->setParent(this);
	_children.push_back(gameObject);
}

Component* GameObject::getComponent(unsigned int componentId) const
{
	if (componentId < 0 || componentId >= _components.size())
		throw "Id of component doesnt correspond to any component";

	return _components[componentId];
}

void GameObject::insertInOrder(unsigned int componentId, Component* component)
{
	auto begin = _activeComponents.begin();
	auto end = _activeComponents.end();

	while ((begin != end) && begin->first < componentId) {
		++begin;
	}

	_activeComponents.insert(begin, std::make_pair(componentId, component));
}

void GameObject::removeFromActiveComponents(unsigned int componentId)
{
	auto begin = _activeComponents.begin();
	auto end = _activeComponents.end();

	while ((begin != end)) {
		if (begin->first == componentId) {
			_activeComponents.erase(begin);
			return;
		}
		++begin;
	}
}
