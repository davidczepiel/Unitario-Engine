#include "Transform.h"
#include "ComponentIDs.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"

Transform::Transform(GameObject* gameObject) :Component(0, gameObject), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale, GameObject* gameObject) : Component(0, gameObject),
_position(position), _rotation(rotation), _scale(scale)
{
}

Transform::~Transform()
{
}

void Transform::setPosition(const Vector3& position)
{
	_position = position;
	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setPosition(_position);
	}

	ColliderComponent* coll = dynamic_cast<ColliderComponent*>(_gameObject->getComponent(ComponentId::Collider));
	if (coll != nullptr) {
		coll->setPosition(_position);
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

	ColliderComponent* coll = dynamic_cast<ColliderComponent*>(_gameObject->getComponent(ComponentId::Collider));
	if (coll != nullptr) {
		coll->setRotation(_rotation);
	}
}