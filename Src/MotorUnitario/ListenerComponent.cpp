#include "ListenerComponent.h"
#include "MotorAudio/Listener.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"

ListenerComponent::ListenerComponent(GameObject* gameObject):Component(ComponentId::ListenerComponent,gameObject), _tr(nullptr), _listener(new Listener())
{
}

ListenerComponent::~ListenerComponent()
{
	delete _listener;
	delete _tr;
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
	//_listener = new Listener();
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	_listener->setPosition(_tr->getPosition().getX(), _tr->getPosition().getY(), _tr->getPosition().getZ());
}

void ListenerComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_listener->setPosition(x,y,z);

	float xR = static_cast<float>(_tr->getRotation().getX());
	float yR = static_cast<float>(_tr->getRotation().getY());
	float zR = static_cast<float>(_tr->getRotation().getZ());
	_listener->setForward(xR,0,zR);
	_listener->setUp(xR,yR,0);
}

void ListenerComponent::lateUpdate()
{
	_listener->update();
}

void ListenerComponent::setListenerNumber(int listenNumber)
{
	_listener->setListenerNumber(listenNumber);
}
