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
	//Rotation matrix for Y Axis
	/*Vector3 yaw;
	yaw.setX(cos((int)_rotation.getX()%360) * _dir.getX() - sin((int)_rotation.getZ() % 360) * _dir.getZ());
	yaw.setY(0);
	yaw.setZ(sin((int)_rotation.getX() % 360) * _dir.getX() + cos(_rotation.getZ()) * _dir.getZ());
	//Rotation matrix for X Axis
	Vector3 pitch;
	pitch.setX(cos((int)_rotation.getX() % 360) * _dir.getX() - sin(_rotation.getY()) * _dir.getY());
	pitch.setY(sin(_rotation.getX()) * _dir.getX() + cos(_rotation.getY()) * _dir.getY());
	pitch.setZ(_dir.getZ());
	//set the dir
	_dir = yaw + pitch;
	_dir.normalize();*/

	double yaw = _rotation.getY(), pitch = _rotation.getX();
	_dir.setX(cos(yaw)*cos(pitch));
	_dir.setY(sin(yaw)*cos(pitch));
	_dir.setZ(sin(pitch));

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

Transform::~Transform()
{
	GraphicsEngine::getInstance()->removeNode(_gameObject->getName());
}

Vector3 Transform::getForward() const
{
	return _dir;
}