#include "FontManager.h"

namespace engine{
	namespace graphics{

		std::vector <Font*> FontManager::m_Fonts;
		Font *FontManager::m_Font;

		void FontManager::init(){
			Font *font = new Font("default", "arial.ttf");
			add(font);
			m_Font = font;
			NUB_SUCCESS("[FontManager] INIT");
		}

		void FontManager::add(Font *font){
			m_Fonts.push_back(font);
		}

		Font *FontManager::getDefault(){
			return get("default", 32);
		}

		Font *FontManager::get(){
			return m_Font;
		}

		Font *FontManager::get(const std::string& name, int size){
			for (Font *font : m_Fonts){
				if ((size == 0 || font->getSize() == size) && font->getName() == name){
					return font;
				}
			}
			NUB_ERROR("[Font] " + name + (size > 0 ? " size " + std::to_string(size) : "") + " not found");

			return nullptr;
		}

		void FontManager::set(const std::string& name, int size){
			Font *font = get(name, size);
			m_Font = font ? font : m_Fonts.front();
		}

		void FontManager::setDefault(){
			m_Font = m_Fonts.front();
		}

		void FontManager::clean(){
			for (Font *font : m_Fonts){
				delete font;
			}
			NUB_SUCCESS("[FontManager] CLOSED");
		}
	}
}