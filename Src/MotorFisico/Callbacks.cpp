#include "Callbacks.h"
#include "RigidBody.h"
#include "Collider.h"

void ContactReportCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	physx::PxShape* shape1 = pairs->triggerShape;
	physx::PxShape* shape2 = pairs->otherShape;

	Collider* coll1 = static_cast<Collider*>(shape1->userData);
	Collider* coll2 = static_cast<Collider*>(shape2->userData);

	coll1->getColliderCallback()(coll1->getGameObject(), coll2->getGameObject());
}

void ContactReportCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	PX_UNUSED(pairs);
	PX_UNUSED(nbPairs);
	physx::PxActor* actor1 = pairHeader.actors[0];
	physx::PxActor* actor2 = pairHeader.actors[1];

	if (actor1 != nullptr && actor2 != nullptr) {
		RigidBody* rb1 = static_cast<RigidBody*>(actor1->userData);
		RigidBody* rb2 = static_cast<RigidBody*>(actor2->userData);

		rb1->getColliderCallback()(rb1->getGameObject(), rb2->getGameObject());
	}
	else {
		physx::PxShape* shape1 = pairHeader.pairs[0].shapes[0];
		physx::PxShape* shape2 = pairHeader.pairs[0].shapes[1];

		Collider* coll1 = static_cast<Collider*>(shape1->userData);
		Collider* coll2 = static_cast<Collider*>(shape2->userData);

		coll1->getColliderCallback()(coll1->getGameObject(), coll2->getGameObject());
	}
}
