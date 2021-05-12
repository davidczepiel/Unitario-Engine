#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include "Component.h"
#include "Vector3.h"
#include <string>

class Logger;
class RigidBody;
class Vector3;
class Transform;
class GameObject;

class RigidBodyComponent :	public Component
{
public:
	enum Type{ Box, Capsule, Sphere};

	/// <summary>
	/// Constructor of the class
	/// </summary>
	RigidBodyComponent();

	virtual ~RigidBodyComponent();

	void awake(luabridge::LuaRef& data) override;
	/// <summary>
	/// Called each pshyical step to update physiscal information
	/// </summary>
	virtual void fixedUpdate() override;

	/// <summary>
	/// Called after every physic simulation (only sets the Transform)
	/// </summary>
	virtual void postFixedUpdate() override;

	/// <summary>
	/// Sets the position of the transform to a specified one
	/// </summary>
	void setPosition(Vector3 pos);

	/// <summary>
	/// Rotates the rigidbody
	/// <param name="rot">the vector to rotate by</param>
	/// </summary>
	void rotate(Vector3 rot);

	/// <summary>
	/// Sets the rotation of the transform to a specified one
	/// </summary>
	/// <param name="angle">the angle in radians to rotate</param>
	/// <param name="axis">the axis to rotate</param>
	void setRotation(Vector3 rot);

	/// <summary>
	/// Sets the scale of the transform to a specified one
	/// </summary>
	void setScale(Vector3 scale);

	/// <summary>
	/// Sets the body static friction if it's a dynamic rigid body
	/// </summary>
	/// <param name="f">The new static friction</param>
	void setStaticFriction(float f);

	/// <summary>
	/// Sets the body dynamic friction if it's a dynamic rigid body
	/// </summary>
	/// <param name="f">The new dynamic friction</param>
	void setDynamicFriction(float f);

	/// <summary>
	/// Sets the body bounciness if it's a dynamic rigid body
	/// </summary>
	/// <param name="b">The new bounciness</param>
	void setBounciness(float b);

	/// <summary>
	/// Sets the body mass if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="m">The new mass</param>
	void setMass(float m);

	/// <summary>
	/// Sets the body linear velocity if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="vel">The new velocity</param>
	void setLinearVelocity(const Vector3& vel);

	/// <summary>
	/// Sets the body angular velocity if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="vel">The new velocity</param>
	void setAngularVelocity(const Vector3& vel);

	/// <summary>
	/// Enables or disables the gravity
	/// </summary>
	/// <param name="g">true if gravity enabled</param>
	void setGravity(bool g);

	/// <summary>
	/// Gets the angular velocity of the body
	/// </summary>
	/// <returns>The angular velocity of the body</returns>
	const Vector3& getAngularVelocity();

	/// <summary>
	/// Gets the linear velocity of the body
	/// </summary>
	/// <returns>The linear velocity of the body</returns>
	const Vector3& getLinearVelocity();

	/// <summary>
	/// Gets the mass of the body
	/// </summary>
	/// <returns>The mass of the body</returns>
	float getMass();

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
	void constrainX(bool constrain, bool linear = true);

	/// <summary>
	/// Enables or disables the constraint in the rigid body y axis
	/// </summary>
	/// <param name="constrain">True to enable the constraint</param>
	/// <param name="linear">True to constrain the movement, false to constrain the rotation</param>
	void constrainY(bool constrain, bool linear = true);

	/// <summary>
	/// Enables or disables the constraint in the rigid body z axis
	/// </summary>
	/// <param name="constrain">True to enable the constraint</param>
	/// <param name="linear">True to constrain the movement, false to constrain the rotation</param>
	void constrainZ(bool constrain, bool linear = true);


	/// <summary>
	/// Callback for gameobject collision
	/// </summary>
	/// <param name="thisGO"></param>
	/// <param name="otherGO"></param>
	static void gameObjectsCollision(GameObject* thisGO, GameObject* otherGO);

private:

	void onEnable() override;

	void onDisable() override;

	RigidBody* _rb;
	Transform* _tr;
	Logger* _log;

	bool _constrainRotation;
};

#endif //!RIGIDBODYCOMPONENT_H
