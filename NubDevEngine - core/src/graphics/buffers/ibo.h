#pragma once

#include "../../utils/NubDevEngineGL.h"

namespace engine{
	namespace graphics{

		class IBO{

		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IBO(GLuint *data, GLsizei count);
			~IBO();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const{	return m_Count;	}

		};

	}
}