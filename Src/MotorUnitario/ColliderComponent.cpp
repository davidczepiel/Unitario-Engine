#include "ColliderComponent.h"
#include "MotorFisico/Collider.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "Transform.h"

void ColliderComponent::awake(luabridge::LuaRef& data)
{
}

ColliderComponent::ColliderComponent(int id): Component(id, nullptr), _collider(nullptr)
{
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
	_collider->rotate(VEC3_TO_TUPLE(rot));
}

/////////////////////////////////////////////


BoxColliderComponent::BoxColliderComponent() : ColliderComponent(ComponentId::BoxCollider)
{
	_collider = new BoxCollider(1, 1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, std::tuple<float, float, float>(0.0f, 0.0f, 0.0f));
}

BoxColliderComponent::~BoxColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void BoxColliderComponent::awake(luabridge::LuaRef& data)
{
	int width = 2;
	if (LUAFIELDEXIST(Width)) width = GETLUAFIELD(Width, int);
	int height = 2;
	if (LUAFIELDEXIST(Height)) height = GETLUAFIELD(Height, int);
	int depth = 2;
	if (LUAFIELDEXIST(Depth)) depth = GETLUAFIELD(Depth, int);

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

	_collider = new BoxCollider(width, height, depth, isTrigger, _gameObject,
		gameObjectsCollision, gameObjectTriggered, pos, staticFriction, dynamicFriction, restitution);
}

void BoxColliderComponent::setScale(int width, int heigh, int depth)
{
	static_cast<BoxCollider*>(_collider)->setScale(width, heigh, depth);
}

////////////////////////////////////////////

SphereColliderComponent::SphereColliderComponent(): ColliderComponent(ComponentId::SphereCollider)
{
	_collider = new SphereCollider(1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, std::tuple<float,float,float>(0.0f,0.0f,0.0f));
}

SphereColliderComponent::~SphereColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void SphereColliderComponent::awake(luabridge::LuaRef& data)
{
	int radius = 2;
	if (LUAFIELDEXIST(Radius)) GETLUAFIELD(radius, int);

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

	_collider = new SphereCollider(radius, isTrigger, _gameObject,
		gameObjectsCollision, gameObjectTriggered, pos, staticFriction, dynamicFriction, restitution);
}

void SphereColliderComponent::setScale(int radius)
{
	static_cast<SphereCollider*>(_collider)->setScale(radius);
}

/////////////////////////////////////////////////////////


CapsuleColliderComponent::CapsuleColliderComponent() : ColliderComponent(ComponentId::CapsuleCollider)
{
	_collider = new CapsuleCollider(1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, std::tuple<float, float, float>(0.0f, 0.0f, 0.0f));
}

CapsuleColliderComponent::~CapsuleColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void CapsuleColliderComponent::awake(luabridge::LuaRef& data)
{
	int radius = 1;
	if (LUAFIELDEXIST(Radius)) radius = GETLUAFIELD(radius, int);
	int length = 3;
	if (LUAFIELDEXIST(Length)) length = GETLUAFIELD(length, int);

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

	_collider = new CapsuleCollider(radius, length, isTrigger, _gameObject,
		gameObjectsCollision, gameObjectTriggered, pos, staticFriction, dynamicFriction, restitution);
}

void CapsuleColliderComponent::setScale(int radius, int length)
{
	static_cast<CapsuleCollider*>(_collider)->setScale(radius, length);
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
