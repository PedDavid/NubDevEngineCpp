#include "shader.h"

namespace engine{
	namespace graphics{

			Shader::Shader(const char *vertPath, const char *fragPath) : 
				m_VertPath(vertPath), m_FragPath(fragPath)
			{
				m_ShaderID = load();
			}
			
			Shader::~Shader(){
				glDeleteProgram(m_ShaderID);
			}

			void Shader::enable() const{
				glUseProgram(m_ShaderID);
			}
			
			void Shader::disable() const{
				glUseProgram(0);
			}

			GLuint Shader::load(){
				GLuint programID = glCreateProgram();
				GLuint vertexID = load(m_VertPath, GL_VERTEX_SHADER);
				GLuint fragmentID = load(m_FragPath, GL_FRAGMENT_SHADER);
				glAttachShader(programID, vertexID);
				glAttachShader(programID, fragmentID);

				glLinkProgram(programID);
				glValidateProgram(programID);

				glDeleteShader(vertexID);
				glDeleteShader(fragmentID);

				return programID;
			}

			GLuint Shader::load(const char *path, GLuint type){
				GLuint shaderID = glCreateShader(type);
				std::string vertSourceString = read_file(path);
				const char *source = vertSourceString.c_str();
				glShaderSource(shaderID, 1, &source, NULL);
				glCompileShader(shaderID);

				GLint result;
				glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
				if (result == GL_FALSE){
					GLint length;
					glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(shaderID, length, &length, &error[0]);
					std::cout << &error[0] << std::endl;
					glDeleteShader(shaderID);
				}
				else{
					std::cout << "[Shader] ID: " << shaderID << " -> " << path << " -> Compilation Success" << std::endl;
				}
				return shaderID;
			}

			GLint Shader::getUniformLocation(const GLchar *name){
				return glGetUniformLocation(m_ShaderID, name);
			}

			void Shader::setUniform1f(const GLchar *name, float value){
				glUniform1f(getUniformLocation(name), value);
			}

			void Shader::setUniform1fv(const GLchar *name, float *value, GLsizei size){
				glUniform1fv(getUniformLocation(name), size, value);
			}

			void Shader::setUniform1i(const GLchar *name, int value){
				glUniform1i(getUniformLocation(name), value);
			}

			void Shader::setUniform1iv(const GLchar *name, int *value, GLsizei size){
				glUniform1iv(getUniformLocation(name), size, value);
			}

			void Shader::setUniform2f(const GLchar *name, const maths::vec2& vector){
				glUniform2f(getUniformLocation(name), vector.x, vector.y);
			}

			void Shader::setUniform3f(const GLchar *name, const maths::vec3& vector){
				glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
			}
			void Shader::setUniform4f(const GLchar *name, const maths::vec4& vector){
				glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
			}
			void Shader::setUniformMat4(const GLchar* name, const maths::mat4 &matrix){
				glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
			}

	}
}