#pragma once

#include <vector>

#include "../graphics/buffers/buffers.h"
#include "../maths/maths.h"
#include "../graphics/shader.h"
#include "Triangle.h"


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

				vao->addBuffer(new VBO(square_positions, 8, 3), SHADER_VERTEX_INDEX);
				vao->addBuffer(new VBO(square_colors, 8, 4), SHADER_COLOR_INDEX);

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

			Mesh(int i) {
				using namespace graphics;

				vao = new VAO;

				GLfloat square_positions[] = {
					0.0, sqrt(2.0f) / 2.0f, 0.0,
					-0.5, 0.0, -0.5,
					-0.5, 0.0, 0.5,
					0.5, 0.0, -0.5,
					0.5, 0.0, 0.5,
					0.0, -sqrt(2.0f) / 2.0f, 0.0
				};

				GLfloat square_colors[] = {
					1.0, 0.0, 0.0, 1.0,
					1.0, 1.0, 0.0, 1.0,
					1.0, 0.0, 1.0, 1.0,
					1.0, 1.0, 1.0, 1.0,
					0.0, 0.0, 1.0, 1.0,
					0.0, 1.0, 1.0, 1.0,
				};

				vao->addBuffer(new VBO(square_positions, 6, 3), SHADER_VERTEX_INDEX);
				vao->addBuffer(new VBO(square_colors, 6, 4), SHADER_COLOR_INDEX);

				vao->bind();

				GLuint cube_elements[] = {
					// front
					0, 1, 2,
					0, 2, 4,
					0, 4, 3,
					0, 3, 1,
					5, 2, 1,
					5, 4, 2,
					5, 3, 4,
					5, 1, 3
				};

				m_VerticesCount = 24;
				ibo = new IBO(cube_elements, m_VerticesCount);
				m_VaoID = vao->getID();

				vao->unbind();
			}

			Mesh(int i, int a) {
				using namespace graphics;

				vao = new VAO;

				GLfloat square_positions[] = {
					1.0, 0.0, 0.0,
					-1.0, 0.0, 0.0,
					0.0, sqrt(3), 0.0,
				};

				maths::vec3(1.0, 0.0, 0.0);

				//Triangle triangle = Triangle(maths::vec3(0.0, sqrt(3), 0.0), maths::vec3(1.0, 0.0, 0.0), maths::vec3(-1.0, 0.0, 0.0), 2);

				GLfloat square_colors[] = {
					1.0, 0.0, 0.0, 1.0,
					1.0, 1.0, 0.0, 1.0,
					1.0, 0.0, 1.0, 1.0,
				};

				vao->addBuffer(new VBO(square_positions, 3, 3), SHADER_VERTEX_INDEX);
				vao->addBuffer(new VBO(square_colors, 3, 4), SHADER_COLOR_INDEX);

				vao->bind();

				GLuint cube_elements[] = {
					// front
					0, 1, 2,
				};

				m_VerticesCount = 3;
				ibo = new IBO(cube_elements, m_VerticesCount);
				m_VaoID = vao->getID();

				vao->unbind();
			}

			Mesh(maths::vec3 v1, maths::vec3 v2, maths::vec3 v3, int tesselation) {
				using namespace graphics;

				vao = new VAO;

				GLfloat square_positions[] = {
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z
				};

				maths::vec4 color = maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f);
				//maths::vec4 color = maths::vec4(1.0f, 0.0f, 1.0f, 1.0f);

				GLfloat square_colors[] = {
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				vao->addBuffer(new VBO(square_positions, 3, 3), SHADER_VERTEX_INDEX);
				vao->addBuffer(new VBO(square_colors, 3, 4), SHADER_COLOR_INDEX);

				vao->bind();

				GLuint cube_elements[] = {
					// front
					0, 1, 2,
				};

				m_VerticesCount = 3;
				ibo = new IBO(cube_elements, m_VerticesCount);
				m_VaoID = vao->getID();

				vao->unbind();
			}

			Mesh(std::vector<maths::vec3> &positions, std::vector<GLuint> &indices)
				: m_VerticesCount(indices.size()) {
				using namespace graphics;

				std::vector<maths::vec4> colors;
				maths::vec4 pink = maths::vec4(1.0, 0.0, 1.0, 1.0);

				for (int i = 0; i < positions.size(); i++){
					colors.push_back(pink);
				}

				vao = new VAO;

				vao->addBuffer(new VBO(&positions[0].x, positions.size(), 3), SHADER_VERTEX_INDEX);
				vao->addBuffer(new VBO(&colors[0].x, positions.size(), 4), SHADER_COLOR_INDEX);

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