#pragma once

#include <GL/glew.h>

namespace engine{
	namespace graphics{

		class VBO{

		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;

		public:
			VBO(GLfloat *data, GLsizei count, GLuint componentCount);
			~VBO();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const{ 
				return m_ComponentCount; 
			}

		};

	}
}