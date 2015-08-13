#include "vao.h"

namespace engine{
	namespace graphics{

		VAO::VAO(){
			glGenVertexArrays(1, &m_ArrayID);
		}

		VAO::~VAO(){
			for (int i = 0; i < m_Buffers.size(); i++){
				delete m_Buffers[i];
			}
			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VAO::addBuffers(VBO *buffer, GLuint index){
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();

			m_Buffers.push_back(buffer);
		}

		void VAO::bind() const{
			glBindVertexArray(m_ArrayID);
		}

		void VAO::unbind() const{
			glBindVertexArray(0);
		}

	}
}