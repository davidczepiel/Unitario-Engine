#include "ListenerComponent.h"
#include "MotorAudio/Listener.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"
#include "Logger.h"

#include <algorithm>

#define PI 3.14159265

ListenerComponent::ListenerComponent(GameObject* gameObject):Component(ComponentId::ListenerComponent,gameObject), _tr(nullptr), _listener(new Listener())
{
	
}
ListenerComponent::ListenerComponent():Component(ComponentId::ListenerComponent),_tr(nullptr),_listener(nullptr)
{
}

ListenerComponent::~ListenerComponent()
{
	delete _listener; _listener = nullptr;
}

void ListenerComponent::awake(luabridge::LuaRef& data)
{

	_listener->setListenerNumber(data["ListenerNumber"].cast<int>());
	//float x = data["Velocity"]["X"].cast<float>();
	_listener->setVelocity(data["Velocity"]["X"].cast<float>(), data["Velocity"]["Y"].cast<float>(), data["Velocity"]["Z"].cast<float>());
	_listener->setForward(data["Forward"]["X"].cast<float>(), data["Forward"]["Y"].cast<float>(), data["Forward"]["Z"].cast<float>());
	_listener->setUp(data["Up"]["X"].cast<float>(), data["Up"]["Y"].cast<float>(), data["Up"]["Z"].cast<float>());
	//TODO:COGE EL TRANSFORM, SE PUEDE HACER TAMBIEN OTRA POSICION DESDE LUA SI SE QUIERE, si se hace desde aqui, se mueve todo al awake

}

void ListenerComponent::start()
{
	_listener->setUp(0, 1, 0);
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	_listener->setPosition(_tr->getPosition().getX(), _tr->getPosition().getY(), _tr->getPosition().getZ());
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