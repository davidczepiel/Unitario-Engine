#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H
#define VEC3_TO_TUPLE(vec) std::tuple<float, float, float>(vec.getX(), vec.getY(), vec.getZ())
#define TUPLE_TO_VEC3(tuple) Vector3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))
#include "Component.h"
#include "Vector3.h"
class RigidBody;
class Vector3;
class Transform;
class RigidBodyComponent :
	public Component
{
public:
	virtual ~RigidBodyComponent();

	/// <summary>
	/// Adds a force if it's a dynamic rigid body 
	/// </summary>
	/// <param name="force">The force to add</param>
	void addForce(Vector3& force);

	/// <summary>
	/// Adds an impulse if it's a dynamic rigid body 
	/// </summary>
	/// <param name="impulse">The impulse to add</param>
	//void addImpulse(Vector3& impulse);

private:
	RigidBody* _rb;
	Transform* _tr;
};
#endif //!RIGIDBODYCOMPONENT_H

