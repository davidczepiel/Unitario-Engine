#include "Logger.h"

#include <ctime>

std::unique_ptr<Logger> Logger::instance = nullptr;

Logger::Logger() : _logLevel(Level::DEBUG), _logFile("Assets/Logs/log.txt", std::fstream::out)
{
}

Logger::~Logger()
{
	if (_logFile.is_open())
		_logFile.close();
}

Logger* Logger::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new Logger());
	}
	return instance.get();
}

void Logger::log(const std::string& message, Level logLevel)
{
	if (logLevel > _logLevel || !_logFile.is_open())
		return;

	// get time
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	if (newtime.tm_hour < 10) _logFile << "0";
	_logFile << newtime.tm_hour << ":";

	if (newtime.tm_min < 10) _logFile << "0";
	_logFile << newtime.tm_min << ":";

	if (newtime.tm_sec < 10) _logFile << "0";
	_logFile << newtime.tm_sec;

	_logFile << " -> " << getLevelAsString(logLevel) << message << '\n' << std::flush;
}


const std::string Logger::getLevelAsString(Level logLevel)
{
	std::string level("Undefined");
	switch (logLevel)
	{
	case Level::FATAL:
		level = "FATAl: ";
		break;
	case Level::ERROR:
		level = "ERROR: ";
		break;
	case Level::WARN:
		level = "WARN: ";
		break;
	case Level::INFO:
		level = "INFO: ";
		break;
	case Level::DEBUG:
		level = "DEBUG: ";
		break;
	case Level::TRACE:
		level = "TRACE: ";
		break;
	default:
		level = "UNDEFINED: ";
		break;
	}
	return level;
}
