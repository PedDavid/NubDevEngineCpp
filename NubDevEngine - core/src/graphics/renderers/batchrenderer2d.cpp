#include "batchrenderer2d.h"

namespace engine{
	namespace graphics{

		BatchRenderer2D::BatchRenderer2D(){
			init();
		}

		BatchRenderer2D::~BatchRenderer2D(){
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::init(){
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, 10000, NULL, GL_DYNAMIC_DRAW);

			// NEEDS CHAGES IN VALUES  (10 000 and maybr const GLvoid* x)
			glEnableVertexAttribArray(0); //vertex index
			glEnableVertexAttribArray(1); //color index
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10000, (const GLvoid*) 0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10000, (const GLvoid*) (3 * sizeof(GLfloat)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);


			GLuint indices[10000];
			for (int i = 0, offset = 0; i < 10000; i += 6, offset += 4){
				indices[  i  ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;
			}

			m_IBO = new IBO(indices, 10000);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable){
			VertexData* buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			buffer->vertex = renderable->getPosition();
			buffer->color = renderable->getColor();
			buffer++;
		}

		void BatchRenderer2D::flush(){

		}


	}
}