#pragma once

#include "renderable2d.h"
#include "..\FontManager.h"

namespace engine{
	namespace graphics{

		class Label : public Renderable2D{

		public:
			Font *m_Font;
			std::string text;

		public:
			Label(std::string text, float x, float y, unsigned int color);
			Label(std::string text, float x, float y, Font *font = nullptr, unsigned int color = 0xffffffff);
			Label(std::string text, float x, float y, const std::string &name, int size = 0, unsigned int color = 0xffffffff);
			void submit(Renderer2D *renderer) const override;

		};

	}
}