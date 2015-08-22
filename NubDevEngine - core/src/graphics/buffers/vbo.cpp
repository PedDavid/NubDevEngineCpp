#include "vbo.h"

namespace engine{
	namespace graphics{


		VBO::VBO(GLfloat *data, GLsizei count, GLuint componentCount) 
			: m_ComponentCount(componentCount){

			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			unbind();
		}

		VBO::VBO(std::vector<maths::vec3> *data)
			: m_ComponentCount(3){
			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(maths::vec3), data, GL_STATIC_DRAW);
			unbind();
		}

		VBO::VBO(std::vector<maths::vec4> *data)
			: m_ComponentCount(4){
			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(maths::vec4), data, GL_STATIC_DRAW);
			unbind();
		}

		VBO::~VBO(){
			glDeleteBuffers(1, &m_BufferID);
		}

		void VBO::bind() const{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void VBO::unbind() const{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


	}
}