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