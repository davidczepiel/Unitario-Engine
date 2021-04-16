#include "Collider.h"
#include "PhysxEngine.h"
#include <PxRigidDynamic.h>
#include <PxRigidActor.h>
#include <PxShape.h>
#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <PxRigidActor.h>

#define GetPhysx() PhysxEngine::getPxInstance()->getScene()->getPhysics()

Collider::Collider(bool isTrigger, GameObject* gameObject, ContactCallback* coliderCallback, ContactCallback* triggerCallback,
	float staticFriction, float dynamicFriction, float restitution)
	:_isTrigger(isTrigger), _gameObject(gameObject), _contCallback(coliderCallback), _triggerCallback(triggerCallback)
{
	physx::PxMaterial* gMaterial = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);

	if (isTrigger) setTrigger();
	else setCollider();
}

void Collider::setCollider()
{
	_mShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	_mShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
	_mShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
	_mShape->setFlag(physx::PxShapeFlag::eVISUALIZATION, false);
}

void Collider::setTrigger()
{
	_mShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	_mShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	_mShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	_mShape->setFlag(physx::PxShapeFlag::eVISUALIZATION, false);
}

//////////////////////////////////////////////////

BoxCollider::BoxCollider(int width, int heigh, int depth, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
	float staticFriction, float dynamicFriction, float restitution)
	: Collider(isTrigger, gameObject, colliderCallback, triggerCallback, staticFriction, dynamicFriction, restitution)
{
	physx::PxMaterial* mat = GetPhysx().createMaterial(0.5f, 0.5f, 0.5);
	physx::PxBoxGeometry aux(width / 2, heigh / 2, depth / 2);
	_mShape = GetPhysx().createShape(aux, *mat);
	_mShape->userData = this;
}

void BoxCollider::setScale(int width, int heigh, int depth) {
	_mShape->setGeometry(physx::PxBoxGeometry(width / 2, heigh / 2, depth / 2));
}

///////////////////////////////////////////////

SphereCollider::SphereCollider(int radius, bool isTrigger, GameObject* gameObject, ContactCallback* callback, ContactCallback* triggerCallback,
	float staticFriction, float dynamicFriction, float restitution)
	:Collider(isTrigger, gameObject, callback, triggerCallback, staticFriction, dynamicFriction, restitution)
{
	physx::PxSphereGeometry aux(radius);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	_mShape->userData = this;
}

void SphereCollider::setScale(int r) {
	_mShape->setGeometry(physx::PxSphereGeometry(r));
}

/////////////////////////////////////////////////

CapsuleCollider::CapsuleCollider(int radius, int length, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
	float staticFriction, float dynamicFriction, float restitution)
	:Collider(isTrigger, gameObject, colliderCallback, triggerCallback, staticFriction, dynamicFriction, restitution)
{
	physx::PxCapsuleGeometry aux(radius, length / 2);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	_mShape->userData = this;
}

void CapsuleCollider::setScale(int radius, int length) {
	_mShape->setGeometry(physx::PxCapsuleGeometry(radius, length / 2));
}