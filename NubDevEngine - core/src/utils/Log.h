#pragma once

#include <sstream>
#include <string>

#include "..\Config.h"

#define NUB_LOG_LEVEL_FATAL 0
#define NUB_LOG_LEVEL_ERROR 1
#define NUB_LOG_LEVEL_WARN  2
#define NUB_LOG_LEVEL_INFO  3
#define NUB_LOG_LEVEL_SUCCESS  4


namespace engine{

	void PlatformLogMessage(uint level, std::string message);

	static void log_message(int level, std::string message, bool source, std::string filename, int line){
		PlatformLogMessage(level, message);
		if (source && (filename != "nubdevenginegl.cpp")){
			if (level <= _DEBUG_INFO_LEVEL){
				std::ostringstream sstream;
				sstream << '\t' << "File: " << filename << " | Line: " << line;
				PlatformLogMessage(level, sstream.str());
			}
		}
	}
}


#ifndef NUB_LOG_LEVEL
#define NUB_LOG_LEVEL NUB_LOG_LEVEL_SUCCESS
#endif

#if NUB_LOG_LEVEL >= NUB_LOG_LEVEL_FATAL
#define NUB_FATAL(message) log_message(NUB_LOG_LEVEL_FATAL, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define NUB_FATAL(...)
#endif

#if NUB_LOG_LEVEL >= NUB_LOG_LEVEL_ERROR
#define NUB_ERROR(message) log_message(NUB_LOG_LEVEL_ERROR, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define NUB_ERROR(...)
#endif

#if NUB_LOG_LEVEL >= NUB_LOG_LEVEL_WARN
#define NUB_WARN(message) log_message(NUB_LOG_LEVEL_WARN, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define NUB_WARN(...)
#endif

#if NUB_LOG_LEVEL >= NUB_LOG_LEVEL_INFO
#define NUB_INFO(message) log_message(NUB_LOG_LEVEL_INFO, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define NUB_INFO(...)
#endif

#if NUB_LOG_LEVEL >= NUB_LOG_LEVEL_SUCCESS
#define NUB_SUCCESS(message) log_message(NUB_LOG_LEVEL_SUCCESS, message, _DEBUG_SOURCE, __FILENAME__, __LINE__)
#else
#define NUB_SUCCESS(...)
#endif

#define NUB_CHECK(x, message) \
	if(!x){ \
		SPARKY_FATAL(message); \
		