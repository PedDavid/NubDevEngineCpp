#include "label.h"

namespace engine{
	namespace graphics{

		Label::Label(std::string text, float x, float y, Font *font)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), maths::vec4(1, 1, 1, 1)),
			text(text){
			m_Font = font ? font : FontManager::getFont();
		}

		Label::Label(std::string text, float x, float y, const std::string &name, int size)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), maths::vec4(1, 1, 1, 1)),
			text(text){
			Font* font = FontManager::get(name, size);
			m_Font = font ? font : FontManager::getDefault();
		}

		void Label::submit(Renderer2D *renderer) const{
			renderer->drawString(text, m_Position, *m_Font);
		}

	}
}