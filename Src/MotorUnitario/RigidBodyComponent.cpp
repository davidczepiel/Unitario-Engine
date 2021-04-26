#include "RigidBodyComponent.h"
#include "Transform.h"
#include "MotorFisico/RigidBody.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "Logger.h"
#include "Vector3.h"


RigidBodyComponent::RigidBodyComponent() : Component(ComponentId::Rigidbody, nullptr), _rb(nullptr), _tr(nullptr), _log(nullptr)
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
	float linearDamping = 0.0f;
	float angularDamping = 0.0f;
	float staticFriction = 1.0f;
	float dynamicFriction = 1.0f;
	float bounciness = 1.0f;
	float mass = 1000.0f;

	if (LUAFIELDEXIST(mass))
		GETLUAFIELD(mass, float);

	if (LUAFIELDEXIST(bounciness))
		GETLUAFIELD(bounciness, float);

	if (LUAFIELDEXIST(dynamicFriction))
		GETLUAFIELD(dynamicFriction, float);

	if (LUAFIELDEXIST(staticFriction))
		GETLUAFIELD(staticFriction, float);

	if (LUAFIELDEXIST(angularDamping))
		GETLUAFIELD(angularDamping, float);

	if (LUAFIELDEXIST(linearDamping))
		linearDamping = GETLUAFIELD(linearDamping, float);

	if (LUAFIELDEXIST(Kinematic))
		isKinematic = GETLUAFIELD(Kinematic, bool);

	if (LUAFIELDEXIST(Position))
	{
		int x, y, z;
		x = y = z = 0;
		if (!data["Position"]["X"].isNil())
			x = data["Position"]["X"].cast<int>();
		if (!data["Position"]["Y"].isNil())
			x = data["Position"]["Y"].cast<int>();
		if (!data["Position"]["Z"].isNil())
			x = data["Position"]["Z"].cast<int>();
		position = Vector3(x, y, z);

	}
	if (LUAFIELDEXIST(Static))
		isStatic = GETLUAFIELD(Static, bool);
	if (LUAFIELDEXIST(Type)) { //Sphere
		std::string t = GETLUASTRINGFIELD(Type);
		if (t == "Sphere") {
			float r = 1.0f;
			if (LUAFIELDEXIST(Radius))
				r = GETLUAFIELD(Radius, float);
			_rb = new RigidBody(r, _gameObject, gameObjectsCollision, isStatic, VEC3_TO_TUPLE(position), isKinematic, linearDamping,
				angularDamping, staticFriction, dynamicFriction, bounciness, mass);
		}
		else if (t == "Box") { //Box
			float w = 1.0f, h = 1.0f, d = 1.0f;
			if (LUAFIELDEXIST(Width))
				w = GETLUAFIELD(Width, float);
			if (LUAFIELDEXIST(Height))
				h = GETLUAFIELD(Height, float);
			if (LUAFIELDEXIST(Depth))
				d = GETLUAFIELD(Depth, float);

			_rb = new RigidBody(w, h, d, _gameObject, gameObjectsCollision, isStatic, VEC3_TO_TUPLE(position), isKinematic, linearDamping,
				angularDamping, staticFriction, dynamicFriction, bounciness, mass);
		}
		else if (t == "Capsule") { //Capsule
			float r = 1.0f, h = 1.0f;
			if (LUAFIELDEXIST(Radius))
				r = GETLUAFIELD(Radius, float);
			if (LUAFIELDEXIST(Height))
				h = GETLUAFIELD(Height, float);
			_rb = new RigidBody(r, h, _gameObject, gameObjectsCollision, isStatic, VEC3_TO_TUPLE(position), isKinematic, linearDamping,
				angularDamping, staticFriction, dynamicFriction, bounciness, mass);
		}
	}

}

void RigidBodyComponent::fixedUpdate()
{
	if (_rb->isStatic()) return;

	Vector3 position = TUPLE_TO_VEC3(_rb->getPosition());
	Vector3 rotation = TUPLE_TO_VEC3(_rb->getRotation());

	Transform* t = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	t->updateFromPhysics(position, rotation);
}

void RigidBodyComponent::setPosition(Vector3 pos)
{
	_rb->setPosition(VEC3_TO_TUPLE(pos));
}

void RigidBodyComponent::setRotation(Vector3 rot)
{
	if (!_rb->rotate(VEC3_TO_TUPLE(rot)))
		_log->log("trying to rotate a static rigidBody will result in nothig", Logger::Level::WARN);

}

void RigidBodyComponent::setScale(Vector3 scale)
{
	if (!_rb->setScale(VEC3_TO_TUPLE(scale)))
		_log->log("trying to scale a static rigidBody will result in nothig", Logger::Level::WARN);

}

void RigidBodyComponent::setStaticFriction(float f)
{
	if (!_rb->setStaticFriction(f))
		_log->log("trying to set the static friction of a static rigidBody will result in nothig", Logger::Level::WARN);

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
	if (!_rb->setLinearVelocity(VEC3_TO_TUPLE(vel)))
		_log->log("trying to set the linear velocity of a static rigidBody will result in nothig", Logger::Level::WARN);

}

void RigidBodyComponent::setAngularVelocity(const Vector3& vel)
{
	if (!_rb->setAngularVelocity(VEC3_TO_TUPLE(vel)))
		_log->log("trying to set the angular velocity of a static rigidBody will result in nothig", Logger::Level::WARN);

}

void RigidBodyComponent::setGravity(bool g)
{
	if (!_rb->setGravity(g))
		_log->log("trying to enable or disable the gravity of a static rigidBody will result in nothig", Logger::Level::WARN);

}

const Vector3& RigidBodyComponent::getAngularVelocity()
{
	return TUPLE_TO_VEC3(_rb->getAngularVelocity());
}

const Vector3& RigidBodyComponent::getLinearVelocity()
{
	return TUPLE_TO_VEC3(_rb->getLinearVelocity());
}

float RigidBodyComponent::getMass()
{
	{ return _rb->getMass(); }
}

void RigidBodyComponent::addForce(Vector3& force)
{
	auto tupleForce = VEC3_TO_TUPLE(force);
	if (!_rb->addForce(tupleForce))
		_log->log("trying to move a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::addImpulse(Vector3& impulse)
{
	auto tupleImpulse = VEC3_TO_TUPLE(impulse);
	if (!_rb->addImpulse(tupleImpulse))
		_log->log("trying to move a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::addTorque(Vector3& torque)
{
	auto tupleTorque = VEC3_TO_TUPLE(torque);
	if (!_rb->addTorque(tupleTorque))
		_log->log("trying to rotate a static rigidBody will result in nothig", Logger::Level::WARN);
}

void RigidBodyComponent::moveTo(Vector3& dest)
{
	auto tupleDest = VEC3_TO_TUPLE(dest);
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