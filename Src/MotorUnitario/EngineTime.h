#pragma once

#ifndef TIME_H
#define TIME_H

#include <memory>

class EngineTime
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
	~EngineTime();

	/// <summary>
	/// Returns the instance of KeyBoardInput, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static EngineTime* getInstance();
	EngineTime& operator=(const EngineTime&) = delete;
	EngineTime(EngineTime& other) = delete;

	/// <summary>
	/// Time since last frame
	/// </summary>
	/// <returns>seconds</returns>
	inline float deltaTime() const { return _deltaTime; }

	/// <summary>
	/// Returns fixed delta time
	/// </summary>
	/// <returns></returns>
	inline float fixedDeltaTime() { return _fixedDeltaTime; }

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

	/// <summary>
	/// Sets the time between two calls to the phisycs engine
	/// </summary>
	/// <param name="newFixedDeltaTime"> The new value of fixed delta time in seconds</param>
	inline void setFixedDeltaTime(unsigned int newFixedDeltaTime) { _fixedDeltaTime = newFixedDeltaTime * 1000.0f; }

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	EngineTime();

	/// <summary>
	/// When called, calculates deltaTime with the time value it obtained last time it was called
	/// </summary>
	void update();

	/// <summary>
	/// When called, calculates deltaTime with the time value it obtained last time it was called
	/// </summary>
	void fixedTimeUpdate();

	/// <summary>
	/// Returns the number of calls to the phisycs engine in this frame
	/// </summary>
	int fixedUpdateRequired();

	static std::unique_ptr<EngineTime> instance;

	unsigned int _msTimeLastTick;
	unsigned int _msTimeLastFixed;

	float _deltaTime;
	unsigned int _fixedDeltaTime;
	float _maxDeltaTimeRecorded;

	int _fps;

	/// <summary>
	/// Used so only Engine is able to update deltaTime
	/// if this methods were in public, the user could call those
	/// </summary>
	friend class Engine;
};

#endif /*EngineTime.h*/