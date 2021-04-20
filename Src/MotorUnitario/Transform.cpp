#include "Transform.h"
#include "GameObject.h"
#include "ComponentIDs.h"

#include <math.h>
#define PI 3.14159265

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

Vector3 Transform::getForward() const
{
	double X = sin(_rotation.getY() * PI / 180.0) * cos(_rotation.getX() * PI / 180.0);
	double Y = sin(-_rotation.getX() * PI / 180.0);
	double Z = cos(_rotation.getX() * PI / 180.0) * cos(_rotation.getY() * PI / 180.0);

	return Vector3(X, Y, -Z);
}
