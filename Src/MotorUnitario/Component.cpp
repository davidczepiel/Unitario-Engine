#include "Component.h"
#include "Exceptions.h"

Component::Component(unsigned int id, GameObject* gameObject):
	_id(id), _gameObject(gameObject), _enabled(true)
{}

Component::~Component()
{}

inline void Component::setGameObject(GameObject * gameObject)
{
	if (gameObject == nullptr) {
		throw NullptrObjectException("Trying to set component's owner to nullptr");
		return;
	}
	_gameObject = gameObject;
}
