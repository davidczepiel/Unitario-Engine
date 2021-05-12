#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"  
#include "Component.h"
#include <cmath>

#define PI 3.1416 

class GameObject;

struct Quaternion {
	double w, x, y, z;
};

struct EulerAngles {
	double roll, pitch, yaw;
};


class Transform : public Component {
public:

	Transform();

	~Transform();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Returns the current position of the transform
	/// </summary>
	inline const Vector3& getPosition() const { return _position; }

	/// <summary>
	/// Sets a new transform position
	/// </summary>
	/// <param name="position">New position</param>
	void setPosition(const Vector3& position);

	/// <summary>
	/// Called to update transform's position when object has a rigidbody
	/// </summary>
	/// <param name="position">physx's rigidbody position</param>
	void updateFromPhysics(const Vector3& position);

	/// <summary>
	/// Called to update transform's position and rotation when object has a rigidbody
	/// </summary>
	/// <param name="position">Physx's rigidbody position</param>
	/// <param name="rotation">Physx's rigidbody rotation</param>
	void updateFromPhysics(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// Returns the current rotation of the transform
	/// </summary>
	inline const Vector3& getRotation() const { return _rotation; }

	/// <summary>
	/// Returns the direccion where the object is looking at
	/// </summary>
	Vector3 getForward() const;

	/// <summary>
	/// Sets a new transform rotation
	/// </summary>
	/// <param name="position">New rotation</param>
	void setRotation(const Vector3& rotation);

	/// <summary>
	/// Returns the current scale of the transform
	/// </summary>
	inline Vector3 getScale() const { return _scale; }

	/// <summary>
	/// Returns the current size of the transform
	/// </summary>
	inline Vector3 getSize() const { return _scale * _proportions; }

	/// <summary>
	/// Returns the current scale of the transform
	/// </summary>
	inline const Vector3& getDir() const { return _dir; }

	/// <summary>
	/// Sets a new transform scale
	/// </summary>
	/// <param name="position">New scale</param>
	inline void setScale(const Vector3& scale) { _scale = scale; }

	/// <summary>
	/// Conversion to Euler by Quaternion
	/// </summary>
	/// <param name="position">New scale</param>
	EulerAngles ToEulerAngles(Quaternion q);

	/// <summary>
	/// Conversion to Quaternion by Euler angle
	/// </summary>
	/// <param name="position">New scale</param>
	Quaternion ToQuaternion(double pitch, double yaw, double roll); // pitch (X), yaw (Y), roll (Z)

	/// <summary>
	/// Setted by RenderObject to be in accordance to the mesh proportions
	/// </summary>
	/// <param name="proportions"></param>
	inline void setProportions(const Vector3& proportions) { _proportions = proportions; }

private:
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;
	Vector3 _proportions;
	Vector3 _dir;
};


#endif // !TRANSFORM_H
