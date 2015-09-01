#pragma once

#include <sstream>
#include <string>

#include "..\Config.h"

#define SPARKY_LOG_LEVEL_FATAL 0
#define SPARKY_LOG_LEVEL_ERROR 1
#define SPARKY_LOG_LEVEL_WARN  2
#define SPARKY_LOG_LEVEL_INFO  3
#define SPARKY_LOG_LEVEL_SUCCESS  4


namespace engine{

	void PlatformLogMessage(uint level, std::string message);

	static void log_message(int level, std::string message, bool source, std::string filename, int line){
		PlatformLogMessage(level, message);
		if (source && (filename != "nubdevenginegl.cpp")){
			std::ostringstream sstream;
			sstream << '\t' << "File: " << filename << " | Line: " << line << std::endl;
			PlatformLogMessage(level, sstream.str());
		}
	}
}


#ifndef SPARKY_LOG_LEVEL
#define SPARKY_LOG_LEVEL SPARKY_LOG_LEVEL_SUCCESS
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_FATAL
#define SPARKY_FATAL(message) log_message(SPARKY_LOG_LEVEL_FATAL, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define SPARKY_FATAL(...)
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_ERROR
#define SPARKY_ERROR(message) log_message(SPARKY_LOG_LEVEL_ERROR, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define SPARKY_ERROR(...)
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_WARN
#define SPARKY_WARN(message) log_message(SPARKY_LOG_LEVEL_WARN, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define SPARKY_WARN(...)
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_INFO
#define SPARKY_INFO(message) log_message(SPARKY_LOG_LEVEL_INFO, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define SPARKY_INFO(...)
#endif

#define NUB_CHECK(x, message) \
	if(!x) \
		SPARKY_FATAL(message);