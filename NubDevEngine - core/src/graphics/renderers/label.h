#pragma once

#include "renderable2d.h"

namespace engine{
	namespace graphics{

		class Label : public Renderable2D{

		public:
			Font *m_Font;
			std::string text;

		public:
			Label(std::string text, float x, float y, Font *font);
			void submit(Renderer2D *renderer) const override;

		};

	}
}