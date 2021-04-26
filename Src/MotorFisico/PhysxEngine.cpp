#include "PhysxEngine.h"
#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultSimulationFilterShader.h"
#include "Exceptions.h"
#include "Callbacks.h"
#include "pvd/PxPvdTransport.h"

#define PVD_HOST "127.0.0.1"

PhysxEngine* PhysxEngine::_instance = nullptr;

PhysxEngine::PhysxEngine() : _mFoundation(nullptr), _mPhysics(nullptr), _mPvd(nullptr), /*_mCooking(nullptr),*/ _mMaterial(nullptr),
	_scene(nullptr), alreadyInitialized(false), _callback(new ContactReportCallback()), _gDefaultAllocatorCallback(new physx::PxDefaultAllocator()),
	_gDefaultErrorCallback(new physx::PxDefaultErrorCallback()), _gDispatcher(nullptr)
{
}

PhysxEngine::~PhysxEngine()
{
	_scene->release();
	_mPhysics->release();
	
	physx::PxPvdTransport* transport = _mPvd->getTransport();
	_mPvd->release();
	transport->release();

	_mFoundation->release();

	delete _callback; _callback = nullptr;
	delete _gDefaultAllocatorCallback; _gDefaultAllocatorCallback = nullptr;
	delete _gDefaultErrorCallback; _gDefaultErrorCallback = nullptr;
}

void PhysxEngine::CreateInstance()
{
	if (_instance == nullptr) {
		_instance = new PhysxEngine();
	}
}

PhysxEngine* PhysxEngine::getPxInstance()
{
	return _instance;
}

bool PhysxEngine::init()
{
	if (alreadyInitialized) return false;

	_mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *_gDefaultAllocatorCallback, *_gDefaultErrorCallback);
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
	_gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = _gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = _callback;

	_scene = _mPhysics->createScene(sceneDesc);
	if (!_scene)
		throw EPhysxEngine("PxSceneDesc failed!");

	alreadyInitialized = true;
	return true;
}

void PhysxEngine::update(float time)
{
	_scene->simulate(physx::PxReal(time));
	_scene->fetchResults(true);
}