#pragma once

#define _NUB_DEBUG
#define _GL_DEBUG

#if defined(_NUB_DEBUG) || defined(_GL_DEBUG)

	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#endif

typedef unsigned int uint;