#include "label.h"

namespace engine{
	namespace graphics{

		Label::Label(std::string text, float x, float y, unsigned int color)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), color), 
			text(text), m_Font(FontManager::getDefault())
		{
		}

		Label::Label(std::string text, float x, float y, Font *font, unsigned int color)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(1, 1), color), text(text){
			m_Font = font ? font : FontManager::getDefault();
		}

		Label::Label(std::string text, float x, float y, const std::string &name, int size, unsigned int color)
			: Label(text, x, y, FontManager::get(name, size), color){
		}

		void Label::submit(Renderer2D *renderer) const{
			renderer->drawString(text, m_Position, *m_Font, m_Color);
		}

	}
}