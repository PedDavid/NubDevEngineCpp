#pragma once

#include "../buffers/buffers.h"
#include "../shader.h"

namespace engine {
	namespace graphics{

		struct VertexData{
			maths::vec3 vertex;
			maths::vec4 color;
		};

		class Renderable2D{

		protected:
			maths::vec3 m_Position;
			maths::vec2 m_Size;
			maths::vec4 m_Color;

			VAO* m_VertexArray;
			IBO* m_IndexBuffer;
			Shader& m_Shader;

		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader& shader)
				:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader){
				m_VertexArray = new VAO();

				GLfloat vertices[] = {
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				GLfloat colors[] = {
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				m_VertexArray->addBuffers(new VBO(vertices, 4 * 3, 3), 0);
				m_VertexArray->addBuffers(new VBO(vertices, 4 * 3, 3), 1);


				GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
				m_IndexBuffer = new IBO(indices, 6);
			}

			virtual ~Renderable2D(){
				delete m_VertexArray;
				delete m_IndexBuffer;
			}


			inline const VAO* getVAO() const{
				return m_VertexArray;
			}

			inline const IBO* getIBO() const{
				return m_IndexBuffer;
			}

			inline Shader& getShader() const{
				return m_Shader;
			}

			inline const maths::vec3& getPosition() const{
				return m_Position;
			}

			inline const maths::vec2& getSize() const{ 
				return m_Size; 
			}

			inline const maths::vec4& getColor() const{ 
				return m_Color;
			}

		};
	}
}