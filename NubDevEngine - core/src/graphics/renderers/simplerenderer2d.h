#pragma once

#include <deque>

#include "renderer2d.h"
#include "staticsprite.h"

namespace engine{
	namespace graphics{

		class SimpleRenderer2D : public Renderer2D {

		private:
			std::deque<const StaticSprite*> m_RenderQueue;

		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;

		};
	}
}