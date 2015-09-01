#pragma once

#include "../../utils/NubDevEngineGL.h"

#include <vector>

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

			void addBuffer(VBO *buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};

	}
}