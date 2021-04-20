#include "Vector3.h"

Vector3::Vector3():_x(),_y(),_z()
{
}

Vector3::Vector3(const Vector3& v):_x(v.getX()),_y(v.getY()),_z(v.getZ())
{
}

Vector3::Vector3(double x, double y, double z):_x(x),_y(y),_z(z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::normalize() const
{
	Vector3 r;
	r._x = _x;
	r._y = _y;
	r._z = _z;

	double mag = magnitude();
	if (mag > 0.0) {
		r._x = r._x / mag;
		r._y = r._y / mag;
		r._z = r._z / mag;
	}
	return r;
}

