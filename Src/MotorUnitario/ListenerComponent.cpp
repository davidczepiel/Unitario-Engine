#include "ListenerComponent.h"
#include "MotorAudio/Listener.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"

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
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
}

void ListenerComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_listener->setPosition(x, y, z);

	float xR = static_cast<float>(_tr->getRotation().getX());
	float yR = static_cast<float>(_tr->getRotation().getY());
	float zR = static_cast<float>(_tr->getRotation().getZ());
	_listener->setForward(xR, 0, zR);
	_listener->setUp(xR, yR, 0);
}

void ListenerComponent::lateUpdate()
{
	_listener->update();
}

void ListenerComponent::setListenerNumber(int listenNumber)
{
	_listener->setListenerNumber(listenNumber);
}