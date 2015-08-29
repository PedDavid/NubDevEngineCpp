#include "FontManager.h"

namespace engine{
	namespace graphics{

		std::vector <Font*> FontManager::m_Fonts;
		Font *FontManager::m_Font;

		void FontManager::init(){
			Font *font = new Font("default", "arial.ttf", 32, 0xffff00ff);
			add(font);
			m_Font = font;
		}

		void FontManager::add(Font *font){
			m_Fonts.push_back(font);
		}

		Font *FontManager::getFont(){
			return m_Font;
		}

		Font *FontManager::get(const std::string& name, int size){
			for (Font *font : m_Fonts){
				if ((size == 0 || font->getSize() == size) && font->getName() == name){
					return font;
				}
			}
			std::cout << "[Font Error] Font " << name;
			if (size > 0)
				std::cout << " with size " << size;
			std::cout << " was not found!" << std::endl;

			setDefault();
			return m_Font;
		}

		void FontManager::set(const std::string& name, int size){
			m_Font = get(name, size);
		}

		void FontManager::setDefault(){
			m_Font = m_Fonts.front();
		}

		void FontManager::clean(){
			for (Font *font : m_Fonts){
				delete font;
			}
		}
		
	}
}