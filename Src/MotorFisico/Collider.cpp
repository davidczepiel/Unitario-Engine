#include "Collider.h"
#include "PhysxEngine.h"

#include <PxShape.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include "foundation/PxTransform.h"

#define GetPhysx() PhysxEngine::getPxInstance()->getScene()->getPhysics()

void Collider::setPosition(const std::tuple<float, float, float>& position)
{
	_pxTrans->p = TUPLE_TO_PHYSXVEC3(position);
	_mShape->setLocalPose(*_pxTrans);
}

void Collider::rotate(const std::tuple<float, float, float>& rotation)
{
	_pxTrans->q.rotate(TUPLE_TO_PHYSXVEC3(rotation).getNormalized());
}

void Collider::setMaterial(float staticFriction, float dynamicFriction, float restitution)
{
	int buffsize = 1;
	physx::PxMaterial** buffer = new physx::PxMaterial*[buffsize];
	
	_mShape->getMaterials(buffer, buffsize);

	buffer[0]->setStaticFriction(staticFriction);
	buffer[0]->setDynamicFriction(dynamicFriction);
	buffer[0]->setRestitution(restitution);

	_mShape->setMaterials(buffer, 1);

	delete[] buffer;
}

Collider::Collider(bool isTrigger, GameObject* gameObject, ContactCallback* coliderCallback, ContactCallback* triggerCallback,
	float staticFriction, float dynamicFriction, float restitution, const std::tuple<float, float, float>& position)
	:_isTrigger(isTrigger), _gameObject(gameObject), _contCallback(coliderCallback), _triggerCallback(triggerCallback)
{
	physx::PxMaterial* gMaterial = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);

	_pxTrans = new physx::PxTransform(TUPLE_TO_PHYSXVEC3(position));
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
	const std::tuple<float, float, float>& position, float staticFriction, float dynamicFriction, float restitution)
	: Collider(isTrigger, gameObject, colliderCallback, triggerCallback, staticFriction, dynamicFriction, restitution, position)
{
	physx::PxMaterial* mat = GetPhysx().createMaterial(0.5f, 0.5f, 0.5);
	physx::PxBoxGeometry aux(width / 2.0f, heigh / 2.0f, depth / 2.0f);
	_mShape = GetPhysx().createShape(aux, *mat);

	_mShape->userData = this;

	if (isTrigger) setTrigger();
	else setCollider();
}

void BoxCollider::setScale(int width, int heigh, int depth) {
	_mShape->setGeometry(physx::PxBoxGeometry(width / 2, heigh / 2, depth / 2));
}

///////////////////////////////////////////////

SphereCollider::SphereCollider(int radius, bool isTrigger, GameObject* gameObject, ContactCallback* callback, ContactCallback* triggerCallback,
	const std::tuple<float, float, float>& position, float staticFriction, float dynamicFriction, float restitution)
	:Collider(isTrigger, gameObject, callback, triggerCallback, staticFriction, dynamicFriction, restitution, position)
{
	physx::PxSphereGeometry aux(radius);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	_mShape->userData = this;

	if (isTrigger) setTrigger();
	else setCollider();
}

void SphereCollider::setScale(int r) {
	_mShape->setGeometry(physx::PxSphereGeometry(r));
}

/////////////////////////////////////////////////

CapsuleCollider::CapsuleCollider(int radius, int length, bool isTrigger, GameObject* gameObject, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
	const std::tuple<float, float, float>& position, float staticFriction, float dynamicFriction, float restitution)
	:Collider(isTrigger, gameObject, colliderCallback, triggerCallback, staticFriction, dynamicFriction, restitution, position)
{
	physx::PxCapsuleGeometry aux(radius, length / 2);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	_mShape->userData = this;

	if (isTrigger) setTrigger();
	else setCollider();
}

void CapsuleCollider::setScale(int radius, int length) {
	_mShape->setGeometry(physx::PxCapsuleGeometry(radius, length / 2));
}