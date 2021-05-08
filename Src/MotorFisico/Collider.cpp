#include "Collider.h"
#include "PhysxEngine.h"

#include <PxShape.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include "foundation/PxTransform.h"

#define GetPhysx() PhysxEngine::getPxInstance()->getScene()->getPhysics()


void Collider::enable()
{
	_body->setActorFlag(physx::PxActorFlag::Enum::eDISABLE_SIMULATION, false);
}


void Collider::disable()
{
	_body->setActorFlag(physx::PxActorFlag::Enum::eDISABLE_SIMULATION, true);
}

void Collider::setPosition(const std::tuple<float, float, float>& position)
{
	_body->setGlobalPose(physx::PxTransform(TUPLE_TO_PHYSXVEC3(position)));
}

void Collider::rotate(const std::tuple<float, float, float>& rotation)
{
	_body->getGlobalPose().rotate(TUPLE_TO_PHYSXVEC3(rotation));
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

Collider::Collider(bool isTrigger, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* coliderCallback, ContactCallback* triggerCallback,
	float staticFriction, float dynamicFriction, float restitution, const std::tuple<float, float, float>& position)
	:_isTrigger(isTrigger), _gameObject(gameObject), _contCallback(coliderCallback), _triggerCallback(triggerCallback), _mShape(nullptr)
{
	_body = PhysxEngine::getPxInstance()->getPhysics()->createRigidDynamic(physx::PxTransform(TUPLE_TO_PHYSXVEC3(position)));
	_body->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
	_body->setLinearDamping(0.99);
	_body->setAngularDamping(0.99);
	_body->setName(gameObjectName.c_str());
	_body->userData = this;
	physx::PxRigidBodyExt::updateMassAndInertia(*_body, 1);
}

void Collider::initParams(bool isTrigger)
{

	if (isTrigger) setTrigger();
	else setCollider();

	_body->attachShape(*_mShape);
	PhysxEngine::getPxInstance()->getScene()->addActor(*_body);
}

Collider::~Collider()
{
	_mShape->release(); 
	_body->release();
}

void Collider::setCollider()
{
	_mShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	_mShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
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

BoxCollider::BoxCollider(float width, float heigh, float depth, bool isTrigger, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
	const std::tuple<float, float, float>& position, float staticFriction, float dynamicFriction, float restitution)
	: Collider(isTrigger, gameObject, gameObjectName, colliderCallback, triggerCallback, staticFriction, dynamicFriction, restitution, position)
{
	physx::PxBoxGeometry aux(width / 2.0f, heigh / 2.0f, depth / 2.0f);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	mat->release();
	initParams(isTrigger);
}

void BoxCollider::setScale(float width, float heigh, float depth) {
	_mShape->setGeometry(physx::PxBoxGeometry(width / 2, heigh / 2, depth / 2));
}

///////////////////////////////////////////////

SphereCollider::SphereCollider(float radius, bool isTrigger, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* callback, ContactCallback* triggerCallback,
	const std::tuple<float, float, float>& position, float staticFriction, float dynamicFriction, float restitution)
	:Collider(isTrigger, gameObject, gameObjectName, callback, triggerCallback, staticFriction, dynamicFriction, restitution, position)
{
	physx::PxSphereGeometry aux(radius);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	initParams(isTrigger);
}

void SphereCollider::setScale(float r) {
	_mShape->setGeometry(physx::PxSphereGeometry(r));
}

/////////////////////////////////////////////////

CapsuleCollider::CapsuleCollider(float radius, float length, bool isTrigger, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* colliderCallback, ContactCallback* triggerCallback,
	const std::tuple<float, float, float>& position, float staticFriction, float dynamicFriction, float restitution)
	:Collider(isTrigger, gameObject, gameObjectName, colliderCallback, triggerCallback, staticFriction, dynamicFriction, restitution, position)
{
	physx::PxCapsuleGeometry aux(radius, length / 2);
	physx::PxMaterial* mat = GetPhysx().createMaterial(staticFriction, dynamicFriction, restitution);
	_mShape = GetPhysx().createShape(aux, *mat);
	initParams(isTrigger);
}

void CapsuleCollider::setScale(float radius, float length) {
	_mShape->setGeometry(physx::PxCapsuleGeometry(radius, length / 2));
}