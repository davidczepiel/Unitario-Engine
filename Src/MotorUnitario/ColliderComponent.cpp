#include "ColliderComponent.h"
#include "MotorFisico/Collider.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "Transform.h"
#include "includeLUA.h"

ColliderComponent::ColliderComponent(int id) : Component(id, nullptr), _collider(nullptr)
{
}

void ColliderComponent::onEnable()
{
	_collider->enable();
}

void ColliderComponent::onDisable()
{
	_collider->disable();
}

ColliderComponent::~ColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void ColliderComponent::setCollider() {
	_collider->setCollider();
}

void ColliderComponent::setTrigger() {
	_collider->setTrigger();
}

void ColliderComponent::setPosition(Vector3 pos)
{
	_collider->setPosition(VEC3_TO_TUPLE(pos));
}

void ColliderComponent::setRotation(Vector3 rot)
{
	_collider->setRotation(VEC3_TO_TUPLE(rot));
}

/////////////////////////////////////////////


BoxColliderComponent::BoxColliderComponent() : ColliderComponent(ComponentId::BoxCollider)
{

}


void BoxColliderComponent::awake(luabridge::LuaRef& data)
{
	float width = 2;
	if (LUAFIELDEXIST(Width)) width = GETLUAFIELD(Width, float);
	float height = 2;
	if (LUAFIELDEXIST(Height)) height = GETLUAFIELD(Height, float);
	float depth = 2;
	if (LUAFIELDEXIST(Depth)) depth = GETLUAFIELD(Depth, float);

	bool isTrigger = false;
	if (LUAFIELDEXIST(IsTrigger)) isTrigger = GETLUAFIELD(IsTrigger, bool);

	float staticFriction = 0.5f;
	if (LUAFIELDEXIST(StaticFriction)) staticFriction = GETLUAFIELD(StaticFriction, float);
	float dynamicFriction = 0.5f;
	if (LUAFIELDEXIST(DynamicFriction)) dynamicFriction = GETLUAFIELD(DynamicFriction, float);
	float restitution = 0.5f;
	if (LUAFIELDEXIST(Restitution)) restitution = GETLUAFIELD(Restitution, float);

	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	std::tuple<float, float, float> pos = VEC3_TO_TUPLE(t->getPosition());
	std::tuple<float, float, float> rot = VEC3_TO_TUPLE(t->getRotation());

	_collider = new BoxCollider(width, height, depth, isTrigger, _gameObject, _gameObject->getName(),
		gameObjectsCollision, gameObjectTriggered, pos, staticFriction, dynamicFriction, restitution);
	_collider->setRotation(rot);
}

void BoxColliderComponent::setScale(float width, float heigh, float depth)
{
	static_cast<BoxCollider*>(_collider)->setScale(width, heigh, depth);
}

float BoxColliderComponent::getWidth()
{
	return static_cast<BoxCollider*>(_collider)->getWidth();
}

float BoxColliderComponent::getHeight()
{
	return static_cast<BoxCollider*>(_collider)->getHeight();

}

float BoxColliderComponent::getDepth()
{
	return static_cast<BoxCollider*>(_collider)->getDepth();

}

////////////////////////////////////////////

SphereColliderComponent::SphereColliderComponent() : ColliderComponent(ComponentId::SphereCollider)
{

}


void SphereColliderComponent::awake(luabridge::LuaRef& data)
{
	float radius = 2;
	if (LUAFIELDEXIST(Radius))radius = GETLUAFIELD(Radius, float);

	bool isTrigger = false;
	if (LUAFIELDEXIST(IsTrigger)) isTrigger = GETLUAFIELD(IsTrigger, bool);

	float staticFriction = 0.5f;
	if (LUAFIELDEXIST(StaticFriction)) staticFriction = GETLUAFIELD(StaticFriction, float);
	float dynamicFriction = 0.5f;
	if (LUAFIELDEXIST(DynamicFriction)) dynamicFriction = GETLUAFIELD(DynamicFriction, float);
	float restitution = 0.5f;
	if (LUAFIELDEXIST(Restitution)) restitution = GETLUAFIELD(Restitution, float);

	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	std::tuple<float, float, float> pos = VEC3_TO_TUPLE(t->getPosition());
	std::tuple<float, float, float> rot = VEC3_TO_TUPLE(t->getRotation());

	_collider = new SphereCollider(radius, isTrigger, _gameObject, _gameObject->getName(),
		gameObjectsCollision, gameObjectTriggered, pos, staticFriction, dynamicFriction, restitution);
	_collider->setRotation(rot);
}

void SphereColliderComponent::setScale(float radius)
{
	static_cast<SphereCollider*>(_collider)->setScale(radius);
}

float SphereColliderComponent::getRadius()
{
	return static_cast<SphereCollider*>(_collider)->getRadius();

}

/////////////////////////////////////////////////////////


CapsuleColliderComponent::CapsuleColliderComponent() : ColliderComponent(ComponentId::CapsuleCollider)
{

}

void CapsuleColliderComponent::awake(luabridge::LuaRef& data)
{
	float radius = 1;
	if (LUAFIELDEXIST(Radius)) radius = GETLUAFIELD(radius, float);
	float length = 3;
	if (LUAFIELDEXIST(Length)) length = GETLUAFIELD(length, float);

	bool isTrigger = false;
	if (LUAFIELDEXIST(IsTrigger)) isTrigger = GETLUAFIELD(isTrigger, bool);

	float staticFriction = 0.5f;
	if (LUAFIELDEXIST(StaticFriction)) staticFriction = GETLUAFIELD(staticFriction, float);
	float dynamicFriction = 0.5f;
	if (LUAFIELDEXIST(DynamicFriction)) dynamicFriction = GETLUAFIELD(dynamicFriction, float);
	float restitution = 0.5f;
	if (LUAFIELDEXIST(Restitution)) restitution = GETLUAFIELD(restitution, float);

	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	std::tuple<float, float, float> pos = VEC3_TO_TUPLE(t->getPosition());
	std::tuple<float, float, float> rot = VEC3_TO_TUPLE(t->getRotation());

	_collider = new CapsuleCollider(radius, length, isTrigger, _gameObject, _gameObject->getName(),
		gameObjectsCollision, gameObjectTriggered, pos, staticFriction, dynamicFriction, restitution);
	_collider->setRotation(rot);
}

void CapsuleColliderComponent::setScale(float radius, float length)
{
	static_cast<CapsuleCollider*>(_collider)->setScale(radius, length);
}

float CapsuleColliderComponent::getRadius()
{
	return static_cast<CapsuleCollider*>(_collider)->getRadius();

}

float CapsuleColliderComponent::getHeight()
{
	return static_cast<CapsuleCollider*>(_collider)->getHeight();

}

void ColliderComponent::gameObjectsCollision(GameObject* thisGO, GameObject* otherGO)
{
	thisGO->onCollision(otherGO);
	otherGO->onCollision(thisGO);
}

void ColliderComponent::gameObjectTriggered(GameObject* thisGO, GameObject* otherGO)
{
	thisGO->onTrigger(otherGO);
	otherGO->onTrigger(thisGO);
}
