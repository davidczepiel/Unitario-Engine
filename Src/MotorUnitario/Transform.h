#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"  //NOTA: no me deja poner class Vector3; me da error,asi que de momento pongo el include
//class Vector3;
class Transform {
public:
	Transform();
	Transform(Vector3 position, Vector3 rotation, Vector3 scale);
	~Transform();

	/// <summary>
	/// Returns the current position of the transform
	/// </summary>
	inline const Vector3& getPosition() const { return _position; }

	/// <summary>
	/// Sets a new transform position
	/// </summary>
	/// <param name="position">New position</param>
	inline void setPosition(const Vector3& position) { _position = position; }

	/// <summary>
	/// Returns the current rotation of the transform
	/// </summary>
	inline const Vector3& getRotation() const { return _rotation; }

	/// <summary>
	/// Sets a new transform rotation
	/// </summary>
	/// <param name="position">New rotation</param>
	inline void setRotation(const Vector3& rotation) { _rotation = rotation; }

	/// <summary>
	/// Returns the current scale of the transform
	/// </summary>
	inline const Vector3& getScale() const { return _scale; }

	/// <summary>
	/// Sets a new transform scale
	/// </summary>
	/// <param name="position">New scale</param>
	inline void setScale(const Vector3& scale) { _scale = scale; }
		
private:	
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;
};
#endif // !TRANSFORM_H