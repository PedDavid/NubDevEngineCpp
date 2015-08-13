#include "ibo.h"

namespace engine{
	namespace graphics{

		IBO::IBO(GLuint *data, GLsizei count) 
			: m_Count(count){

			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			unbind();
		}

		IBO::~IBO(){
			glDeleteBuffers(1, &m_BufferID);
		}

		void IBO::bind() const{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IBO::unbind() const{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}