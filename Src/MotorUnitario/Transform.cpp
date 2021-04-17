#include "Transform.h"


Transform::Transform(GameObject* gameObject) :Component(0,gameObject),_position(0,0,0), _rotation(0,0,0),_scale(1,1,1)
{
}

Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale, GameObject* gameObject) : Component(0,gameObject),
	_position(position),_rotation(rotation),_scale(scale)
{
}

Transform::~Transform()
{
}

void Transform::awake(luabridge::LuaRef& data)
{
	luabridge::LuaRef lua_coord = data["Coord"];
	_position = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
	std::cout << "Tr: X=" << _position.getX() << ", Y=" << _position.getY() << ", Z=" << _position.getZ() << std::endl;
}
