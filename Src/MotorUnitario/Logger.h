#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <string>
#include <fstream>

class Logger
{
public:
	enum class Level {
		//Any error that is forcing a shutdown
		FATAL = 0,

		//Any error which is fatal to the operation
		ERROR,		

		//Anything that can potentially cause application oddities
		WARN, 

		//Generally useful information to log
		INFO,

		//Useful to provide context to understand the steps leading up to errors and warnings
		TRACE,

		//Information that is diagnostically helpful, but cutted out of release builds
		DEBUG
	};

public:
	~Logger();

	/// <summary>
	/// Returns the instance of Logger, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static Logger* getInstance();
	Logger& operator=(const Logger&) = delete;
	Logger(Logger& other) = delete;

	/// <summary>
	/// Sets the log level.
	/// <para>Every log above this level will be ignored</para>
	/// </summary>
	/// <param name="logLevel"></param>
	inline void setLogLevel(Level logLevel) { _logLevel = logLevel; }

	/// <summary>
	/// Logs message into the logFile
	/// </summary>
	/// <param name="message">: message to Log</param>
	/// <param name="logLevel">: level of relevance of said message</param>
	void log(const std::string& message, Level logLevel = Level::INFO);

private:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	Logger();

	static std::unique_ptr<Logger> instance;

	/// <summary>
	/// Used to convert Level enum to the correspondient string
	/// </summary>
	/// <param name="logLevel"></param>
	/// <returns></returns>
	const std::string getLevelAsString(Level logLevel);

	Level _logLevel;

	std::ofstream _logFile;
};

#endif /*LOGGER.h*/