#include "vbo.h"

namespace engine{
	namespace graphics{


		VBO::VBO(GLfloat *data, GLsizei count, GLuint componentCount) 
			: m_ComponentCount(componentCount){

			GlCheck(glGenBuffers(1, &m_BufferID));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
			GlCheck(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		VBO::VBO(std::vector<maths::vec3> *data)
			: m_ComponentCount(3){
			GlCheck(glGenBuffers(1, &m_BufferID));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
			GlCheck(glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(maths::vec3), &data->front(), GL_STATIC_DRAW));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		VBO::VBO(std::vector<maths::vec4> *data)
			: m_ComponentCount(4){
			GlCheck(glGenBuffers(1, &m_BufferID));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
			GlCheck(glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(maths::vec4), &data->front(), GL_STATIC_DRAW));
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