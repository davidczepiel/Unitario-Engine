#include "RigidBodyComponent.h"
#include "MotorFisico/RigidBody.h"
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
