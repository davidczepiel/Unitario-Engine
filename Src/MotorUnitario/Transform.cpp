#include "Transform.h"
#include "GameObject.h"

Transform::Transform() :Component(0), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

Transform::Transform(GameObject* gameObject): Component(/*ComponentId::Transform*/0,gameObject), _position(0,0,0), _rotation(0,0,0),_scale(1,1,1)
{
}

Transform::Transform(GameObject* gameObject, const Vector3& position, const Vector3& rotation, const Vector3& scale): Component(/*ComponentId::Transform*/0, gameObject), 
_position(position),_rotation(rotation),_scale(scale)
{
}

Transform::~Transform()
{
}