#pragma once

#include "renderable2d.h"

namespace engine {
	namespace graphics {

		class StaticSprite : public Renderable2D{

		private:
			VAO* m_VertexArray;
			IBO* m_IndexBuffer;
			Shader& m_Shader;

		public:
			StaticSprite(float x, float y, float width, float height, const maths::vec4& color, Shader& shader);
			~StaticSprite();

			inline const VAO* getVAO() const { return m_VertexArray; }
			inline const IBO* getIBO() const { return m_IndexBuffer; }

			inline Shader& getShader() const { return m_Shader; }
		};

	}
}