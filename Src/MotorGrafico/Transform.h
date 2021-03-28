#pragma once
#ifndef  TRANSFORM_H
#define TRANSFORM_H

#include<OgreVector.h>

class Transform {
public:
	Transform();
	Transform(Ogre::Vector3 position, Ogre::Vector3 rotation, Ogre::Vector3 scale);
	~Transform();

	/// <summary>
	/// Returns the current position of the transform
	/// </summary>
	inline Ogre::Vector3 getPosition() const;

	/// <summary>
	/// Sets a new transform position
	/// </summary>
	/// <param name="position">New position</param>
	inline void setPosition(const Ogre::Vector3& position);

	/// <summary>
	/// Returns the current rotation of the transform
	/// </summary>
	inline Ogre::Vector3 getRotation() const;

	/// <summary>
	/// Sets a new transform rotation
	/// </summary>
	/// <param name="position">New rotation</param>
	inline void setRotation(const Ogre::Vector3& rotation);

	/// <summary>
	/// Returns the current scale of the transform
	/// </summary>
	inline Ogre::Vector3 getScale() const;

	/// <summary>
	/// Sets a new transform scale
	/// </summary>
	/// <param name="position">New scale</param>
	inline void setScale(const Ogre::Vector3& scale);
		
private:	
	Ogre::Vector3 _position;
	Ogre::Vector3 _rotation;
	Ogre::Vector3 _scale;
};
#endif // !TRANSFORM_H