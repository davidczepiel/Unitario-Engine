#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H
#define VEC3_TO_TUPLE(vec) std::tuple<float, float, float>(vec.getX(), vec.getY(), vec.getZ())
#define TUPLE_TO_VEC3(tuple) Vector3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))
#include "Component.h"
#include "Vector3.h"
#include "MotorFisico/RigidBody.h"
//class RigidBody;
class Vector3;
class Transform;
class RigidBodyComponent :
	public Component
{
public:
	virtual ~RigidBodyComponent();

	/// <summary>
	/// Sets the body static friction if it's a dynamic rigid body
	/// </summary>
	/// <param name="f">The new static friction</param>
	inline void setStaticFriction(float f) { _rb->setStaticFriction(f); }

	/// <summary>
	/// Sets the body dynamic friction if it's a dynamic rigid body
	/// </summary>
	/// <param name="f">The new dynamic friction</param>
	inline void setDynamicFriction(float f) { _rb->setDynamicFriction(f); }

	/// <summary>
	/// Sets the body bounciness if it's a dynamic rigid body
	/// </summary>
	/// <param name="b">The new bounciness</param>
	inline void setBounciness(float b) { _rb->setBounciness(b); }

	/// <summary>
	/// Sets the body mass if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="m">The new mass</param>
	inline void setMass(float m) { _rb->setMass(m); }

	/// <summary>
	/// Sets the body linear velocity if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="vel">The new velocity</param>
	inline void setLinearVelocity(const Vector3& vel) { _rb->setLinearVelocity(VEC3_TO_TUPLE(vel)); }

	/// <summary>
	/// Sets the body angular velocity if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="vel">The new velocity</param>
	inline void setAngularVelocity(const Vector3& vel) { _rb->setAngularVelocity(VEC3_TO_TUPLE(vel)); }

	/// <summary>
	/// Enables or disables the gravity
	/// </summary>
	/// <param name="g">true if gravity enabled</param>
	inline void setGravity(bool g) { _rb->setGravity(g); }

	/// <summary>
	/// Gets the angular velocity of the body
	/// </summary>
	/// <returns>The angular velocity of the body</returns>
	inline const Vector3& getAngularVelocity() {return TUPLE_TO_VEC3(_rb->getAngularVelocity()); }

	/// <summary>
	/// Gets the linear velocity of the body
	/// </summary>
	/// <returns>The linear velocity of the body</returns>
	inline const Vector3& getLinearVelocity() { return TUPLE_TO_VEC3(_rb->getLinearVelocity()); }

	/// <summary>
	/// Gets the mass of the body
	/// </summary>
	/// <returns>The mass of the body</returns>
	inline float getMass() { return _rb->getMass(); }

	/// <summary>
	/// Adds a force if it's a dynamic rigid body 
	/// </summary>
	/// <param name="force">The force to add</param>
	void addForce(Vector3& force);

	/// <summary>
	/// Adds an impulse if it's a dynamic rigid body 
	/// </summary>
	/// <param name="impulse">The impulse to add</param>
	void addImpulse(Vector3& impulse);

	/// <summary>
	/// Adds a torque if it's a dynamic rigid body
	/// </summary>
	/// <param name="torque">The torque to add</param>
	/// <returns>The new rotation of the object and if it's valid</returns>
	void addTorque(Vector3& torque);

	/// <summary>
	/// Moves the rigidBody to a point, (only if Kinematic)
	/// </summary>
	/// <param name="dest">The point where the rigidBody will be moved</param>
	/// <returns>The new position of the object and if it's valid</returns>
	void moveTo(Vector3& dest);

	/// <summary>
	/// Enables or disables the constraint in the rigid body x axis
	/// </summary>
	/// <param name="constrain">True to enable the constraint</param>
	/// <param name="linear">True to constrain the movement, false to constrain the rotation</param>
	inline void constrainX(bool constrain, bool linear = true) { _rb->constrainX(constrain, linear); }

	/// <summary>
	/// Enables or disables the constraint in the rigid body y axis
	/// </summary>
	/// <param name="constrain">True to enable the constraint</param>
	/// <param name="linear">True to constrain the movement, false to constrain the rotation</param>
	inline void constrainY(bool constrain, bool linear = true) { _rb->constrainY(constrain, linear); }

	/// <summary>
	/// Enables or disables the constraint in the rigid body z axis
	/// </summary>
	/// <param name="constrain">True to enable the constraint</param>
	/// <param name="linear">True to constrain the movement, false to constrain the rotation</param>
	inline void constrainZ(bool constrain, bool linear = true) { _rb->constrainZ(constrain, linear); }



private:
	RigidBody* _rb;
	Transform* _tr;
};
#endif //!RIGIDBODYCOMPONENT_H

