#pragma once
#include <list>
#include <tuple>
#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#define TUPLE_TO_PHYSXVEC3(tuple) physx::PxVec3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))
namespace physx {

	class PxPhysics;
	class PxRigidBody;
	class PxRigidDynamic;
	class PxRigidStatic;
	class PxShape;
	class PxPhysicsAPI;
	class PxTransform;
	class PxMaterial;
	class PxScene;
};
//#include "PxPhysics.h"
//#include "PxRigidBody.h"
//#include "PxRigidDynamic.h"
class RigidBody
{
public:
	/// <summary>
	/// creates a dynamic spherical rigidBody
	/// </summary>
	/// <param name="radious">The radious of the sphere</param>
	/// <param name="isStatic">Set true if a static rigid body needed; false if dynamic rigid body needed</param>
	/// <param name="position">The object initial position</param>
	/// <param name="isKinematic">Set true if a kinematic rigid body needed</param>
	/// <param name="linearDamping">The linear damping of the body</param>
	/// <param name="angularDamping">The angular damping  of the body</param>
	/// <param name="staticFriction">The static friction, between 0 and 3.4 e 38. 
	/// Static friction defines the amount of friction that is applied between surfaces that are not moving lateral to each-other</param>
	/// <param name="dynamicFriction">The dynamic friction, between 0 and 3.4 e 38.
	/// Dynamic friction defines the amount of friction applied between surfaces that are moving relative to each-other</param>
	/// <param name="restitution">The bounciness, between 0 and 1</param>
	/// <param name="mass">The mass of the sphere</param>

	RigidBody(float radious, bool isStatic = false, std::tuple<float, float, float> position = std::tuple<float, float, float>(0, 0, 0), 
		bool isKinematic = false, float linearDamping = 0, float angularDamping = 0, float staticFriction = 1.0f, 
		float dynamicFriction = 1.0f, float restitution = 1.0f, float mass = 1000.0f);

	/// <summary>
	/// creates a dynamic box rigidBody
	/// </summary>
	/// <param name="width">The width of the box</param>
	/// <param name="height">The height of the box</param>
	/// <param name="depth">The depth of the box</param>
	/// <param name="isStatic">Set true if a static rigid body needed; false if dynamic rigid body needed</param>
	/// <param name="position">The object initial position</param>
	/// <param name="isKinematic">Set true if a kinematic rigid body needed</param>
	/// <param name="linearDamping">The linear damping of the body</param>
	/// <param name="angularDamping">The angular damping  of the body</param>
	/// <param name="staticFriction">The static friction, between 0 and 3.4 e 38. 
	/// Static friction defines the amount of friction that is applied between surfaces that are not moving lateral to each-other</param>
	/// <param name="dynamicFriction">The dynamic friction, between 0 and 3.4 e 38.
	/// Dynamic friction defines the amount of friction applied between surfaces that are moving relative to each-other</param>
	/// <param name="restitution">The bounciness, between 0 and 1</param>
	/// <param name="mass">The mass of the sphere</param>

	RigidBody(float width, float height, float depth, bool isStatic = false, 
		std::tuple<float, float, float> position = std::tuple<float, float, float>(0, 0, 0), bool isKinematic = false, 
		float linearDamping = 0, float angularDamping = 0, float staticFriction = 1.0f, float dynamicFriction = 1.0f,
		float restitution = 1.0f, float mass = 1000.0f);

	/// <summary>
	/// creates a dynamic capsule rigidBody
	/// </summary>
	/// <param name="radious">The radious of the capsule</param>
	/// <param name="height">The height of the capsule</param>
	/// <param name="isStatic">Set true if a static rigid body needed; false if dynamic rigid body needed</param>
	/// <param name="position">The object initial position</param>
	/// <param name="isKinematic">Set true if a kinematic rigid body needed</param>
	/// <param name="staticFriction">The static friction, between 0 and 3.4 e 38. 
	/// Static friction defines the amount of friction that is applied between surfaces that are not moving lateral to each-other</param>
	/// <param name="dynamicFriction">The dynamic friction, between 0 and 3.4 e 38.
	/// Dynamic friction defines the amount of friction applied between surfaces that are moving relative to each-other</param>
	/// <param name="restitution">The bounciness, between 0 and 1</param>
	/// <param name="mass">The mass of the sphere</param>
	RigidBody(float radious, float height, bool isStatic = false,
		std::tuple<float, float, float> position = std::tuple<float, float, float>(0, 0, 0), bool isKinematic = false, float linearDamping = 0,
		float AngularDamping = 0, float staticFriction = 1.0f, float dynamicFriction = 1.0f, float restitution = 1.0f, float mass = 1000.0f);

	~RigidBody();

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
	void setLinearVelocity(std::tuple<float, float, float>vel);

	/// <summary>
	/// Sets the body angular velocity if it's a dynamic rigid body (static rigid bodies don't have mass)
	/// </summary>
	/// <param name="vel">The new velocity</param>
	void setAngularVelocity(std::tuple<float, float, float>vel);


	/// <summary>
	/// Enables or disables the gravity
	/// </summary>
	/// <param name="g">true if gravity enabled</param>
	void setGravity(bool g);
	/// <summary>
	/// Adds a force if it's a dynamic rigid body 
	/// </summary>
	/// <param name="force">The force to add</param>
	std::tuple<float, float, float, bool> addForce(std::tuple<float, float, float>& force);

	/// <summary>
	/// Adds an impulse if it's a dynamic rigid body 
	/// </summary>
	/// <param name="impulse">The impulse to add</param>
	std::tuple<float, float, float, bool> addImpulse(std::tuple<float, float, float>& impulse);

	/// <summary>
	/// Adds a torque if it's a dynamic rigid body
	/// </summary>
	/// <param name="torque">The torque to add</param>
	/// <returns>The new rotation of the object and if it's valid</returns>
	std::tuple<float, float, float, bool> addTorque(std::tuple<float, float, float>& torque);

	/// <summary>
	/// Moves the rigidBody to a point, (only if Kinematic)
	/// </summary>
	/// <param name="dest">The point where the rigidBody will be moved</param>
	/// <returns>The new position of the object and if it's valid</returns>
	
	std::tuple<float,float,float,bool> moveTo(std::tuple<float, float, float>& dest);

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


private:
	/// <summary>
	/// Configures a shape to avoid collision detection and scene queries (raycasts, sweeps and overlays)
	/// </summary>
	/// <param name="shape">The shape to modify</param>
	void setFlags(physx::PxShape* shape);

	/// <summary>
	/// used for physic parameters initialization
	/// </summary>
	/// <param name="x">The x component of the position</param>
	/// <param name="y">The y component of the position</param>
	/// <param name="z">The z component of the position</param>
	/// <param name="mass">The mass of the body</param>
	/// <param name="linearDamping">The linear damping of the body</param>
	/// <param name="angularDamping">The angular damping  of the body</param>

	void initParams(std::tuple<float, float, float> pos, float mass, bool isKinematic, float linearDamping, float angularDamping);
	/// <summary>
	/// gets all materials from the dynamic rigidBody
	/// </summary>
	/// <returns></returns>
	std::list<physx::PxMaterial*>getAllMaterials();

	physx::PxPhysics* _physx;
	physx::PxScene* _scene;
	physx::PxTransform* _transform;
	physx::PxRigidDynamic* _dynamicBody;
	physx::PxRigidStatic* _staticBody;
	bool _isStatic;
};
#endif //!RIGIDBODY_H