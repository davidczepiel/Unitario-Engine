#include "Transform.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "MotorGrafico/GraphicsEngine.h"
#include "includeLUA.h"

#include <math.h>
#define PI 3.14159265

Transform::Transform() : Component(ComponentId::Transform), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _dir(0, 0, -1)
{
}

void Transform::setPosition(const Vector3& position)
{
	_position = position;
	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setPosition(_position);
	}

	ColliderComponent* boxColl = dynamic_cast<BoxColliderComponent*>(_gameObject->getComponent(ComponentId::BoxCollider));
	ColliderComponent* sphColl = dynamic_cast<SphereColliderComponent*>(_gameObject->getComponent(ComponentId::SphereCollider));
	ColliderComponent* capsColl = dynamic_cast<CapsuleColliderComponent*>(_gameObject->getComponent(ComponentId::CapsuleCollider));
	if (boxColl != nullptr) {
		boxColl->setPosition(_position);
	}
	else if (sphColl != nullptr) {
		sphColl->setPosition(_position);
	}
	else if (capsColl != nullptr) {
		capsColl->setPosition(_position);
	}
}

void Transform::updateFromPhysics(const Vector3& position)
{
	_position = position;
}

void Transform::awake(luabridge::LuaRef& data)
{
	const std::string& parentName = _gameObject->getParent() != nullptr ? _gameObject->getParent()->getName() : "";
	GraphicsEngine::getInstance()->addNode(_gameObject->getName(), parentName);

	if (LUAFIELDEXIST(Coord)) {
	luabridge::LuaRef lua_coord = data["Coord"];
	_position = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
	std::cout << "Tr: X=" << _position.getX() << ", Y=" << _position.getY() << ", Z=" << _position.getZ() << std::endl;
	}

	if (LUAFIELDEXIST(Rotation)) {
	luabridge::LuaRef lua_coord = data["Rotation"];
	_rotation = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
	}

	if (LUAFIELDEXIST(Scale)) {
	luabridge::LuaRef lua_coord = data["Scale"];
	_scale = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
	}
}

void Transform::updateFromPhysics(const Vector3& position, const Vector3& rotation)
{
	_position = position;
	_rotation = rotation;
}

void Transform::setRotation(const Vector3& rotation)
{
	_rotation = rotation;

	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setRotation(_rotation);
	}

	ColliderComponent* boxColl = dynamic_cast<BoxColliderComponent*>(_gameObject->getComponent(ComponentId::BoxCollider));
	ColliderComponent* sphColl = dynamic_cast<SphereColliderComponent*>(_gameObject->getComponent(ComponentId::SphereCollider));
	ColliderComponent* capsColl = dynamic_cast<CapsuleColliderComponent*>(_gameObject->getComponent(ComponentId::CapsuleCollider));
	if (boxColl != nullptr) {
		boxColl->setRotation(getForward());
	}
	else if (sphColl != nullptr) {
		sphColl->setRotation(getForward());
	}
	else if (capsColl != nullptr) {
		capsColl->setRotation(getForward());
	}
}

EulerAngles Transform::ToEulerAngles(Quaternion q)
{
	EulerAngles angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.roll = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		angles.pitch = std::copysign(PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.pitch = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.yaw = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

Quaternion Transform::ToQuaternion(double yaw, double pitch, double roll)
{
	// Abbreviations for the various angular functions
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

Transform::~Transform()
{
	GraphicsEngine::getInstance()->removeNode(_gameObject->getName());
}

Vector3 Transform::getForward() const
{
	return _dir;
}