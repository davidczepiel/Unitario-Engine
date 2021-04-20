#include "ColliderComponent.h"
#include "MotorFisico/Collider.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "Transform.h"

ColliderComponent::ColliderComponent(int id, GameObject* gameObject) : Component(id, gameObject), _collider(nullptr)
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

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject) : ColliderComponent(ComponentId::BoxCollider, gameObject)
{
	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	_collider = new BoxCollider(1, 1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, VEC3_TO_TUPLE(t->getPosition()));
}

BoxColliderComponent::BoxColliderComponent() : ColliderComponent(ComponentId::BoxCollider, nullptr)
{
	_collider = new BoxCollider(1, 1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, std::tuple<float, float, float>(0.0f, 0.0f, 0.0f));
}

BoxColliderComponent::~BoxColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void BoxColliderComponent::setScale(int width, int heigh, int depth)
{
	static_cast<BoxCollider*>(_collider)->setScale(width, heigh, depth);
}

////////////////////////////////////////////

SphereColliderComponent::SphereColliderComponent(GameObject* gameObject) : ColliderComponent(ComponentId::SphereCollider, gameObject)
{
	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	_collider = new SphereCollider(1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, VEC3_TO_TUPLE(t->getPosition()));
}

SphereColliderComponent::SphereColliderComponent(): ColliderComponent(ComponentId::SphereCollider, nullptr)
{
	_collider = new SphereCollider(1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, std::tuple<float,float,float>(0.0f,0.0f,0.0f));
}

SphereColliderComponent::~SphereColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void SphereColliderComponent::setScale(int radius)
{
	static_cast<SphereCollider*>(_collider)->setScale(radius);
}

/////////////////////////////////////////////////////////

CapsuleColliderComponent::CapsuleColliderComponent(GameObject* gameObject) : ColliderComponent(ComponentId::CapsuleCollider, gameObject)
{
	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	_collider = new CapsuleCollider(1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, VEC3_TO_TUPLE(t->getPosition()));
}

CapsuleColliderComponent::CapsuleColliderComponent() : ColliderComponent(ComponentId::CapsuleCollider, nullptr)
{
	_collider = new CapsuleCollider(1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered, std::tuple<float, float, float>(0.0f, 0.0f, 0.0f));
}

CapsuleColliderComponent::~CapsuleColliderComponent()
{
	delete _collider; _collider == nullptr;
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
