#include "..\Config.h"

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

#define SPARKY_LOG_LEVEL_FATAL 0
#define SPARKY_LOG_LEVEL_ERROR 1
#define SPARKY_LOG_LEVEL_WARN  2
#define SPARKY_LOG_LEVEL_INFO  3




#ifndef SPARKY_LOG_LEVEL
#define SPARKY_LOG_LEVEL SPARKY_LOG_LEVEL_INFO
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_FATAL
#define SPARKY_FATAL(...) sparky::internal::log_message(SPARKY_LOG_LEVEL_FATAL, true, "SPARKY:    ", __VA_ARGS__)
#define _SPARKY_FATAL(...) sparky::internal::log_message(SPARKY_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define SPARKY_FATAL(...)
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_ERROR
#define SPARKY_ERROR(...) sparky::internal::log_message(SPARKY_LOG_LEVEL_ERROR, true, "SPARKY:    ", __VA_ARGS__)
#else
#define SPARKY_ERROR(...)
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_WARN
#define SPARKY_WARN(...) sparky::internal::log_message(SPARKY_LOG_LEVEL_WARN, true, "SPARKY:    ", __VA_ARGS__)
#else
#define SPARKY_WARN(...)
#endif

#if SPARKY_LOG_LEVEL >= SPARKY_LOG_LEVEL_INFO
#define SPARKY_INFO(...) sparky::internal::log_message(SPARKY_LOG_LEVEL_INFO, true, "SPARKY:    ", __VA_ARGS__)
#else
#define SPARKY_INFO(...)
#endif

#define NUB_LOG(x, ...) \
	if(!x) \
		SPARKY_FATAL(typeid(x).name(), __FILENAME__, __LINE__);