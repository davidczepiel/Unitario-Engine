#include "RayCast.h"
#include "PxPhysicsAPI.h"
#include "PhysxEngine.h"
#include "Exceptions.h"

PxRayCast::PxRayCast(const std::tuple<float, float, float>& source, const std::tuple<float, float, float>& directionVector, float distance, PxRayCast::Type collidesWith) :
	_raycast()
{

	if (distance <= 0)
		throw ERayCast("RayCast distance cannot negative or zero");
	if(TUPLE_TO_PHYSXVEC3(directionVector).isZero())
		throw ERayCast("RayCast direction vector cannot be zero");

	physx::PxRaycastBuffer hit;
	physx::PxQueryFilterData filter;

	switch (collidesWith)
	{
	case PxRayCast::Type::Static:
		filter = physx::PxQueryFilterData(physx::PxQueryFlag::eSTATIC);
		break;
	case PxRayCast::Type::Dynamic:
		filter = physx::PxQueryFilterData(physx::PxQueryFlag::eDYNAMIC);
		break;
	default:
		filter = physx::PxQueryFilterData(physx::PxQueryFlag::eSTATIC | physx::PxQueryFlag::eDYNAMIC);
		break;
	}
	
	_raycast.hit = PhysxEngine::getPxInstance()->getScene()->raycast(TUPLE_TO_PHYSXVEC3(source), TUPLE_TO_PHYSXVEC3(directionVector).getNormalized(), distance, hit,
			physx::PxHitFlags(physx::PxHitFlag::eDEFAULT), filter);

	if (_raycast.hit) {
		_raycast.actorName = hit.block.actor->getName();
		_raycast.distance = hit.block.distance;
		_raycast.hitPosition = PHYSXVEC3_TO_TUPLE(hit.block.position);
	}
}
