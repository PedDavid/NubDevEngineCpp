#pragma once

#include "../../utils/NubDevEngineGL.h"

#include <vector>
#include "../../maths/maths.h"

namespace engine{
	namespace graphics{

		class VBO{

		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;

		public:
			VBO(GLfloat *data, GLsizei count, GLuint componentCount);
			VBO(std::vector<maths::vec3> *data);
			VBO(std::vector<maths::vec4> *data);
			~VBO();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const{	return m_ComponentCount;	}

		};

	}
}