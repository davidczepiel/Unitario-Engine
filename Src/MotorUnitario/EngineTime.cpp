#include "EngineTime.h"

#include "SDL.h"

#include <ctime>

std::unique_ptr<EngineTime> EngineTime::instance = nullptr;

EngineTime::EngineTime(): _msTimeLastTick(), _deltaTime(0.0f), _msTimeLastFixed(), _maxDeltaTimeRecorded(0.0f), _fps(60), _fixedDeltaTime(20)
{
	_msTimeLastTick = SDL_GetTicks();
	_msTimeLastFixed = SDL_GetTicks();
}

void EngineTime::update()
{
	Uint32 timeNow = SDL_GetTicks();

	_deltaTime = static_cast<float>((timeNow - _msTimeLastTick)) / 1000.0f;

	if (_deltaTime > _maxDeltaTimeRecorded)
		_maxDeltaTimeRecorded = _deltaTime;

	_msTimeLastTick = timeNow;

	//I take the median between last tick fps and now, so it's more stable
	//Adding 1 so it rounds up (unless both are equal)
	_fps = (_fps + static_cast<int>(1.0f / _deltaTime) + 1) / 2;
}

void EngineTime::fixedTimeUpdate()
{
	Uint32 timeNow = SDL_GetTicks();

	_msTimeLastFixed = timeNow;
}

int EngineTime::fixedUpdateRequired()
{
	Uint32 timeNow = SDL_GetTicks();

	return (timeNow - _msTimeLastFixed) / _fixedDeltaTime;
}

EngineTime::~EngineTime()
{
}

EngineTime* EngineTime::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new EngineTime());
	}
	return instance.get();
}

void EngineTime::startTimeNow()
{
	_msTimeLastTick = SDL_GetTicks();
	_msTimeLastFixed = SDL_GetTicks();
	_deltaTime = 0.0f;
}

EngineTime::Date EngineTime::getDate() const
{
	// get time
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	return { newtime.tm_sec, newtime.tm_min, newtime.tm_hour, newtime.tm_mday, newtime.tm_mon, newtime.tm_year + 1900, newtime.tm_wday };
}
