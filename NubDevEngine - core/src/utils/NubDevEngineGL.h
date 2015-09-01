#pragma once

#include "..\Config.h"

#include <GL\glew.h>

#include "Log.h"

namespace engine{

	void _gl_check_error(const char *stmt, const char *file, int line);

}

#ifdef _GL_DEBUG

	#define GlCheck(stmt) \
		stmt; \
		_gl_check_error(#stmt, __FILENAME__, __LINE__);

#else

	#define GlCheck(stmt) stmt;

#endif