#pragma once

#include "../utils/NubDevEngineGL.h"

#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace engine{
	namespace graphics{

		class Shader{

		private:
			GLuint m_ShaderID;
			const char *m_VertPath;
			const char *m_FragPath;

		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			void setUniform1f(const GLchar *name, float value);
			void setUniform1fv(const GLchar *name, float *value, GLsizei size);
			void setUniform1i(const GLchar *name, int value);
			void setUniform1iv(const GLchar *name, int *value, GLsizei size);
			void setUniform2f(const GLchar *name, const maths::vec2& vector);
			void setUniform3f(const GLchar *name, const maths::vec3& vector);
			void setUniform4f(const GLchar *name, const maths::vec4& vector);
			void setUniformMat4(const GLchar* name, const maths::mat4 &matrix);

			void enable() const;
			void disable() const;

		private:
			GLuint load();
			GLuint load(const char *path, GLuint type);

			GLint getUniformLocation(const char *name);
		};

	}
}