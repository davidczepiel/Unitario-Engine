#include "RigidBodyComponent.h"
#include "Transform.h"
#include "MotorFisico/RigidBody.h"
#include "GameObject.h"

RigidBodyComponent::RigidBodyComponent(GameObject* go) :Component(3, go), _rb(nullptr), _tr(nullptr)
{
}

RigidBodyComponent::RigidBodyComponent(const std::string& path, GameObject* go) : Component(3, go), _rb(nullptr), _tr(nullptr)
{
}

RigidBodyComponent::RigidBodyComponent() : Component(3, nullptr), _rb(nullptr), _tr(nullptr)
{
}

RigidBodyComponent::~RigidBodyComponent()
{
	delete _rb; _rb = nullptr;
}

void RigidBodyComponent::setStaticFriction(float f)
{
	_rb->setStaticFriction(f);
}

void RigidBodyComponent::setDynamicFriction(float f)
{
	_rb->setDynamicFriction(f);
}

void RigidBodyComponent::setBounciness(float b)
{
	_rb->setBounciness(b);
}

void RigidBodyComponent::setMass(float m)
{
	_rb->setMass(m);
}

void RigidBodyComponent::setLinearVelocity(const Vector3& vel)
{
	_rb->setLinearVelocity(VEC3_TO_TUPLE(vel));
}

void RigidBodyComponent::setAngularVelocity(const Vector3& vel)
{
	_rb->setAngularVelocity(VEC3_TO_TUPLE(vel));
}

void RigidBodyComponent::setGravity(bool g)
{
	_rb->setGravity(g);
}

const Vector3& RigidBodyComponent::getAngularVelocity()
{
	return TUPLE_TO_VEC3(_rb->getAngularVelocity());
}









const Vector3& RigidBodyComponent::getLinearVelocity()
{
	return TUPLE_TO_VEC3(_rb->getLinearVelocity());
}

float RigidBodyComponent::getMass()
{
	{ return _rb->getMass(); }
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

void RigidBodyComponent::constrainX(bool constrain, bool linear)
{
	_rb->constrainX(constrain, linear);
}

void RigidBodyComponent::constrainY(bool constrain, bool linear)
{
	_rb->constrainY(constrain, linear);
}

void RigidBodyComponent::constrainZ(bool constrain, bool linear)
{
	_rb->constrainZ(constrain, linear);
}



