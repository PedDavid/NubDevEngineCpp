#pragma once

#include "../utils/Log.h"

#include <iostream>
#include <vector>

#include "font.h"

namespace engine{
	namespace graphics{

		class FontManager{

		private:
			static std::vector<Font*> m_Fonts;
			static Font *m_Font;

		public:
			static void init();
			static void add(Font *font);
			static Font *getDefault();
			static Font *get();
			static Font *get(const std::string &name, int size = 0);
			static void set(const std::string &name, int size = 0);
			static void setDefault();
			static void clean();
		
		private:
			FontManager();

		};

	}
}