#pragma once
#ifndef PHYSXENGINE_H
#define PHYSXENGINE_H

#include <memory>

namespace physx {
	class PxFoundation;
	class PxPhysics;
	class PxCooking;
	class PxPvd;
	class PxScene;
};


/// <summary>
/// Class that implememnts control of physx engine
/// </summary>
class PhysxEngine {
public:
	~PhysxEngine();

	/// <summary>
	/// If the instance is not created creates a new one
	/// </summary>
	/// <returns>Unique instance of physx engine</returns>
	static PhysxEngine* getPxInstance();

	void operator=(const PhysxEngine&) = delete;
	PhysxEngine(PhysxEngine& other) = delete;

	/// <summary>
	/// Initializes physx engine
	/// </summary>
	void init();

	/// <summary>
	/// Calls physx simulation step
	/// </summary>
	/// <param name="time">Time in seconds</param>
	void update(float time);

	/// <summary>
	/// Returns a pointer to the physx scene
	/// </summary>
	/// <returns>A pointer to the physx scene</returns>
	inline physx::PxScene* getScene() const { return _scene; }
	
private:

	/// <summary>
	/// Constructor of the class
	/// </summary>
	PhysxEngine();

	/// <summary>
	/// Singleton of physx engine
	/// </summary>
	static std::unique_ptr<PhysxEngine> _instance;

	/// <summary>
	/// Physx foundation (to initialize physx)
	/// </summary>
	physx::PxFoundation* _mFoundation;

	/// <summary>
	/// Physx Pvd (to initialize physx)
	/// </summary>
	physx::PxPvd* _mPvd;

	/// <summary>
	/// Physics object (to initialize physx)
	/// </summary>
	physx::PxPhysics* _mPhysics;

	/// <summary>
	/// Cooking object for extra physx utilities
	/// </summary>
	physx::PxCooking* _mCooking;

	/// <summary>
	/// Physx scene to simulate
	/// </summary>
	physx::PxScene* _scene;
};

#endif PHYSXENGINE_H