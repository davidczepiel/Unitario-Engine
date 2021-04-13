#include "Time.h"

#include "SDL.h"

#include <ctime>

std::unique_ptr<Time> Time::instance = nullptr;

Time::Time(): _msTimeLastTick(), _deltaTime(), _maxDeltaTimeRecorded(0.0f), _fps(60)
{
	_msTimeLastTick = SDL_GetTicks();
}

void Time::update()
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

Time::~Time()
{
}

Time* Time::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new Time());
	}
	return instance.get();
}

Time::Date Time::getDate() const
{
	// get time
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	return { newtime.tm_sec, newtime.tm_min, newtime.tm_hour, newtime.tm_mday, newtime.tm_mon, newtime.tm_year + 1900, newtime.tm_wday };
}
