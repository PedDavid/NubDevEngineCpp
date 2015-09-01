#pragma once

#include "..\utils\Log.h"
#include "..\maths\maths.h"

#include "..\..\ext\freetype-gl\freetype-gl.h"


namespace engine{
	namespace graphics{

		class Font{

		private:
			ftgl::texture_atlas_t *m_FTAtlas;
			ftgl::texture_font_t *m_FTFont;

			maths::vec2 m_Scale;
			unsigned int m_Size;

			std::string m_Name;
			std::string m_FilePath;

		public:
			Font(std::string name, std::string filepath, int size = 32);

			void setScale(float x, float y);

			inline ftgl::texture_font_t* getFTFont() const{ return m_FTFont; }

			inline const unsigned int getID() const { return m_FTAtlas->id; }

			inline const maths::vec2 &getScale() const { return m_Scale; }
			inline const int getSize() const { return m_Size; }

			inline const std::string &getName() const { return m_Name; }
			inline const std::string &getPath() const { return m_FilePath; }

		};

	}
}