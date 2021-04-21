#include "PhysxEngine.h"
#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultSimulationFilterShader.h"
#include "Exceptions.h"
#include "Callbacks.h"

#define PVD_HOST "127.0.0.1"

std::unique_ptr<PhysxEngine>PhysxEngine::_instance = nullptr;

PhysxEngine::PhysxEngine() : _mFoundation(nullptr), _mPhysics(nullptr), _mPvd(nullptr), _mCooking(nullptr), _mMaterial(nullptr), _scene(nullptr)
{
}

PhysxEngine::~PhysxEngine()
{
	_mPhysics->release();
	_mFoundation->release();
	_mPvd->release();
	_mCooking->release();
	_scene->release();
}

PhysxEngine* PhysxEngine::getPxInstance()
{
	if (_instance.get() == nullptr) {
		_instance.reset(new PhysxEngine());
	}
	return _instance.get();
}

void PhysxEngine::init()
{
	static physx::PxDefaultErrorCallback gDefaultErrorCallback;
	static physx::PxDefaultAllocator gDefaultAllocatorCallback;
	static ContactReportCallback callback;

	_mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (!_mFoundation)
		throw EPhysxEngine("PxCreateFoundation failed!");

	_mPvd = physx::PxCreatePvd(*_mFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	_mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	_mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *_mFoundation, physx::PxTolerancesScale(), true, _mPvd);
	if (!_mPhysics)
		throw EPhysxEngine("PxCreatePhysics failed!");

	//_mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *_mFoundation, physx::PxCookingParams(_mPhysics->getTolerancesScale()));
	//if (!_mCooking)
	//	throw EPhysxEngine("PxCreateCooking failed!");

	_mMaterial = _mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	physx::PxSceneDesc sceneDesc(_mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 0.0f);
	static physx::PxDefaultCpuDispatcher* gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &callback;

	_scene = _mPhysics->createScene(sceneDesc);
	if (!_scene)
		throw EPhysxEngine("PxSceneDesc failed!");
}

void PhysxEngine::update(float time)
{
	_scene->simulate(physx::PxReal(time));
	_scene->fetchResults(true);
}