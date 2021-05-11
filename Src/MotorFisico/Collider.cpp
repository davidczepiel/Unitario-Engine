#include "Collider.h"
#include "PhysxEngine.h"

#include <PxShape.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include "foundation/PxTransform.h"
#include <iostream>

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

void Collider::setRotation(const std::tuple<float, float, float>& rotation)
{
	physx::PxQuat q = toQuaternion(rotation);
	physx::PxTransform tr(_body->getGlobalPose().p, q);
	_body->setGlobalPose(tr);
}

void Collider::setMaterial(float staticFriction, float dynamicFriction, float restitution)
{
	int buffsize = 1;
	physx::PxMaterial** buffer = new physx::PxMaterial * [buffsize];

	_mShape->getMaterials(buffer, buffsize);

	buffer[0]->setStaticFriction(staticFriction);
	buffer[0]->setDynamicFriction(dynamicFriction);
	buffer[0]->setRestitution(restitution);

	_mShape->setMaterials(buffer, 1);

	delete[] buffer;
}

physx::PxQuat Collider::toQuaternion(const std::tuple<float, float, float>& rotation)
{
	physx::PxVec3 rot = TUPLE_TO_PHYSXVEC3(rotation);

	double cy = cos(rot.y * 0.5);
	double sy = sin(rot.y * 0.5);
	double cp = cos(rot.z * 0.5);
	double sp = sin(rot.z * 0.5);
	double cr = cos(rot.x * 0.5);
	double sr = sin(rot.x * 0.5);

	physx::PxQuat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

physx::PxVec3 Collider::ToEulerAngles(physx::PxQuat q)
{
	physx::PxVec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.z = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		angles.x = std::copysign(physx::PxPi / 2, sinp); // use 90 degrees if out of range
	else
		angles.x = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.y = std::atan2(siny_cosp, cosy_cosp);

	return angles;
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

float BoxCollider::getWidth()
{
	return _mShape->getGeometry().box().halfExtents.x * 2;
}

float BoxCollider::getHeight()
{
	return _mShape->getGeometry().box().halfExtents.y * 2;

}

float BoxCollider::getDepth()
{
	return _mShape->getGeometry().box().halfExtents.y * 2;

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

float SphereCollider::getRadius()
{
	return _mShape->getGeometry().sphere().radius;
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

float CapsuleCollider::getRadius()
{
	return _mShape->getGeometry().capsule().radius;
}

float CapsuleCollider::getHeight()
{
	return _mShape->getGeometry().capsule().halfHeight * 2;
}
