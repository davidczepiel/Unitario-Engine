#include "..\..\Src\MotorGrafico\Transform.h"

Transform::Transform() :_position(0, 0, 0), _rotation(0, 0, 0),_scale(1, 1, 1)
{
}

Transform::Transform(Ogre::Vector3 position, Ogre::Vector3 rotation, Ogre::Vector3 scale):_position(position),_rotation(rotation),_scale(scale)
{
}

Transform::~Transform()
{
}

inline Ogre::Vector3 Transform::getPosition() const
{
	return _position;
}

inline void Transform::setPosition(const Ogre::Vector3& position)
{
	_position = position;
}

inline Ogre::Vector3 Transform::getRotation() const
{
	return _rotation;
}

inline void Transform::setRotation(const Ogre::Vector3& rotation)
{
	_rotation = rotation;
}

inline Ogre::Vector3 Transform::getScale() const
{
	return _scale;
}

inline void Transform::setScale(const Ogre::Vector3& scale)
{
	_scale = scale;
}


