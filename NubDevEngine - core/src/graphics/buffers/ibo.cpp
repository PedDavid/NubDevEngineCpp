#include "ibo.h"

namespace engine{
	namespace graphics{

		IBO::IBO(GLuint *data, GLsizei count) 
			: m_Count(count){

			GlCheck(glGenBuffers(1, &m_BufferID));
			GlCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
			GlCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
			GlCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		IBO::~IBO(){
			GlCheck(glDeleteBuffers(1, &m_BufferID));
		}

		void IBO::bind() const{
			GlCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
		}

		void IBO::unbind() const{
			GlCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

	}
}