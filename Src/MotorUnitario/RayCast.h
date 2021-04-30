#pragma once
#ifndef RAYCAST_H
#define RAYCAST_H

class GameObject;
class PxRayCast;

#include "Vector3.h"

class RayCast {
public:
	/// <summary>
	/// The types of colliders
	/// </summary>
	enum class Type {
		Both, Static, Dynamic
	};

	struct RayCastHit {
		bool hit = false;
		GameObject* gameObjectHitted = nullptr;
		Vector3 hitPosition = { 0, 0, 0 };
		float distance = -1.0f;
	};

	/// <summary>
	/// Casts a ray from source in the directionVector a distance units, only colliding with RayCast::Type objects
	/// </summary>
	/// <param name="source">: Position</param>
	/// <param name="directionVector">: Direction</param>
	/// <param name="distance">: Max distance</param>
	/// <param name="collidesWith">: the ray only collides with this types of colliders</param>
	/// <exception cref="ERayCast">thrown when distance is negative, or direction vector is all zeroes</exception>
	RayCast(const Vector3& source, const Vector3& directionVector, float distance, RayCast::Type collidesWith = RayCast::Type::Both);

	/// <summary>
	/// Casts a ray from source towards target, only colliding with RayCast::Type objects
	/// </summary>
	/// <param name="source">: source position</param>
	/// <param name="target">: target position</param>
	/// <param name="collidesWith">: the ray only collides with this types of colliders</param>
	/// <exception cref="ERayCast">thrown when target equals source</exception>
	RayCast(const Vector3& source, const Vector3& target, RayCast::Type collidesWith = RayCast::Type::Both);

	/// <summary>
	/// Returns the raycast aftermath
	/// </summary>
	/// <returns></returns>
	inline const RayCastHit& getRayCastInformation() const { return _raycast; }

private:

	void getInformation(const PxRayCast& ray);

	RayCastHit _raycast;
};

#endif // !RAYCAST_H