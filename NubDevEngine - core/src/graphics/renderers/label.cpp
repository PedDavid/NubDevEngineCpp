#include "label.h"

namespace engine{
	namespace graphics{

		Label::Label(std::string text, float x, float y, Font *font)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), maths::vec4(1, 1, 1, 1)),
			text(text), m_Font(font) {

		}

		Label::Label(std::string text, float x, float y, const std::string &name, int size)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), maths::vec4(1, 1, 1, 1)),
			text(text), m_Font(FontManager::get(name, size)){

		}

		void Label::submit(Renderer2D *renderer) const{
			renderer->drawString(text, m_Position, *m_Font);
		}

	}
}