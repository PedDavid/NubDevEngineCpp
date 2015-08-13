#pragma once

#include "renderer2d.h"

namespace engine{
	namespace graphics{

		class BatchRenderer2D : public Renderer2D{

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IBO *m_IBO;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void submit(const Renderable2D *renderable) override;
			void flush() override;

		private:
			void init();

		};

	}
}