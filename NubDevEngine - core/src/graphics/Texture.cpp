#include "Texture.h"

namespace engine{
	namespace graphics{

		Texture::Texture(const std::string &filePath) : m_FilePath(filePath){

			BYTE *pixels = loadImage(m_FilePath.c_str(), &m_Width, &m_Height, &m_Bits);

			GlCheck(glGenTextures(1, &m_TID));
			GlCheck(glBindTexture(GL_TEXTURE_2D, m_TID));
			GlCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GlCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			if (m_Bits == 32){
				GlCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels));
			}
			else{
				GlCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels));
			}
			GlCheck(glBindTexture(GL_TEXTURE_2D, 0));

			delete[] pixels;

			NUB_SUCCESS(std::string("[Texture] ID: ") + std::to_string(m_TID) + " | Path: " + m_FilePath + 
				" | W: " + std::to_string(m_Width) + " | H: " + std::to_string(m_Height) + " | BPP: " + std::to_string(m_Bits));
		}

		Texture::~Texture(){
			GlCheck(glDeleteTextures(1, &m_TID));
		}

		void Texture::bind() const{
			GlCheck(glBindTexture(GL_TEXTURE_2D, m_TID));
		}

		void Texture::unbind() const{
			GlCheck(glBindTexture(GL_TEXTURE_2D, 0));
		}

	}
}