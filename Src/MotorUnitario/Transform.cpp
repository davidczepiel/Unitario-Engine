#include "Transform.h"
//#include "Vector3.h"

Transform::Transform() :_position(0,0,0), _rotation(0,0,0),_scale(1,1,1)
{
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale):_position(position),_rotation(rotation),_scale(scale)
{
}

Transform::~Transform()
{
}


