#pragma once

#include "renderable2d.h"

namespace engine{
	namespace graphics{

		class Label : public Renderable2D{

		public:
			std::string text;

		public:
			Label(std::string text, float x, float y, maths::vec4 color);
			void submit(Renderer2D *renderer) const override;

		};

	}
}