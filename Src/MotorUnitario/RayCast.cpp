#include "RayCast.h"
#include "MotorFisico/RayCast.h"
#include "MotorFisico/Exceptions.h"
#include "Engine.h"
#include "Logger.h"

#define VEC3_TO_TUPLE(vec) std::tuple<float,float,float>(vec.getX(),vec.getY(),vec.getZ())
#define TUPLE_TO_VEC3(tuple) Vector3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))

RayCast::RayCast(const Vector3& source, const Vector3& directionVector, float distance, RayCast::Type collidesWith) : _raycast()
{
	try {
		PxRayCast ray = PxRayCast(VEC3_TO_TUPLE(source), VEC3_TO_TUPLE(directionVector), distance, (PxRayCast::Type)collidesWith);
		getInformation(ray);
	}
	catch (const ExcepcionTAD& e) {
		Logger::getInstance()->log(e.msg(), Logger::Level::ERROR);
	}
}

RayCast::RayCast(const Vector3& source, const Vector3& target, RayCast::Type collidesWith)
{
	if (source == target)
		throw ERayCast("Raycast source position cannot be the same as target position");

	try {
		PxRayCast ray = PxRayCast(VEC3_TO_TUPLE(source), VEC3_TO_TUPLE((target - source).normalize()), (target - source).magnitude(), (PxRayCast::Type)collidesWith);
		getInformation(ray);
	}
	catch (const ExcepcionTAD& e) {
		Logger::getInstance()->log(e.msg(), Logger::Level::ERROR);
	}
}

void RayCast::getInformation(const PxRayCast& ray)
{
	PxRayCast::RayCastHit info = ray.getRayCastInformation();

	_raycast.hit = info.hit;
	if (_raycast.hit) {
		_raycast.distance = info.distance;
		_raycast.hitPosition = TUPLE_TO_VEC3(info.hitPosition);
		_raycast.gameObjectHitted = Engine::getInstance()->findGameObject(info.actorName);
	}
}
