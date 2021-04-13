#include "RigidBody.h"
#include "PxMaterial.h"
#include "PxScene.h"
#include "PxPhysics.h"
#include "PxRigidBody.h"
#include "PxRigidDynamic.h"
#include "PxRigidStatic.h"
#include "PhysxEngine.h"

RigidBody::RigidBody(float radious, GameObject* gameObject, ContactCallback* collisionCallback, bool isKinematic, const std::tuple<float, float, float>& position,
	bool isStatic, float linearDamping, float angularDamping, float staticFriction,
	float dynamicFriction, float restitution, float mass) :_physx(nullptr), _transform(), _dynamicBody(nullptr),
	_staticBody(nullptr), _isStatic(isStatic), _scene(nullptr), _gameObject(gameObject), _collisionCallback(collisionCallback)
{
	initParams(position, mass, isKinematic, linearDamping, angularDamping);
	physx::PxSphereGeometry aux(radious);
	physx::PxMaterial* mat = _physx->createMaterial(staticFriction, dynamicFriction, restitution);
	physx::PxShape* e = _physx->createShape(aux, *mat);
	setFlags(e);
	mat->release();
	e->release();
	_dynamicBody->attachShape(*e);
	_scene->addActor(*_dynamicBody);
}

RigidBody::RigidBody(float width, float height, float depth, GameObject* gameObject, ContactCallback* collisionCallback, bool isStatic, const std::tuple<float, float, float>& position,
	bool isKinematic, float linearDamping, float angularDamping, float staticFriction,
	float dynamicFriction, float restitution, float mass) :
	_physx(nullptr), _transform(), _dynamicBody(nullptr), _staticBody(nullptr), _isStatic(isStatic), _scene(nullptr),
	_gameObject(gameObject), _collisionCallback(collisionCallback)
{
	initParams(position, mass, isKinematic, linearDamping, angularDamping);
	physx::PxMaterial* mat = _physx->createMaterial(staticFriction, dynamicFriction, restitution);
	physx::PxBoxGeometry aux(width / 2, height / 2, depth / 2);
	physx::PxShape* e = _physx->createShape(aux, *mat);
	setFlags(e);
	mat->release();
	_dynamicBody->attachShape(*e);
	e->release();
	_scene->addActor(*_dynamicBody);
}

RigidBody::RigidBody(float radious, float height, GameObject* gameObject, ContactCallback* collisionCallback, bool isStatic, const std::tuple<float, float, float>& position, bool isKinematic,
	float linearDamping, float angularDamping, float staticFriction, float dynamicFriction, float restitution, float mass) :
	_physx(nullptr), _transform(), _dynamicBody(nullptr), _staticBody(nullptr), _isStatic(isStatic), _scene(nullptr),
	_gameObject(gameObject), _collisionCallback(collisionCallback)
{
	initParams(position, mass, isKinematic, linearDamping, angularDamping);
	physx::PxMaterial* mat = _physx->createMaterial(staticFriction, dynamicFriction, restitution);
	physx::PxCapsuleGeometry aux(radious, height / 2);
	physx::PxShape* e = _physx->createShape(aux, *mat);
	setFlags(e);
	mat->release();
	_dynamicBody->attachShape(*e);
	e->release();
	_scene->addActor(*_dynamicBody);
}

RigidBody::~RigidBody()
{
	if (_dynamicBody != nullptr)
		_dynamicBody->release();
	if (_staticBody != nullptr)
		_staticBody->release();
	delete _transform;
	_transform = nullptr;
}

void RigidBody::setStaticFriction(float f)
{
	if (!_isStatic) {
		std::list<physx::PxMaterial*> materials = getAllMaterials();
		for (auto it = materials.begin(); it != materials.end(); ++it)
		{
			(*it)->setStaticFriction(f);
		}
	}
}

void RigidBody::setDynamicFriction(float f)
{
	if (!_isStatic) {
		std::list<physx::PxMaterial*> materials = getAllMaterials();
		for (auto it = materials.begin(); it != materials.end(); ++it)
		{
			(*it)->setDynamicFriction(f);
		}
	}
}

void RigidBody::setBounciness(float b)
{
	if (!_isStatic) {
		std::list<physx::PxMaterial*> materials = getAllMaterials();
		for (auto it = materials.begin(); it != materials.end(); ++it)
		{
			(*it)->setRestitution(b);
		}
	}
}

void RigidBody::setMass(float m)
{
	if (!_isStatic)
		_dynamicBody->setMass(m);
}

void RigidBody::setLinearVelocity(const std::tuple<float, float, float>& vel)
{
	if (!_isStatic)
		_dynamicBody->setLinearVelocity(TUPLE_TO_PHYSXVEC3(vel));
}

void RigidBody::setAngularVelocity(const std::tuple<float, float, float>& vel)
{
	if (!_isStatic)
		_dynamicBody->setAngularVelocity(TUPLE_TO_PHYSXVEC3(vel));
}

const std::tuple<float, float, float>& RigidBody::getAngularVelocity()
{
	if (_isStatic)
		return std::tuple<float, float, float>(0, 0, 0);
	else return  PHYSXVEC3_TO_TUPLE(_dynamicBody->getAngularVelocity());
}

const std::tuple<float, float, float>& RigidBody::getLinearVelocity()
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
void RigidBody::addForce(std::tuple<float, float, float>& force)
{
	if (_isStatic)
		_dynamicBody->addForce(TUPLE_TO_PHYSXVEC3(force));
}

void RigidBody::addImpulse(std::tuple<float, float, float>& impulse)
{
	if (!_isStatic)
		_dynamicBody->addForce(TUPLE_TO_PHYSXVEC3(impulse), physx::PxForceMode::eIMPULSE);
}

void RigidBody::addTorque(std::tuple<float, float, float>& torque)
{
	if (!_isStatic)
		_dynamicBody->addTorque(TUPLE_TO_PHYSXVEC3(torque));
}

void RigidBody::setGravity(bool g)
{
	if (!_isStatic)
		_dynamicBody->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, !g);
}

void RigidBody::moveTo(std::tuple<float, float, float>& dest)
{
	if (!_isStatic && _dynamicBody->getRigidBodyFlags().isSet(physx::PxRigidBodyFlag::eKINEMATIC))
		_dynamicBody->setKinematicTarget(physx::PxTransform(TUPLE_TO_PHYSXVEC3(dest)));
}

void RigidBody::constrainX(bool constrain, bool linear)
{
	if (!_isStatic)
	{
		if (linear)
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, constrain);
		else
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, constrain);
	}
}

void RigidBody::constrainY(bool constrain, bool linear)
{
	if (!_isStatic)
	{
		if (linear)
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, constrain);
		else
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, constrain);
	}
}

void RigidBody::constrainZ(bool constrain, bool linear)
{
	if (!_isStatic)
	{
		if (linear)
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, constrain);
		else
			_dynamicBody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, constrain);
	}
}

void RigidBody::setPosition(const std::tuple<float, float, float>& position)
{
	if (!_isStatic) {
		_transform->p = TUPLE_TO_PHYSXVEC3(position);
		_dynamicBody->setGlobalPose(*_transform);
	}
	//else Exception?
}

void RigidBody::setRotation(const std::tuple<float, float, float>& position)
{
	if (!_isStatic) {
		//physx::PxQuat();
		//_transform->q = TUPLE_TO_PHYSXVEC3(position);
		//_dynamicBody->setGlobalPose();
	}
}

void RigidBody::setScale(const std::tuple<float, float, float>& scale)
{
	//else Exception?
	if (!_isStatic) {
		int nbShapes = _dynamicBody->getNbShapes();
		physx::PxShape** shapes = new physx::PxShape * [nbShapes];
		_dynamicBody->getShapes(shapes, nbShapes);
		for (int i = 0; i < nbShapes; i++) {
			if (shapes[i]->getGeometryType() == physx::PxGeometryType::eBOX) {
				shapes[i]->setGeometry(physx::PxBoxGeometry(TUPLE_TO_PHYSXVEC3(scale)));
			}
			else {
				//Exception
			}
		}
	}
}

void RigidBody::setScale(const std::tuple<float, float>& scale)
{
	//else Exception?
	if (!_isStatic) {
		int nbShapes = _dynamicBody->getNbShapes();
		physx::PxShape** shapes = new physx::PxShape * [nbShapes];
		_dynamicBody->getShapes(shapes, nbShapes);
		for (int i = 0; i < nbShapes; i++) {
			if (shapes[i]->getGeometryType() == physx::PxGeometryType::eCAPSULE) {
				//shapes[i]->setGeometry(physx::PxSphereGeometry(TUPLE_TO_PHYSXVEC3(scale)));
			}
			else {
				//Exception
			}
		}
	}
}

void RigidBody::setScale(const std::tuple<float>& scale)
{
	//else Exception?
	if (!_isStatic) {
		int nbShapes = _dynamicBody->getNbShapes();
		physx::PxShape** shapes = new physx::PxShape * [nbShapes];
		_dynamicBody->getShapes(shapes, nbShapes);
		for (int i = 0; i < nbShapes; i++) {
			if (shapes[i]->getGeometryType() == physx::PxGeometryType::eSPHERE) {
				//shapes[i]->setGeometry(physx::PxBoxGeometry(TUPLE_TO_PHYSXVEC3(scale)));
			}
			else {
				//Exception
			}
		}
	}
}

const std::tuple<float, float, float>& RigidBody::getPosition()
{
	if (_isStatic) {
		return PHYSXVEC3_TO_TUPLE(_staticBody->getGlobalPose().p);
	}
	else
		return PHYSXVEC3_TO_TUPLE(_dynamicBody->getGlobalPose().p);
}

const std::tuple<float, float, float>& RigidBody::getRotation()
{
	float angle = 0;
	physx::PxVec3 axis;
	_transform->q.toRadiansAndUnitAxis(angle, axis);
	return PHYSXVEC3_TO_TUPLE(axis);
}

void RigidBody::setFlags(physx::PxShape* shape)
{
	shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
	shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
	shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, false);
}

void RigidBody::initParams(const std::tuple<float, float, float>& pos, float mass, bool isKinematic, float linearDamping, float angularDamping)
{
	_physx = &PhysxEngine::getPxInstance()->getScene()->getPhysics();
	_scene = PhysxEngine::getPxInstance()->getScene();

	_transform = new physx::PxTransform(TUPLE_TO_PHYSXVEC3(pos));
	if (_isStatic) {
		_staticBody = _physx->createRigidStatic(*_transform);
		_staticBody->userData = this;
	}
	else
	{
		_dynamicBody = _physx->createRigidDynamic(*_transform);
		_dynamicBody->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, isKinematic);
		_dynamicBody->setLinearDamping(linearDamping);
		_dynamicBody->setAngularDamping(angularDamping);
		_dynamicBody->userData = this;
	}
	_dynamicBody->setMass(mass);
}

std::list<physx::PxMaterial*> RigidBody::getAllMaterials()
{
	std::list<physx::PxMaterial*> list = std::list<physx::PxMaterial*>();
	int nbShapes = _dynamicBody->getNbShapes();
	physx::PxShape** shapes = new physx::PxShape * [nbShapes];
	_dynamicBody->getShapes(shapes, nbShapes);
	for (int i = 0; i < nbShapes; i++)
	{
		int nbMaterials = shapes[i]->getNbMaterials();
		physx::PxMaterial** auxMaterials = new physx::PxMaterial * [nbMaterials];
		shapes[i]->getMaterials(auxMaterials, nbMaterials);
		for (int j = 0; j < nbMaterials; j++)
		{
			list.push_back(auxMaterials[i]);
		}
		delete[] auxMaterials;
	}

	delete[] shapes;
	return list;
}