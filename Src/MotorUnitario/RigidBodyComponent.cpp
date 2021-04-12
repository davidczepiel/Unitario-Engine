#include "RigidBodyComponent.h"
#include "Transform.h"

RigidBodyComponent::~RigidBodyComponent()
{
	delete _rb; _rb = nullptr;
}

void RigidBodyComponent::addForce(Vector3& force)
{
	auto tupleForce = VEC3_TO_TUPLE(force);
	auto pos = _rb->addForce(tupleForce);
	//if the returned position was valid, apply it
	if (std::get<3>(pos))
		_tr->setPosition(TUPLE_TO_VEC3(pos));
}

void RigidBodyComponent::addImpulse(Vector3& impulse)
{
	auto tupleImpulse = VEC3_TO_TUPLE(impulse);
	auto pos = _rb->addImpulse(tupleImpulse);
	//if the returned position was valid, apply it
	if (std::get<3>(pos))
		_tr->setPosition(TUPLE_TO_VEC3(pos));
}

void RigidBodyComponent::addTorque(Vector3& torque)
{
	auto tupleTorque = VEC3_TO_TUPLE(torque);
	auto rotation = _rb->addTorque(tupleTorque);
	//if the returned position was valid, apply it
	if (std::get<3>(rotation))
		_tr->setRotation(TUPLE_TO_VEC3(rotation));
}

void RigidBodyComponent::moveTo(Vector3& dest)
{
	auto tupleDest = VEC3_TO_TUPLE(dest);
	auto pos = _rb->moveTo(tupleDest);
	//if the returned position was valid, apply it
	if (std::get<3>(pos))
		_tr->setPosition(TUPLE_TO_VEC3(pos));
}
