#pragma once

#ifndef PXRAYCAST_H
#define PXRAYCAST_H

#include <tuple>
#include <string>

#define TUPLE_TO_PHYSXVEC3(tuple) physx::PxVec3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))
#define PHYSXVEC3_TO_TUPLE(vec) std::tuple<float,float,float>(vec.x,vec.y,vec.z)

class PxRayCast {

public:
	/// <summary>
	/// The types of colliders
	/// </summary>
	enum class Type {
		Both, Static, Dynamic
	};

	struct RayCastHit {
		bool hit = false;
		std::string actorName = "";
		std::tuple<float, float, float> hitPosition = {0, 0, 0};
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
	PxRayCast(const std::tuple<float, float, float>& source, const std::tuple<float, float, float>& directionVector, float distance, PxRayCast::Type collidesWith);
	
	/// <summary>
	/// Returns the raycast aftermath
	/// </summary>
	/// <returns></returns>
	inline const RayCastHit& getRayCastInformation() const { return _raycast; }

private:

	RayCastHit _raycast;
};

#endif //!PXRAYCAST_H