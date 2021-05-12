#include "RayCast.h"
#include "MotorFisico/RayCast.h"
#include "MotorFisico/Exceptions.h"
#include "Engine.h"
#include "Logger.h"

RayCast::RayCast(const Vector3& source, const Vector3& directionVector, float distance, RayCast::Type collidesWith) : _raycast()
{
	try {
		PxRayCast ray = PxRayCast(source.toTuple(), directionVector.toTuple(), distance, (PxRayCast::Type)collidesWith);
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
		PxRayCast ray = PxRayCast(source.toTuple(), ((target - source).normalize()).toTuple(), (target - source).magnitude(), (PxRayCast::Type)collidesWith);
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
		_raycast.hitPosition = info.hitPosition;
		_raycast.gameObjectHitted = Engine::getInstance()->findGameObject(info.actorName);
	}
}
