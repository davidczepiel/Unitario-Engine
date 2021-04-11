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

class Collider
{
public:

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~Collider(){}

	/// <summary>
	/// Configures the collider component so that it collides with other elements of the world
	/// </summary>
	void setCollider();

	/// <summary>
	/// Configures the collider so that it operates as a Trigger
	/// </summary>
	void setTrigger();

protected:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="isTrigger">Shape is initially a trigger</param>
	/// <param name="staticFriction">Static friction of the shape</param>
	/// <param name="dynamicFriction">Dynamic friction of the shape</param>
	/// <param name="restitution">Shape's restitution coefficient</param>
	Collider(bool isTrigger, float staticFriction, float dynamicFriction, float restitution);

	physx::PxShape* _mShape;
	bool _isTrigger;
};

class BoxCollider : public Collider {
public:
	BoxCollider(int width, int heigh, int depth, bool isTrigger,
		float staticFriction = 0.5f, float dynamicFriction = 0.5f, float restitution = 0.5f);
	virtual ~BoxCollider(){}
	void setScale(int x, int y, int z);

};

class SphereCollider : public Collider {
public:
	SphereCollider(int r, bool isTrigger,float staticFriction=0.5, float dynamicFriction=0.5 , float restitution=0.5);
	virtual ~SphereCollider(){}
	void setScale(int r);

};

class CapsuleCollider : public Collider {
public:
	CapsuleCollider(int radius, int length, bool isTrigger,float staticFriction=0.5, float dynamicFriction=0.5 , float restitution=0.5);
	virtual ~CapsuleCollider(){}
	void setScale(int r, int l);

};

#endif //!COLLIDER_H