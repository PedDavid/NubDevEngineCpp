#pragma once

#include <string>
#include "..\..\ext\freetype-gl\freetype-gl.h"

namespace engine{
	namespace graphics{

		class Font{

		private:
			ftgl::texture_atlas_t *m_FTAtlas;
			ftgl::texture_font_t *m_FTFont;

			unsigned int m_Size;
			unsigned int m_Color;

			std::string m_Name;
			std::string m_FilePath;

		public:
			Font(std::string name, std::string filepath, int size = 32, unsigned int color = 0xffffffff);

			void setColor(unsigned int color){ m_Color = color; }

			inline ftgl::texture_font_t* getFTFont() const{ return m_FTFont; }

			inline const unsigned int getID() const { return m_FTAtlas->id; }
			inline const int getSize() const { return m_Size; }
			inline const int getColor() const { return m_Color; }

			inline const std::string &getName() const { return m_Name; }
			inline const std::string &getPath() const { return m_FilePath; }

		};

	}
}