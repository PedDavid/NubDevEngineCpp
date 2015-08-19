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

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);		
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
			for (int i = 0, offset = 0; i < RENDERER_INDICES_SIZE; offset += 4){
				indices[i++] = offset + 0;
				indices[i++] = offset + 1;
				indices[i++] = offset + 2;

				indices[i++] = offset + 2;
				indices[i++] = offset + 3;
				indices[i++] = offset + 0;
			}

			m_IBO = new IBO(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::begin(){
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable){
			const maths::vec3& position = renderable->getPosition();
			const maths::vec2& size = renderable->getSize();
			const maths::vec4& color = renderable->getColor();

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int c = a<<24 | b << 16 | g << 8 | r;

			m_Buffer->vertex = position;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::vec3(position.x, position.y + size.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::vec3(position.x + size.x, position.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void BatchRenderer2D::end(){
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush(){
			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}


	}
}