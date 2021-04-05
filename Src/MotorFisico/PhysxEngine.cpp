#include "PhysxEngine.h"
#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultSimulationFilterShader.h"

#define PVD_HOST "127.0.0.1"
//#include "Exceptions.h"

PhysxEngine* PhysxEngine::instance = nullptr;
PhysxEngine::~PhysxEngine()
{
	mPhysics->release();
	mFoundation->release();
	mPvd->release();
	mCooking->release();
	scene->release();
}

PhysxEngine* PhysxEngine::getPxInstance()
{
	if (instance == nullptr) {
		instance = new PhysxEngine();
	}
	return instance;
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

	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback,	gDefaultErrorCallback);
	/*if (!mFoundation)
		throw EPhysxEngine("PxCreateFoundation failed!");*/
	bool recordMemoryAllocations = true;

	mPvd = physx::PxCreatePvd(*mFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);


	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation,
		physx::PxTolerancesScale(), recordMemoryAllocations, mPvd);
	/*if (!mPhysics)
		throw EPhysxEngine("PxCreatePhysics failed!");*/
	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, physx::PxCookingParams(mPhysics->getTolerancesScale()));
	/*if (!mFoundation)
		throw EPhysxEngine("PxCreateCooking failed!");*/
	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 0.0f);
	physx::PxDefaultCpuDispatcher* gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	scene = mPhysics->createScene(sceneDesc);	 
	/*if (!scene)
		throw EPhysxEngine("PxSceneDesc failed!");*/
		
}

void PhysxEngine::update(float time)
{
	scene->simulate(physx::PxReal(time));
	scene->fetchResults(true);
}

physx::PxScene* PhysxEngine::getScene()
{
	return scene;
}

PhysxEngine::PhysxEngine(): mFoundation(nullptr), mPhysics(nullptr), mPvd(nullptr), mCooking(nullptr),scene(nullptr)
{
}
