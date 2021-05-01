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
	/// <summary>
	/// 
	/// </summary>
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

	void updateFromPhysics(const Vector3& position);

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
	inline const Vector3& getScale() const { return _scale; }

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
	Quaternion ToQuaternion(double yaw, double pitch, double roll); // yaw (Z), pitch (Y), roll (X)

private:
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;
	Vector3 _dir;
};


#endif // !TRANSFORM_H
