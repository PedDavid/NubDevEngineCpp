#pragma once

#include <vector>

#include "../graphics/buffers/buffers.h"
#include "../maths/maths.h"
#include "../graphics/shader.h"


namespace engine{
	namespace entities{

		class Mesh{

		private:
			GLuint m_VaoID;
			GLsizei m_VerticesCount;
			graphics::VAO *vao;
			graphics::IBO *ibo;

		public:
			Mesh() {
				using namespace graphics;

				vao = new VAO;

				GLfloat square_positions[] = {
					-0.5, -0.5, -0.5,
					0.5, -0.5, -0.5, 
					-0.5, 0.5, -0.5,
					0.5, 0.5, -0.5,
					0.5, 0.5, 0.5,
					-0.5, 0.5, 0.5,
					-0.5, -0.5, 0.5,
					0.5, -0.5, 0.5
				};

				GLfloat square_colors[] = {
					1.0, 0.0, 0.0, 1.0,
					1.0, 0.0, 0.0, 1.0,
					1.0, 0.0, 1.0, 1.0,
					1.0, 0.0, 1.0, 1.0,
					0.0, 0.0, 1.0, 1.0,
					0.0, 0.0, 1.0, 1.0,
					0.0, 1.0, 0.0, 1.0,
					0.0, 1.0, 0.0, 1.0
				};

				vao->addBuffer(new VBO(square_positions, 8 * 3, 3), SHADER_VERTEX_INDEX);
				vao->addBuffer(new VBO(square_colors, 8 * 4, 4), SHADER_COLOR_INDEX);

				vao->bind();

				GLuint cube_elements[] = {
					// front
					0, 1, 2,
					1, 2, 3,
					3, 2, 4,
					2, 4, 5,
					0, 2, 6,
					2, 5, 6,
					0, 1, 6,
					6, 5, 4,
					4, 1, 3,
					4, 1, 7,
					7, 6, 1,
					7, 4, 6
				};

				m_VerticesCount = 36;
				ibo = new IBO(cube_elements, m_VerticesCount);
				m_VaoID = vao->getID();

				vao->unbind();
			}

			Mesh(std::vector<maths::vec3> &positions, std::vector<GLuint> &indices)
				: m_VerticesCount (indices.size()) {
					using namespace graphics;

					vao = new VAO;

					vao->addBuffer(new VBO(&positions[0].x, positions.size() * 3, 3), SHADER_VERTEX_INDEX);

					vao->bind();

					ibo = new IBO(&indices.front(), m_VerticesCount);

					m_VaoID = vao->getID();
					vao->unbind();
			}

			inline graphics::IBO &getIBO(){ return *ibo; }
			inline GLuint getVaoID(){ return m_VaoID; }
			inline GLsizei getCount(){ return m_VerticesCount; }
		};

	}
}