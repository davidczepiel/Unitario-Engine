#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#define VEC3_TO_TUPLE(vec) std::tuple<float, float, float>(vec.getX(), vec.getY(), vec.getZ())
#define TUPLE_TO_VEC3(tuple) Vector3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))

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
	/// <param name="go">Gameobject this component is attached to</param>
	RigidBodyComponent(GameObject* go, Type type);

	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="path">Path of configuration file</param>
	/// <param name="go">Gameobject this component is attached to</param>
	RigidBodyComponent(const std::string& path, GameObject* go);

	/// <summary>
	/// Constructor of the class
	/// </summary>
	RigidBodyComponent();

	virtual ~RigidBodyComponent();

	/// <summary>
	/// Called each pshyical step to update physiscal information
	/// </summary>
	virtual void fixedUpdate();

	/// <summary>
	/// Sets the position of the transform to a specified one
	/// </summary>
	void setPosition(Vector3 pos);

	/// <summary>
	/// Sets the rotation of the transform to a specified one
	/// </summary>
	void setRotation(Vector3 pos);

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
	RigidBody* _rb;
	Transform* _tr;
	Logger* _log;
	Type _type;

};
#endif //!RIGIDBODYCOMPONENT_H
