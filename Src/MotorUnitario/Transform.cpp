#include "Transform.h"

Transform::Transform() :_position(0,0,0), _rotation(0,0,0),_scale(1,1,1)
{
}

Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale):_position(position),_rotation(rotation),_scale(scale)
{
}

Transform::~Transform()
{
}


