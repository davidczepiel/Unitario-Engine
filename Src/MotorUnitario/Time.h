#pragma once

#ifndef TIME_H
#define TIME_H

#include <memory>

class Time
{
public:
	struct Date {
		int sec;   // seconds after the minute - [0, 60] including leap second
		int min;   // minutes after the hour - [0, 59]
		int hour;  // hours since midnight - [0, 23]
		int monthday;  // day of the month - [1, 31]
		int month;   // months since January - [0, 11]
		int year;  // years
		int weekday;  // days since Sunday - [0, 6]
	};

public:
	~Time();

	/// <summary>
	/// Returns the instance of KeyBoardInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static Time* getInstance();
	Time& operator=(const Time&) = delete;
	Time(Time& other) = delete;

	/// <summary>
	/// Time since last frame
	/// </summary>
	/// <returns>seconds</returns>
	inline float deltaTime() const { return _deltaTime; }

	/// <summary>
	/// Maximum deltaTime recorded
	/// </summary>
	/// <returns>seconds</returns>
	inline float getMaxRecordedDeltaTime() const { return _maxDeltaTimeRecorded; }

	/// <summary>
	/// Update rate per second
	/// </summary>
	/// <returns>number of calculated frames per second</returns>
	inline int getFPS() const { return _fps; }

	/// <summary>
	/// Returns the computer user date
	/// </summary>
	/// <returns></returns>
	Date getDate() const;

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	Time();

	/// <summary>
	/// When called, calculates deltaTime with the time value it obtained last time it was called
	/// </summary>
	void update();

	static std::unique_ptr<Time> instance;

	unsigned int _msTimeLastTick;

	float _deltaTime;
	float _maxDeltaTimeRecorded;

	int _fps;

	/// <summary>
	/// Used so only Engine is able to update deltaTime
	/// if this methods were in public, the user could call those
	/// </summary>
	friend class Engine;
};

#endif /*Time.h*/