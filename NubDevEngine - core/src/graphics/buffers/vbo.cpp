#include "vbo.h"

namespace engine{
	namespace graphics{


		VBO::VBO(GLfloat *data, GLsizei count, GLuint componentCount) 
			: m_ComponentCount(componentCount){

			GlCheck(glGenBuffers(1, &m_BufferID));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
			GlCheck(glBufferData(GL_ARRAY_BUFFER, count * componentCount * sizeof(GLfloat), data, GL_STATIC_DRAW));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		VBO::~VBO(){
			GlCheck(glDeleteBuffers(1, &m_BufferID));
		}

		void VBO::bind() const{
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
		}

		void VBO::unbind() const{
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}


	}
}