#include "PhysxEngine.h"
#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultSimulationFilterShader.h"
#include "Exceptions.h"

#define PVD_HOST "127.0.0.1"

std::unique_ptr<PhysxEngine>PhysxEngine::_instance = nullptr;

PhysxEngine::PhysxEngine() : _mFoundation(nullptr), _mPhysics(nullptr), _mPvd(nullptr), _mCooking(nullptr), _scene(nullptr)
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

physx::PxFilterFlags contactReportFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
	physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = physx::PxPairFlag::eSOLVE_CONTACT | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
		| physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
		| physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;
	return physx::PxFilterFlag::eDEFAULT;
}

void PhysxEngine::init()
{
	physx::PxDefaultErrorCallback gDefaultErrorCallback;
	physx::PxDefaultAllocator gDefaultAllocatorCallback;

	_mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback,	gDefaultErrorCallback);
	if (!_mFoundation)
		throw EPhysxEngine("PxCreateFoundation failed!");
	bool recordMemoryAllocations = true;

	_mPvd = physx::PxCreatePvd(*_mFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	_mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);


	_mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *_mFoundation,
		physx::PxTolerancesScale(), recordMemoryAllocations, _mPvd);
	if (!_mPhysics)
		throw EPhysxEngine("PxCreatePhysics failed!");
	_mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *_mFoundation, physx::PxCookingParams(_mPhysics->getTolerancesScale()));
	if (!_mCooking)
		throw EPhysxEngine("PxCreateCooking failed!");
	physx::PxSceneDesc sceneDesc(_mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 0.0f);
	physx::PxDefaultCpuDispatcher* gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	_scene = _mPhysics->createScene(sceneDesc);	 
	if (!_scene)
		throw EPhysxEngine("PxSceneDesc failed!");
		
}

void PhysxEngine::update(float time)
{
	_scene->simulate(physx::PxReal(time));
	_scene->fetchResults(true);
}
