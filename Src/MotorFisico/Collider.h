#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

namespace physx {
	class PxPhysx;
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
	/// Contructor of the class
	/// </summary>
	Collider(bool isTrigger);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~Collider();

	/// <summary>
	/// Configures the collider so that it has a Box Geometry
	/// </summary>
	void setBoxCollider(int x, int y, int z);

	/// <summary>
	/// Configures the collider so that it has a Sphere Geometry
	/// </summary>
	void setSphereCollider(int radius);

	/// <summary>
	/// Configures the collider so that it is static
	/// </summary>
	void setStatic();

	/// <summary>
	/// Configures the collider so that it is dynamic
	/// </summary>
	void setDynamic();

	/// <summary>
	/// Configures the collider so that it is dynamic
	/// </summary>
	void setKinematic();

private:

	/// <summary>
	/// Configures the collider component so that it collides with other elements of the world
	/// </summary>
	void setColliderProperties();

	/// <summary>
	/// Configures the collider so that it operates as a Trigger
	/// </summary>
	void setTriggerProperties();

	physx::PxRigidActor* _mActor;
	physx::PxShape* _mShape;
	physx::PxPhysx* _pxPhysx;

	physx::PxVec3* position;

	bool _isTrigger;
};

#endif //!COLLIDER_H