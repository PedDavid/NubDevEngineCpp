#include "NubDevEngineGL.h"

namespace engine {

	void _gl_check_error(const char *stmt, const char *file, int line){
		GLenum err(glGetError());

		while (err != GL_NO_ERROR){
			std::string error;

			switch (err){
				case GL_INVALID_ENUM:		error = "INVALID ENUM";			break;
				case GL_INVALID_VALUE:		error = "INVALID VALUE";		break;
				case GL_INVALID_OPERATION:	error = "INVALID OPERATION";	break;
				case GL_STACK_OVERFLOW:		error = "STACK OVERFLOW";		break;
				case GL_STACK_UNDERFLOW:	error = "STACK UNDEFLOW";		break;
				case GL_OUT_OF_MEMORY:		error = "OUT OF MEMORY";		break;
				case GL_CONTEXT_LOST:		error = "CONTEXT LOST";			break;
				case GL_TABLE_TOO_LARGE:	error = "TABLE TO LARGE";		break;
				case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID FRAMEBUFFER OPERATION"; break;
				default: error = std::to_string(err);
			}

			NUB_ERROR(std::string("[OpenGL] ") + error + " | Call: " + stmt + '\n' + 
				'\t' + "File: " + file + " | Line: " + std::to_string(line));
			err = glGetError();
		}
	}

}