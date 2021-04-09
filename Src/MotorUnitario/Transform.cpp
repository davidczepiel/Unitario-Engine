#include "Transform.h"

Transform::Transform(GameObject* gameObject) :Component(0, gameObject), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale, GameObject* gameObject) : Component(0, gameObject),
_position(position), _rotation(rotation), _scale(scale)
{
}

Transform::~Transform()
{
}