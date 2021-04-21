#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

#include <tuple>

namespace physx {
	class PxPhysics;
	class PxShape;
	class PxRigidDynamic;
	class PxRigidActor;
	class PxVec3;
	class PxTransform;
}

class Transform;
class GameObject;

using ContactCallback = void(GameObject* thisGO, GameObject* otherGO);

#define TUPLE_TO_PHYSXVEC3(tuple) physx::PxVec3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))
#define PHYSXVEC3_TO_TUPLE(vec) std::tuple<float,float,float>(vec.x,vec.y,vec.z)

class Collider
{
public:

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~Collider() { delete _pxTrans; _pxTrans = nullptr; }

	/// <summary>
	/// Configures the collider component so that it collides with other elements of the world
	/// </summary>
	void setCollider();

	/// <summary>
	/// Configures the collider so that it operates as a Trigger
	/// </summary>
	void setTrigger();

	/// <summary>
	/// Get the GameObject owner of the component owning thre collider
	/// </summary>
	/// <returns>A pointer to the GameObject owner of the component owning thre collider</returns>
	inline GameObject* getGameObject() const { return _gameObject; }

	/// <summary>
	/// Set the pointer to the GameObject used on callbacks
	/// </summary>
	/// <param name="go"></param>
	inline void setGameObject(GameObject* go) { _gameObject = go; }

	/// <summary>
	/// Returns a pointer to the function called on collision if the collider is not a trigger
	/// </summary>
	/// <returns>A pointer to the function called on collision</returns>
	inline ContactCallback* getColliderCallback() const { return _contCallback; }

	/// <summary>
	/// Returns a pointer to the function called on collision if the collider is a trigger
	/// </summary>
	/// <returns>A pointer to the function called on trigger</returns>
	inline ContactCallback* getTriggerCallback() const { return _triggerCallback; }

	/// <summary>
	/// Sets the transform position to a specified one
	/// </summary>
	/// <param name="position">Set of values that determine the position</param>
	void setPosition(const std::tuple<float, float, float>& position);

	/// <summary>
	/// Sets the transform rotation to a specified one
	/// </summary>
	/// <param name="position">Set of values that determine the position</param>
	void rotate(const std::tuple<float, float, float>& rotation);

	/// <summary>
	/// Sets collider's material to given parameters
	/// </summary>
	/// <param name="staticFriction">friction coefficient when collider is not moving</param>
	/// <param name="dynamicFriction">friction coefficient when collider is moving</param>
	/// <param name="restitution">restitution coefficient</param>
	void setMaterial(float staticFriction, float dynamicFriction, float restitution);

protected:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="isTrigger">True if shape is initially a trigger</param>
	/// <param name="staticFriction">Static friction of the shape</param>
	/// <param name="dynamicFriction">Dynamic friction of the shape</param>
	/// <param name="restitution">Shape's restitution coefficient</param>
	Collider(bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		float staticFriction, float dynamicFriction, float restitution, const std::tuple<float, float, float>& position);

	physx::PxShape* _mShape;
	physx::PxTransform* _pxTrans;
	GameObject* _gameObject;
	ContactCallback* _contCallback;
	ContactCallback* _triggerCallback;
	
	bool _isTrigger;
};

class BoxCollider : public Collider {
public:
	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="width">Width of the collider</param>
	/// <param name="heigh">Height of the collider</param>
	/// <param name="depth">Depth of the collider</param>
	/// <param name="isTrigger">True if shape is initially a trigger</param>
	/// <param name="gameObject">Pointer to the GameObject owning the component, used for collision callbacks</param>
	/// <param name="colliderCallback">Pointer to the function called on collision if collider is not a trigger</param>
	/// <param name="triggerCallback">Pointer to the function called on collision if collider is a trigger</param>
	/// <param name="position">Position of the GameObject owning the component</param>
	/// <param name="staticFriction">Static friction of the shape</param>
	/// <param name="dynamicFriction">Dynamic friction of the shape</param>
	/// <param name="restitution">Shape's restitution coefficient</param>
	BoxCollider(int width, int heigh, int depth, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		const std::tuple<float, float, float>& position, float staticFriction = 0.5f, float dynamicFriction = 0.5f, float restitution = 0.5f);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~BoxCollider() {}

	/// <summary>
	/// Changes box size
	/// </summary>
	/// <param name="x">New width</param>
	/// <param name="y">New height</param>
	/// <param name="z">New depth</param>
	void setScale(int x, int y, int z);
};

class SphereCollider : public Collider {
public:
	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="r">Sphere's radius</param>
	/// <param name="isTrigger">True if shape is initially a trigger</param>
	/// <param name="gameObject">Pointer to the GameObject owning the component, used for collision callbacks</param>
	/// <param name="colliderCallback">Pointer to the function called on collision if collider is not a trigger</param>
	/// <param name="triggerCallback">Pointer to the function called on collision if collider is a trigger</param>
	/// <param name="position">Position of the GameObject owning the component</param>
	/// <param name="staticFriction">Static friction of the shape</param>
	/// <param name="dynamicFriction">Dynamic friction of the shape</param>
	/// <param name="restitution">Shape's restitution coefficient</param>
	SphereCollider(int r, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		const std::tuple<float, float, float>& position, float staticFriction = 0.5, float dynamicFriction = 0.5, float restitution = 0.5);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~SphereCollider() {}

	/// <summary>
	/// Changes sphere radius
	/// </summary>
	/// <param name="r">New new radius</param>
	void setScale(int r);
};

class CapsuleCollider : public Collider {
public:
	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="radius">Capsule's radius</param>
	/// <param name="length">Capsule's length</param>
	/// <param name="isTrigger">True if shape is initially a trigger</param>
	/// <param name="gameObject">Pointer to the GameObject owning the component, used for collision callbacks</param>
	/// <param name="colliderCallback">Pointer to the function called on collision if collider is not a trigger</param>
	/// <param name="triggerCallback">Pointer to the function called on collision if collider is a trigger</param>
	/// <param name="position">Position of the GameObject owning the component</param>
	/// <param name="staticFriction">Static friction of the shape</param>
	/// <param name="dynamicFriction">Dynamic friction of the shape</param>
	/// <param name="restitution">Shape's restitution coefficient</param>
	CapsuleCollider(int radius, int length, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		const std::tuple<float, float, float>& position, float staticFriction = 0.5, float dynamicFriction = 0.5, float restitution = 0.5);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~CapsuleCollider() {}

	/// <summary>
	/// Changes capsule's dimensions
	/// </summary>
	/// <param name="r">New radius</param>
	/// <param name="l">New length</param>
	void setScale(int r, int l);
};

#endif //!COLLIDER_H