#include "Transform.h"
#include "GameObject.h"
#include "ComponentIDs.h"

Transform::Transform(): Component(ComponentId::Transform), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

Transform::Transform(GameObject* gameObject): Component(ComponentId::Transform,gameObject), _position(0,0,0), _rotation(0,0,0),_scale(1,1,1)
{
}

Transform::Transform(GameObject* gameObject, const Vector3& position, const Vector3& rotation, const Vector3& scale): Component(ComponentId::Transform, gameObject), 
_position(position),_rotation(rotation),_scale(scale)
{
}

Transform::~Transform()
{
}