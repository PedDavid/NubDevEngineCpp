#include "Texture.h"

namespace engine{
	namespace graphics{

		Texture::Texture(const std::string &filePath) 
			: m_FilePath(filePath){

			BYTE *pixels = loadImage(m_FilePath.c_str(), &m_Width, &m_Height);

			glGenTextures(1, &m_TID);
			glBindTexture(GL_TEXTURE_2D, m_TID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::~Texture(){
			glDeleteTextures(1, &m_TID);
		}

		void Texture::bind() const{
			glBindTexture(GL_TEXTURE_2D, m_TID);
		}

		void Texture::unbind() const{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
}