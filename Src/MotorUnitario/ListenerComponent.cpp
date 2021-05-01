#include "ListenerComponent.h"
#include "MotorAudio/Listener.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"
#include "Logger.h"
#include "includeLUA.h"

ListenerComponent::ListenerComponent() :Component(ComponentId::ListenerComponent), _tr(nullptr), _listener(new Listener())
{

}

ListenerComponent::~ListenerComponent()
{
	delete _listener; _listener = nullptr;
}

void ListenerComponent::awake(luabridge::LuaRef& data)
{
	if (LUAFIELDEXIST(ListenerNumber))
		_listener->setListenerNumber(GETLUAFIELD(ListenerNumber, int));
	else throw "Can't assign a default listener number.";
	if (LUAFIELDEXIST(Velocity)) {
		float x, y, z;
		x = y = z = 0;
		if (!data["Velocity"]["X"].isNil())
			x = data["Velocity"]["X"].cast<float>();
		if (!data["Velocity"]["Y"].isNil())
			y = data["Velocity"]["Y"].cast<float>();
		if (!data["Velocity"]["Z"].isNil())
			z = data["Velocity"]["Z"].cast<float>();

		_listener->setVelocity(x, y, z);
	}
	if (LUAFIELDEXIST(Forward)) {
		float x, y, z;
		x = 1;
		y = z = 0;
		if (!data["Forward"]["X"].isNil())
			x = data["Forward"]["X"].cast<float>();
		if (!data["Forward"]["Y"].isNil())
			y = data["Forward"]["Y"].cast<float>();
		if (!data["Forward"]["Z"].isNil())
			z = data["Forward"]["Z"].cast<float>();

		_listener->setForward(x, y, z);
	}
	if (LUAFIELDEXIST(Forward)) {
		float x, y, z;
		y = 1;
		x = z = 0;
		if (!data["Up"]["X"].isNil())
			x = data["Up"]["X"].cast<float>();
		if (!data["Up"]["Y"].isNil())
			y = data["Up"]["Y"].cast<float>();
		if (!data["Up"]["Z"].isNil())
			z = data["Up"]["Z"].cast<float>();

		_listener->setUp(x, y, z);
	}
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