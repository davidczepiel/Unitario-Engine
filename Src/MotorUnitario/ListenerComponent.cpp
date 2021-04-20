#include "ListenerComponent.h"
#include "MotorAudio/Listener.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"
#include "Logger.h"

#include <algorithm>

#define PI 3.14159265

ListenerComponent::ListenerComponent() :Component(ComponentId::ListenerComponent), _tr(nullptr), _listener(nullptr)
{
}
ListenerComponent::ListenerComponent(GameObject* gameObject) : Component(ComponentId::ListenerComponent, gameObject), _tr(nullptr), _listener(nullptr)
{
}

ListenerComponent::~ListenerComponent()
{
	delete _listener; _listener = nullptr;
}

void ListenerComponent::start()
{
	_listener = new Listener();
	_listener->setUp(0, 1, 0);
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
}

void ListenerComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_listener->setPosition(x, y, z);

	Vector3 forward = _tr->getForward();

	_listener->setForward(forward.getX(), forward.getY(), forward.getZ());
}

void ListenerComponent::lateUpdate()
{
	_listener->update();
}

void ListenerComponent::setListenerNumber(int listenNumber)
{
	_listener->setListenerNumber(listenNumber);
}