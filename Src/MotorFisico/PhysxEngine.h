#pragma once
#ifndef PHYSXENGINE_H
#define PHYSXENGINE_H

namespace physx {
	class PxFoundation;
	class PxPhysics;
	class PxCooking;
	class PxPvd;
	class PxScene;
};
class PhysxEngine {
public:
	~PhysxEngine();
	static PhysxEngine* getPxInstance();
	void operator=(const PhysxEngine&) = delete;
	PhysxEngine(PhysxEngine& other) = delete;

	void init();
	void update(float time);
	physx::PxScene* getScene();
	
private:

	/// <summary>
	/// Constructor of the class
	/// </summary>
	PhysxEngine();
	static PhysxEngine* instance;
	physx::PxFoundation* mFoundation;
	physx::PxPvd* mPvd;
	physx::PxPhysics* mPhysics;
	physx::PxCooking* mCooking;
	physx::PxScene* scene;
};

#endif PHYSXENGINE_H