#include "Transform.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"

Transform::Transform(): Component(ComponentId::Transform), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

Transform::Transform(GameObject* gameObject): Component(ComponentId::Transform,gameObject), _position(0,0,0), _rotation(0,0,0),_scale(1,1,1)
{
}

Transform::Transform(GameObject* gameObject, const Vector3& position, const Vector3& rotation, const Vector3& scale): Component(ComponentId::Transform, gameObject), 
_position(position),_rotation(rotation),_scale(scale)
{
}

void Transform::setPosition(const Vector3& position)
{
	_position = position;
	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setPosition(_position);
	}

	ColliderComponent* boxColl = dynamic_cast<BoxColliderComponent*>(_gameObject->getComponent(ComponentId::BoxCollider));
	ColliderComponent* sphColl = dynamic_cast<SphereColliderComponent*>(_gameObject->getComponent(ComponentId::SphereCollider));
	ColliderComponent* capsColl = dynamic_cast<CapsuleColliderComponent*>(_gameObject->getComponent(ComponentId::CapsuleCollider));
	if (boxColl != nullptr) {
		boxColl->setPosition(_position);
	}
	else if (sphColl != nullptr) {
		sphColl->setPosition(_position);
	}
	else if (capsColl != nullptr) {
		capsColl->setPosition(_position);
	}
}

void Transform::updateFromPhysics(const Vector3& position, const Vector3& rotation)
{
	_position = position;
	_rotation = rotation;
}

void Transform::setRotation(const Vector3& rotation)
{
	_rotation = rotation;

	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setRotation(_rotation);
	}

	ColliderComponent* boxColl = dynamic_cast<BoxColliderComponent*>(_gameObject->getComponent(ComponentId::BoxCollider));
	ColliderComponent* sphColl = dynamic_cast<SphereColliderComponent*>(_gameObject->getComponent(ComponentId::SphereCollider));
	ColliderComponent* capsColl = dynamic_cast<CapsuleColliderComponent*>(_gameObject->getComponent(ComponentId::CapsuleCollider));
	if (boxColl != nullptr) {
		boxColl->setPosition(_position);
	}
	else if (sphColl != nullptr) {
		sphColl->setPosition(_position);
	}
	else if (capsColl != nullptr) {
		capsColl->setPosition(_position);
	}
Transform::~Transform()
{
}