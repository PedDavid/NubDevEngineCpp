#pragma once

#include <cstddef>
#include "../renderables/renderable2d.h"

#include "../font.h"

namespace engine{
	namespace graphics{

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES 32

		class BatchRenderer2D : public Renderer2D{

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IBO *m_IBO;

			VertexData *m_Buffer;
			GLsizei m_IndexCount;

			std::vector<GLuint> m_TextureSlots;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D *renderable) override;
			void drawString(const std::string &text, const maths::vec3 &position, const Font &font, unsigned int color) override;
			void end() override;
			void flush() override;

		private:
			void init();

		};

	}
}