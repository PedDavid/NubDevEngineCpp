#include "vao.h"

namespace engine{
	namespace graphics{

		VAO::VAO(){
			GlCheck(glGenVertexArrays(1, &m_ArrayID));
		}

		VAO::~VAO(){
			for (int i = 0; i < m_Buffers.size(); i++){
				delete m_Buffers[i];
			}
			GlCheck(glDeleteVertexArrays(1, &m_ArrayID));
		}

		void VAO::addBuffer(VBO *buffer, GLuint index){
			bind();
			buffer->bind();

			GlCheck(glEnableVertexAttribArray(index));
			GlCheck(glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0));

			buffer->unbind();
			unbind();

			m_Buffers.push_back(buffer);
		}

		void VAO::bind() const{
			GlCheck(glBindVertexArray(m_ArrayID));
		}

		void VAO::unbind() const{
			GlCheck(glBindVertexArray(0));
		}

	}
}