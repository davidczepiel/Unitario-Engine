#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"  
#include "Component.h"

class GameObject;

class Transform : public Component {
public:
	Transform();
	Transform(GameObject* gameObject);
	Transform(GameObject* gameObject,const Vector3& position, const Vector3& rotation, const Vector3& scale);
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

	void updateFromPhysics(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// Returns the current rotation of the transform
	/// </summary>
	inline const Vector3& getRotation() const { return _rotation; }

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
