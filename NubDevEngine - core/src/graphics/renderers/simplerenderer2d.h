#pragma once

#include <deque>

#include "renderer2d.h"

namespace engine{
	namespace graphics{

		class SimpleRenderer2D : public Renderer2D {

		private:
			std::deque<const Renderable2D*> m_RenderQueue;

		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;

		};
	}
}