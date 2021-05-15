#include "Transform.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "MotorGrafico/GraphicsEngine.h"
#include "includeLUA.h"

#include <math.h>
#define PI 3.14159265


Transform::Transform() : Component(ComponentId::Transform), 
	_position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _dir(0, 0, -1), _proportions(1, 1, 1)
{
}

void Transform::setPosition(const Vector3& position)
{
	_position = position;

	if (_gameObject->hasComponent(ComponentId::Rigidbody))			GETCOMPONENT(RigidBodyComponent, ComponentId::Rigidbody)->setPosition(_position);
	if (_gameObject->hasComponent(ComponentId::BoxCollider))		GETCOMPONENT(BoxColliderComponent, ComponentId::BoxCollider)->setPosition(_position); 
	if (_gameObject->hasComponent(ComponentId::SphereCollider))		GETCOMPONENT(SphereColliderComponent, ComponentId::SphereCollider)->setPosition(_position);
	if (_gameObject->hasComponent(ComponentId::CapsuleCollider))	GETCOMPONENT(CapsuleColliderComponent, ComponentId::CapsuleCollider)->setPosition(_position);
}

void Transform::updateFromPhysics(const Vector3& position)
{
	_position = position;
}

void Transform::awake(luabridge::LuaRef& data)
{
	GraphicsEngine::getInstance()->addNode(_gameObject->getName());

	if (LUAFIELDEXIST(Coord)) {
		luabridge::LuaRef lua_coord = data["Coord"];
		_position = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
		//std::cout << "Tr: X=" << _position.getX() << ", Y=" << _position.getY() << ", Z=" << _position.getZ() << std::endl;
	}

	if (LUAFIELDEXIST(Rotation)) {
		luabridge::LuaRef lua_coord = data["Rotation"];
		_rotation = { lua_coord["X"].cast<double>() * PI / 180, lua_coord["Y"].cast<double>() * PI / 180, lua_coord["Z"].cast<double>() * PI / 180 };
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

	if (_gameObject->hasComponent(ComponentId::Rigidbody))			GETCOMPONENT(RigidBodyComponent, ComponentId::Rigidbody)->setRotation(_rotation);
	if (_gameObject->hasComponent(ComponentId::BoxCollider))		GETCOMPONENT(BoxColliderComponent, ComponentId::BoxCollider)->setRotation(_rotation);
	if (_gameObject->hasComponent(ComponentId::SphereCollider))		GETCOMPONENT(SphereColliderComponent, ComponentId::SphereCollider)->setRotation(_rotation);
	if (_gameObject->hasComponent(ComponentId::CapsuleCollider))	GETCOMPONENT(CapsuleColliderComponent, ComponentId::CapsuleCollider)->setRotation(_rotation);
}


EulerAngles Transform::ToEulerAngles(Quaternion q)
{
	EulerAngles angles;

	// pitch (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.pitch = std::atan2(sinr_cosp, cosr_cosp);

	// yaw (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		angles.yaw = std::copysign(PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.yaw = std::asin(sinp);

	// roll (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.roll = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

Quaternion Transform::ToQuaternion(double pitch, double yaw, double roll)
{
	// Abbreviations for the various angular functions
	double cy = cos(pitch * 0.5);
	double sy = sin(pitch * 0.5);
	double cp = cos(yaw * 0.5);
	double sp = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.z = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.x = cr * cp * sy - sr * sp * cy;

	return q;
}

Transform::~Transform()
{
	GraphicsEngine::getInstance()->removeNode(_gameObject->getName());
}

Vector3 Transform::getForward() const
{
	double X = sin(_rotation.getY()) * cos(_rotation.getX());
	double Y = sin(-_rotation.getX());
	double Z = cos(_rotation.getX()) * cos(_rotation.getY());

	return Vector3(X, Y, -Z);
}