#include "ColliderComponent.h"
#include "MotorFisico/Collider.h"
#include "GameObject.h"
//#include "ComponentIDs.h"

ColliderComponent::ColliderComponent(int id, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject)
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

/////////////////////////////////////////////

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject) : ColliderComponent(/*ComponentId::ImageRender*/1, gameObject)
{
	_collider = new BoxCollider(1, 1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered);
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

SphereColliderComponent::SphereColliderComponent(GameObject* gameObject) : ColliderComponent(/*ComponentId::ImageRender*/1, gameObject)
{
	_collider = new SphereCollider(1, false, _gameObject, gameObjectsCollision, gameObjectTriggered);
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

CapsuleColliderComponent::CapsuleColliderComponent(GameObject* gameObject) : ColliderComponent(/*ComponentId::ImageRender*/1, gameObject)
{
	_collider = new CapsuleCollider(1, 1, false, _gameObject, gameObjectsCollision, gameObjectTriggered);
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
