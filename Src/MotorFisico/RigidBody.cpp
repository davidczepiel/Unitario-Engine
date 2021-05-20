#include "RigidBody.h"
#include "PxMaterial.h"
#include "PxScene.h"
#include "PxPhysics.h"
#include "PxRigidBody.h"
#include "PxRigidDynamic.h"
#include "PxRigidStatic.h"
#include "PhysxEngine.h"
#include "extensions/PxRigidBodyExt.h"
#include <iostream>

RigidBody::RigidBody(float radious, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* collisionCallback, bool isKinematic, const std::tuple<float, float, float>& position,
	bool isStatic, float linearDamping, float angularDamping, float staticFriction,
	float dynamicFriction, float restitution, float density) :_physx(nullptr), _dynamicBody(nullptr),
	_staticBody(nullptr), _isStatic(isStatic), _scene(nullptr), _gameObject(gameObject), _collisionCallback(collisionCallback)
{
	initParams(position, density, isKinematic, linearDamping, angularDamping);
	physx::PxSphereGeometry aux(radious);
	physx::PxMaterial* mat = _physx->createMaterial(staticFriction, dynamicFriction, restitution);
	_shape = _physx->createShape(aux, *mat);
	setFlags(_shape);
	mat->release();
	if (_isStatic)
	{
		_staticBody->attachShape(*_shape);
		_scene->addActor(*_staticBody);
		_staticBody->setName(gameObjectName.c_str());
	}
	else {
		_dynamicBody->attachShape(*_shape);
		_scene->addActor(*_dynamicBody);
		_dynamicBody->setName(gameObjectName.c_str());
	}
}

RigidBody::RigidBody(float width, float height, float depth, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* collisionCallback, bool isStatic, const std::tuple<float, float, float>& position,
	bool isKinematic, float linearDamping, float angularDamping, float staticFriction,
	float dynamicFriction, float restitution, float mass) :
	_physx(nullptr), _dynamicBody(nullptr), _staticBody(nullptr), _isStatic(isStatic), _scene(nullptr),
	_gameObject(gameObject), _collisionCallback(collisionCallback)
{
	initParams(position, mass, isKinematic, linearDamping, angularDamping);
	physx::PxMaterial* mat = _physx->createMaterial(staticFriction, dynamicFriction, restitution);
	physx::PxBoxGeometry aux(width / 2, height / 2, depth / 2);
	_shape = _physx->createShape(aux, *mat);
	setFlags(_shape);
	mat->release();
	if (_isStatic)
	{
		_staticBody->attachShape(*_shape);
		_scene->addActor(*_staticBody);
		_staticBody->setName(gameObjectName.c_str());
	}
	else {
		_dynamicBody->attachShape(*_shape);
		_scene->addActor(*_dynamicBody);
		_dynamicBody->setName(gameObjectName.c_str());
	}
}

RigidBody::RigidBody(float radious, float height, GameObject* gameObject, const std::string& gameObjectName, ContactCallback* collisionCallback, bool isStatic, const std::tuple<float, float, float>& position, bool isKinematic,
	float linearDamping, float angularDamping, float staticFriction, float dynamicFriction, float restitution, float mass) :
	_physx(nullptr), _dynamicBody(nullptr), _staticBody(nullptr), _isStatic(isStatic), _scene(nullptr),
	_gameObject(gameObject), _collisionCallback(collisionCallback)
{
	initParams(position, mass, isKinematic, linearDamping, angularDamping);
	physx::PxMaterial* mat = _physx->createMaterial(staticFriction, dynamicFriction, restitution);
	physx::PxCapsuleGeometry aux(radious, height / 2);
	_shape = _physx->createShape(aux, *mat);
	setFlags(_shape);
	mat->release();
	if (_isStatic)
	{
		_staticBody->attachShape(*_shape);
		_scene->addActor(*_staticBody);
		_staticBody->setName(gameObjectName.c_str());
	}
	else {
		_dynamicBody->attachShape(*_shape);
		_scene->addActor(*_dynamicBody);
		_dynamicBody->setName(gameObjectName.c_str());
	}
}

RigidBody::~RigidBody()
{
	_shape->release();
	if (_isStatic)
		_staticBody->release();
	else
		_dynamicBody->release();
}

void RigidBody::enable()
{
	if (_isStatic)
		_staticBody->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, false);
	else
		_dynamicBody->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, false);
}

void RigidBody::disable()
{
	if (_isStatic)
		_staticBody->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, true);
	else
		_dynamicBody->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, true);
}

bool RigidBody::setStaticFriction(float f)
{
	if (!_isStatic) {
		std::list<physx::PxMaterial*> materials = getAllMaterials();
		for (auto it = materials.begin(); it != materials.end(); ++it)
		{
			(*it)->setStaticFriction(f);
		}
		return true;
	}
	return false;
}

bool RigidBody::setDynamicFriction(float f)
{
	if (!_isStatic) {
		std::list<physx::PxMaterial*> materials = getAllMaterials();
		for (auto it = materials.begin(); it != materials.end(); ++it)
		{
			(*it)->setDynamicFriction(f);
		}
		return true;
	}
	return false;

}

bool RigidBody::setBounciness(float b)
{
	if (!_isStatic) {
		std::list<physx::PxMaterial*> materials = getAllMaterials();
		for (auto it = materials.begin(); it != materials.end(); ++it)
		{
			(*it)->setRestitution(b);
		}
		return true;

	}
	return false;

}

bool RigidBody::setMass(float m)
{
	if (!_isStatic)
	{
		_dynamicBody->setMass(m);
		return true;
	}
	return false;

}

bool RigidBody::setLinearVelocity(const std::tuple<float, float, float>& vel)
{
	if (!_isStatic)
	{
		_dynamicBody->setLinearVelocity(TUPLE_TO_PHYSXVEC3(vel));
		return true;
	}
	return false;

}

bool RigidBody::setAngularVelocity(const std::tuple<float, float, float>& vel)
{
	if (!_isStatic)
	{
		_dynamicBody->setAngularVelocity(TUPLE_TO_PHYSXVEC3(vel));
		return true;
	}
	return false;

}

const std::tuple<float, float, float> RigidBody::getAngularVelocity()
{
	if (_isStatic)
		return std::tuple<float, float, float>(0, 0, 0);
	else return  PHYSXVEC3_TO_TUPLE(_dynamicBody->getAngularVelocity());
}

const std::tuple<float, float, float> RigidBody::getLinearVelocity()
{
	if (_isStatic)
		return std::tuple<float, float, float>(0, 0, 0);
	else return  PHYSXVEC3_TO_TUPLE(_dynamicBody->getLinearVelocity());
}

float RigidBody::getMass()
{
	if (_isStatic)
		0;
	else return _dynamicBody->getMass();
}
bool RigidBody::addForce(std::tuple<float, float, float>& force)
{
	if (!_isStatic) {

		_dynamicBody->addForce(TUPLE_TO_PHYSXVEC3(force));
		return true;
	}
	return false;
}

bool RigidBody::addImpulse(std::tuple<float, float, float>& impulse)
{
	if (!_isStatic)
	{
		_dynamicBody->addForce(TUPLE_TO_PHYSXVEC3(impulse), physx::PxForceMode::eIMPULSE);
		return true;
	}
	return false;

}

bool RigidBody::addTorque(const std::tuple<float, float, float>& torque)
{
	if (!_isStatic)
	{
		_dynamicBody->addTorque(TUPLE_TO_PHYSXVEC3(torque));
		return true;
	}
	return false;
}

bool RigidBody::setGravity(bool g)
{
	if (!_isStatic)
	{
		_dynamicBody->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, !g);
		return true;

	}
	return false;
}

bool RigidBody::moveTo(std::tuple<float, float, float>& dest)
{
	if (!_isStatic && _dynamicBody->getRigidBodyFlags().isSet(physx::PxRigidBodyFlag::eKINEMATIC))
	{
		_dynamicBody->setKinematicTarget(physx::PxTransform(TUPLE_TO_PHYSXVEC3(dest)));
		return true;

	}
	return false;
}

bool RigidBody::constrainX(bool constrain, bool linear)
{
	if (!_isStatic)
	{
		if (linear)
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, constrain);
		else
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, constrain);
		return true;

	}
	return false;

}

bool RigidBody::constrainY(bool constrain, bool linear)
{
	if (!_isStatic)
	{
		if (linear)
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, constrain);
		else
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, constrain);
		return true;

	}
	return false;

}

bool RigidBody::constrainZ(bool constrain, bool linear)
{
	if (!_isStatic)
	{
		if (linear)
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, constrain);
		else
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, constrain);
		return true;

	}
	return false;

}

bool RigidBody::setPosition(const std::tuple<float, float, float>& position)
{
	if (!_isStatic) {
		_dynamicBody->setGlobalPose(physx::PxTransform(TUPLE_TO_PHYSXVEC3(position)));
		return true;

	}
	return false;
}

bool RigidBody::rotate(const std::tuple<float, float, float>& rotation)
{
	if (!_isStatic) {
		physx::PxVec3 postRot = _dynamicBody->getGlobalPose().rotate(TUPLE_TO_PHYSXVEC3(rotation));
		physx::PxQuat q = toQuaternion(PHYSXVEC3_TO_TUPLE(postRot));
		physx::PxTransform tr(_dynamicBody->getGlobalPose().p, q);
		_dynamicBody->setGlobalPose(tr);
		return true;
	}
	return false;
}

bool RigidBody::setRotation(const std::tuple<float, float, float>& rotation)
{
	if (!_isStatic) { 
		physx::PxQuat q = toQuaternion(rotation);
		physx::PxTransform tr(_dynamicBody->getGlobalPose().p, q);
		_dynamicBody->setGlobalPose(tr);
		return true;
	}
	else {
		physx::PxQuat q = toQuaternion(rotation);
		physx::PxTransform tr(_staticBody->getGlobalPose().p, q);
		_staticBody->setGlobalPose(tr);
		return false;
	}
}

bool RigidBody::setScale(const std::tuple<float, float, float>&scale)
{
	if (!_isStatic) {

		if (_shape->getGeometryType() == physx::PxGeometryType::eBOX) {
			physx::PxVec3 boxScale = _shape->getGeometry().box().halfExtents;
			physx::PxVec3 newScale = TUPLE_TO_PHYSXVEC3(scale);
			boxScale.x *= newScale.x;
			boxScale.y *= newScale.y;
			boxScale.z *= newScale.z;

			_shape->setGeometry(physx::PxBoxGeometry(boxScale));
		}
		else if (_shape->getGeometryType() == physx::PxGeometryType::eSPHERE) {

			float sphereScale = _shape->getGeometry().sphere().radius;
			_shape->setGeometry(physx::PxSphereGeometry(getGreater(scale) * sphereScale));
		}
		else if (_shape->getGeometryType() == physx::PxGeometryType::eCAPSULE)
		{
			float capsuleRadious = _shape->getGeometry().capsule().radius;
			float capsuleHalfHeight = _shape->getGeometry().capsule().halfHeight;
			float greater = getGreater(scale);
			_shape->setGeometry(physx::PxCapsuleGeometry(capsuleRadious * greater, capsuleHalfHeight * greater));

		}
		return true;
	}
	return false;

}

const std::tuple<float, float, float> RigidBody::getPosition()
{
	if (_isStatic) {
		return PHYSXVEC3_TO_TUPLE(_staticBody->getGlobalPose().p);
	}
	else {
		return PHYSXVEC3_TO_TUPLE(_dynamicBody->getGlobalPose().p);
	}

}

const std::tuple<float, float, float> RigidBody::getRotation()
{
	return PHYSXVEC3_TO_TUPLE(ToEulerAngles(_dynamicBody->getGlobalPose().q));
}

physx::PxQuat RigidBody::toQuaternion(const std::tuple<float, float, float>& rotation)
{
	physx::PxVec3 rot = TUPLE_TO_PHYSXVEC3(rotation);

	double cy = cos(rot.x * 0.5);
	double sy = sin(rot.x * 0.5);
	double cp = cos(rot.y * 0.5);
	double sp = sin(rot.y * 0.5);
	double cr = cos(rot.z * 0.5);
	double sr = sin(rot.z * 0.5);

	physx::PxQuat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.z = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.x = cr * cp * sy - sr * sp * cy;

	return q;
}

physx::PxVec3 RigidBody::ToEulerAngles(physx::PxQuat q)
{
	physx::PxVec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(physx::PxPi / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

void RigidBody::setFlags(physx::PxShape * shape)
{
	shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
	shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, false);
}

void RigidBody::initParams(const std::tuple<float, float, float>&pos, float mass, bool isKinematic, float linearDamping, float angularDamping)
{
	_physx = PhysxEngine::getPxInstance()->getPhysics();
	_scene = PhysxEngine::getPxInstance()->getScene();

	if (_isStatic) {
		_staticBody = _physx->createRigidStatic(physx::PxTransform(TUPLE_TO_PHYSXVEC3(pos)));
		_staticBody->userData = this;
	}
	else
	{
		_dynamicBody = _physx->createRigidDynamic(physx::PxTransform(TUPLE_TO_PHYSXVEC3(pos)));
		_dynamicBody->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, isKinematic);
		_dynamicBody->setLinearDamping(linearDamping);
		_dynamicBody->setAngularDamping(angularDamping);
		_dynamicBody->userData = this;
		physx::PxRigidBodyExt::updateMassAndInertia(*_dynamicBody, mass);
		_dynamicBody->setMassSpaceInertiaTensor(physx::PxVec3(1, 1, 1));
	}
}

std::list<physx::PxMaterial*> RigidBody::getAllMaterials()
{
	std::list<physx::PxMaterial*> list = std::list<physx::PxMaterial*>();

	int nbMaterials = _shape->getNbMaterials();
	physx::PxMaterial** auxMaterials = new physx::PxMaterial * [nbMaterials];
	_shape->getMaterials(auxMaterials, nbMaterials);
	for (int j = 0; j < nbMaterials; j++)
	{
		list.push_back(auxMaterials[j]);
	}
	delete[] auxMaterials;

	return list;
}

float RigidBody::getGreater(std::tuple<float, float, float> tuple)
{
	float greater;
	if (std::get<0>(tuple) > std::get<1>(tuple))
		greater = std::get<0>(tuple);
	else greater = std::get<1>(tuple);
	if (greater < std::get<2>(tuple))
		greater = std::get<2>(tuple);
	return greater;
}
