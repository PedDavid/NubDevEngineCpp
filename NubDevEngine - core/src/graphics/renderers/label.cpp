#include "label.h"

namespace engine{
	namespace graphics{

		Label::Label(std::string text, float x, float y, maths::vec4 color)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), color), text(text){

		}

		void Label::submit(Renderer2D *renderer) const{
			renderer->drawString(text, m_Position, m_Color);
		}

	}
}