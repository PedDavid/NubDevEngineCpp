#include "window.h"

namespace engine{
	namespace graphics{

		Window::Window(const char *name, int width, int height){
			m_Name = name;
			m_Width = width;
			m_Height = height;
			if (!init()){
				glfwTerminate();
			}
		}

		Window::~Window(){
			glfwTerminate();
			FontManager::clean();
			audio::SoundManager::clean();
		}

		bool Window::init(){
			if (!glfwInit()){
				std::cout << "[GLFW] Init ERROR" << std::endl;
				return false;
			}
			glfwWindowHint(GLFW_SAMPLES, 4);
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
			if (!m_Window){
				std::cout << "[GLFW] Window creation ERROR" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			std::cout << "[GLFW] Init Success" << std::endl;

			if (glewInit() != GLEW_OK){
				std::cout << "[GLEW] Init ERROR" << std::endl;
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::cout << "[GLEW] Init success" << std::endl;
			std::cout << "[OpenGL] v" << glGetString(GL_VERSION) << std::endl;
			std::cout << "[GLSL] v" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

			FontManager::init();
			audio::SoundManager::init();

			return true;
		}

		void Window::clear() const{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() const{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR){
				std::cout << "OpenGL Error: " << error << std::endl;
			}
			glfwPollEvents();
			glfwSwapBuffers(m_Window);

			audio::SoundManager::update();
		}

		bool Window::closed() const{
			return glfwWindowShouldClose(m_Window);
		}

		void window_resize(GLFWwindow *window, int width, int height){
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		bool Window::isKeyPressed(unsigned int key) const{
			if (key >= MAX_KEYS){
				std::cout << "Unasigned key with code " << key << std::endl;
				return false;
			}
			return m_Keys[key];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const{
			if (button >= MAX_BUTTONS){
				std::cout << "Unasigned key with code " << button << std::endl;
				return false;
			}
			return m_Buttons[button];
		}

		void Window::getMousePosition(double& x, double& y) const{
			x = mx;
			y = my;
		}

		void key_callback(GLFWwindow *window, int key, int scanmode, int action, int mods){
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Buttons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos){
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
	}
}