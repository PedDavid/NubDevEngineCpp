#pragma once

#include <vector>
#include <GL/glew.h>

#include "vbo.h"

namespace engine{
	namespace graphics{

		class VAO{

		private:
			GLuint m_ArrayID;
			std::vector<VBO*> m_Buffers;

		public:
			VAO();
			~VAO();

			void addBuffers(VBO *buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};

	}
}