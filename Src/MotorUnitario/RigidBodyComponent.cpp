#include "RigidBodyComponent.h"
#include "Transform.h"
#include "MotorFisico/RigidBody.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "Logger.h"
#include "Vector3.h"
#include "includeLUA.h"
#include <MotorUnitario/KeyboardInput.h>
#include <algorithm>

RigidBodyComponent::RigidBodyComponent() : Component(ComponentId::Rigidbody, nullptr), _rb(nullptr), _tr(nullptr), _log(nullptr), _constrainRotation(false)
{
	_log = Logger::getInstance();
}

RigidBodyComponent::~RigidBodyComponent()
{
	delete _rb; _rb = nullptr;
}

void RigidBodyComponent::awake(luabridge::LuaRef& data)
{
	bool isStatic = false;
	Vector3 position = Vector3();
	bool isKinematic = false;
	float linearDamping = 0.99f;
	float angularDamping = 0.99f;
	float staticFriction = .5;
	float dynamicFriction = .5;
	float bounciness = .6;
	float mass = 1;

	if (LUAFIELDEXIST(Mass))
		mass = GETLUAFIELD(Mass, float);

	if (LUAFIELDEXIST(Bounciness))
		bounciness = GETLUAFIELD(Bounciness, float);

	if (LUAFIELDEXIST(DynamicFriction))
		dynamicFriction = GETLUAFIELD(DynamicFriction, float);

	if (LUAFIELDEXIST(StaticFriction))
		staticFriction = GETLUAFIELD(StaticFriction, float);

	if (LUAFIELDEXIST(AngularDamping))
		angularDamping = GETLUAFIELD(AngularDamping, float);

	if (LUAFIELDEXIST(LinearDamping))
		linearDamping = GETLUAFIELD(LinearDamping, float);

	if (LUAFIELDEXIST(Kinematic))
		isKinematic = GETLUAFIELD(Kinematic, bool);

	if (LUAFIELDEXIST(Static))
		isStatic = GETLUAFIELD(Static, bool);

	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	std::tuple<float, float, float> pos = t->getPosition().toTuple();
	std::tuple<float, float, float> rot = t->getRotation().toTuple();
	Vector3 scale = t->getSize();

	if (LUAFIELDEXIST(Type)) { //Sphere
		std::string t = GETLUASTRINGFIELD(Type);
		if (t == "Sphere") {
			float r = 1.0f;
			if (LUAFIELDEXIST(Diameter)) r = GETLUAFIELD(Diameter, float);
			r /= 2.0f;

			_rb = new RigidBody(r, _gameObject, _gameObject->getName(), gameObjectsCollision, isStatic, pos, isKinematic, linearDamping,
				angularDamping, staticFriction, dynamicFriction, bounciness, mass);
		}
		else if (t == "Box") { //Box
			float w = 1.0f, h = 1.0f, d = 1.0f;
			if (LUAFIELDEXIST(Width)) w = GETLUAFIELD(Width, float);
			if (LUAFIELDEXIST(Height)) h = GETLUAFIELD(Height, float);
			if (LUAFIELDEXIST(Depth)) d = GETLUAFIELD(Depth, float);

			w *= scale.getX();
			h *= scale.getY();
			d *= scale.getZ();

			_rb = new RigidBody(w, h, d, _gameObject, _gameObject->getName(), gameObjectsCollision, isStatic, pos, isKinematic, linearDamping,
				angularDamping, staticFriction, dynamicFriction, bounciness, mass);
		}
		else if (t == "Capsule") { //Capsule
			float r = 1.0f, h = 1.0f;
			if (LUAFIELDEXIST(Radius)) r = GETLUAFIELD(Radius, float);
			if (LUAFIELDEXIST(Height)) h = GETLUAFIELD(Height, float);

			r *= std::max({ scale.getX(), scale.getZ() });
			r /= 2;
			h *= scale.getY();
			h = abs(h - r);

			_rb = new RigidBody(r, h, _gameObject, _gameObject->getName(), gameObjectsCollision, isStatic, pos, isKinematic, linearDamping,
				angularDamping, staticFriction, dynamicFriction, bounciness, mass);
		}
		_rb->setRotation(rot);
	}

	if (LUAFIELDEXIST(ConstrainAngle) && GETLUAFIELD(ConstrainAngle, bool)) {
		constrainX(true, false);
		constrainY(true, false);
		constrainZ(true, false);
		_constrainRotation = true;
	}

}

void RigidBodyComponent::onEnable()
{
	_rb->enable();
}

void RigidBodyComponent::onDisable()
{
	_rb->disable();
}

void RigidBodyComponent::fixedUpdate()
{

}

void RigidBodyComponent::postFixedUpdate()
{
	if (_rb->isStatic()) return;

	Vector3 position = _rb->getPosition();
	Vector3 rotation = _rb->getRotation();
	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));

	if (!_constrainRotation)
		t->updateFromPhysics(position, rotation);
	else t->updateFromPhysics(position);
}

void RigidBodyComponent::setPosition(Vector3 pos)
{
	_rb->setPosition(pos.toTuple());
}

void RigidBodyComponent::rotate(Vector3 rot)
{
	if (!_rb->rotate(rot.toTuple()))
		_log->log("trying to rotate a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::setRotation(Vector3 rot)
{
	if (!_rb->setRotation(rot.toTuple()))
		_log->log("trying to rotate a static rigidBody will result in nothing", Logger::Level::WARN);
}

void RigidBodyComponent::setScale(Vector3 scale)
{
	if (!_rb->setScale(scale.toTuple()))
		_log->log("trying to scale a static rigidBody will result in nothing", Logger::Level::WARN);
}

void RigidBodyComponent::setStaticFriction(float f)
{
	if (!_rb->setStaticFriction(f))
		_log->log("trying to set the static friction of a static rigidBody will result in nothing", Logger::Level::WARN);
}

void RigidBodyComponent::setDynamicFriction(float f)
{
	if (_rb->setDynamicFriction(f))
		_log->log("trying to set the dynamic friction of a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::setBounciness(float b)
{
	if (!_rb->setBounciness(b))
		_log->log("trying to set the bounciness of a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::setMass(float m)
{
	if (!_rb->setMass(m))
		_log->log("trying to set the mass of a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::setLinearVelocity(const Vector3& vel)
{
	if (!_rb->setLinearVelocity(vel.toTuple()))
		_log->log("trying to set the linear velocity of a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::setAngularVelocity(const Vector3& vel)
{
	if (!_rb->setAngularVelocity(vel.toTuple()))
		_log->log("trying to set the angular velocity of a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::setGravity(bool g)
{
	if (!_rb->setGravity(g))
		_log->log("trying to enable or disable the gravity of a static rigidBody will result in nothig", Logger::Level::WARN);
}

const Vector3& RigidBodyComponent::getAngularVelocity()
{
	return _rb->getAngularVelocity();
}

const Vector3& RigidBodyComponent::getLinearVelocity()
{
	return _rb->getLinearVelocity();
}

float RigidBodyComponent::getMass()
{
	{ return _rb->getMass(); }
}

void RigidBodyComponent::addForce(Vector3& force)
{
	auto tupleForce = force.toTuple();
	if (!_rb->addForce(tupleForce))
		_log->log("trying to move a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::addImpulse(Vector3& impulse)
{
	auto tupleImpulse = impulse.toTuple();
	if (!_rb->addImpulse(tupleImpulse))
		_log->log("trying to move a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::addTorque(Vector3& torque)
{
	auto tupleTorque = torque.toTuple();
	if (!_rb->addTorque(tupleTorque))
		_log->log("trying to rotate a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::moveTo(Vector3& dest)
{
	auto tupleDest = dest.toTuple();
	if (!_rb->moveTo(tupleDest))
		_log->log("trying to move a static/not kinematic rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::constrainX(bool constrain, bool linear)
{
	if (!_rb->constrainX(constrain, linear))
		_log->log("trying to constrain a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::constrainY(bool constrain, bool linear)
{
	if (!_rb->constrainY(constrain, linear))
		_log->log("trying to move a constrain rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::constrainZ(bool constrain, bool linear)
{
	if (!_rb->constrainZ(constrain, linear))
		_log->log("trying to move a constrain rigidBody will result in nothig", Logger::Level::WARN);
}
void RigidBodyComponent::gameObjectsCollision(GameObject* thisGO, GameObject* otherGO)
{
	thisGO->onCollision(otherGO);
	otherGO->onCollision(thisGO);
}