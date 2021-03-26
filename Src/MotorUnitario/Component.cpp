#include "Component.h"

Component::Component(unsigned int id, GameObject* gameObject):
	_id(id), _gameObject(gameObject), _enabled(true)
{}

Component::~Component()
{}
