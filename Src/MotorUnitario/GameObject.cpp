#include "GameObject.h"
#include "Component.h"
#include "Exceptions.h"
#include "Transform.h"
#include "Engine.h"
#include "includeLUA.h"

#define _COMPONENT_START_SIZE_ 15
#define _COMPONENT_INCREASE_SIZE_ size_t(5)

GameObject::GameObject() : _components(_COMPONENT_START_SIZE_, nullptr), _name(), _enable(true), _persist(false)
{
}

GameObject::~GameObject()
{
	for (auto c : _activeComponents) {
		delete c.second; c.second = nullptr;
	}
	_activeComponents.clear();
}

void GameObject::start()
{
	for (auto& comp : _activeComponents)
		if(comp.second->getEnabled()) 
			comp.second->start();
}

void GameObject::update()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->update();
}

void GameObject::fixedUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->fixedUpdate();
}

void GameObject::postFixedUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->postFixedUpdate();
}

void GameObject::lateUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->lateUpdate();
}

void GameObject::onCollision(GameObject* other)
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->onCollision(other);
}

void GameObject::onTrigger(GameObject* other)
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->onTrigger(other);
}

void GameObject::addComponent(Component* component)
{
	unsigned int id = component->getId();

	if ((int)id < 0)
		throw InvalidAccessException("Id of component cant be below zero");

	if (id >= _components.size())
		_components.resize(id + _COMPONENT_INCREASE_SIZE_, nullptr);

	if (_components[id] != nullptr)
		throw ComponentException("Component already exists");

	_components[id] = component;

	insertInOrder(id, component);
}

void GameObject::removeComponent(unsigned int componentId)
{
	if (componentId >= _components.size())
		throw ComponentException("Component doesn't exists or it's not in gameObject named \": " + _name + "\"");

	removeFromActiveComponents(componentId);

	delete _components[componentId];
	_components[componentId] = nullptr;
}

Component* GameObject::getComponent(unsigned int componentId) const
{
	if (componentId >= _components.size())
		return nullptr;

	return _components[componentId];
}

bool GameObject::hasComponent(unsigned int componentID) const
{
	return (componentID >= 0 && componentID < _components.size() && _components[componentID] != nullptr);
}

void GameObject::setEnabled(bool enable)
{
	_enable = enable;
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled() != _enable)
			comp.second->setEnabled(_enable);
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
