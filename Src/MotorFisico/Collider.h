#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

namespace physx {
	class PxPhysics;
	class PxShape;
	class PxRigidDynamic;
	class PxRigidActor;
	class PxVec3;
}

class Transform;
class GameObject;

using ContactCallback = void(GameObject* thisGO, GameObject* otherGO);

class Collider
{
public:

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~Collider() {}

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

	inline ContactCallback* getColliderCallback() const { return _contCallback; }

	inline ContactCallback* getTriggerCallback() const { return _triggerCallback; }

protected:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="isTrigger">Shape is initially a trigger</param>
	/// <param name="staticFriction">Static friction of the shape</param>
	/// <param name="dynamicFriction">Dynamic friction of the shape</param>
	/// <param name="restitution">Shape's restitution coefficient</param>
	Collider(bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		float staticFriction, float dynamicFriction, float restitution);

	physx::PxShape* _mShape;
	bool _isTrigger;
	GameObject* _gameObject;
	ContactCallback* _contCallback;
	ContactCallback* _triggerCallback;
};

class BoxCollider : public Collider {
public:
	BoxCollider(int width, int heigh, int depth, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		float staticFriction = 0.5f, float dynamicFriction = 0.5f, float restitution = 0.5f);
	virtual ~BoxCollider() {}
	void setScale(int x, int y, int z);
};

class SphereCollider : public Collider {
public:
	SphereCollider(int r, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		float staticFriction = 0.5, float dynamicFriction = 0.5, float restitution = 0.5);
	virtual ~SphereCollider() {}
	void setScale(int r);
};

class CapsuleCollider : public Collider {
public:
	CapsuleCollider(int radius, int length, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
		float staticFriction = 0.5, float dynamicFriction = 0.5, float restitution = 0.5);
	virtual ~CapsuleCollider() {}
	void setScale(int r, int l);
};

#endif //!COLLIDER_H