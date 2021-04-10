#include "ListenerComponent.h"
#include "MotorAudio/Listener.h"
#include "GameObject.h"
#include "Transform.h"

ListenerComponent::ListenerComponent(GameObject* gameObject) :Component(9, gameObject), _tr(nullptr), _listener(nullptr)
{
}

ListenerComponent::~ListenerComponent()
{
	delete _listener;
	delete _tr;
}

void ListenerComponent::start()
{
	_listener = new Listener();
	_tr = static_cast<Transform*>(_gameObject->getComponent(7));
}

void ListenerComponent::update()
{
	_listener->setPosition(_tr->getPosition().getX(), _tr->getPosition().getY(), _tr->getPosition().getZ());
	_listener->setForward(_tr->getRotation().getX(), 0, _tr->getRotation().getZ());
	_listener->setUp(_tr->getRotation().getX(), _tr->getRotation().getY(), 0);
}

void ListenerComponent::lateUpdate()
{
	_listener->update();
}

void ListenerComponent::setListenerNumber(int listenNumber)
{
	_listener->setListenerNumber(listenNumber);
}