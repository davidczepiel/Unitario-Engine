#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include <PxPhysicsAPI.h>

class ContactReportCallback : public physx::PxSimulationEventCallback
{
	void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count); }
	void onWake(physx::PxActor** actors, physx::PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onSleep(physx::PxActor** actors, physx::PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count);
	void onAdvance(const physx::PxRigidBody*const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) { 
		PX_UNUSED(bodyBuffer); PX_UNUSED(poseBuffer); PX_UNUSED(count);}
	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs);
};

#endif