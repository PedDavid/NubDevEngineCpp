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
			Label(std::string text, float x, float y, Font *font = nullptr);
			Label(std::string text, float x, float y, const std::string &name, int size = 0);
			void submit(Renderer2D *renderer) const override;

		};

	}
}