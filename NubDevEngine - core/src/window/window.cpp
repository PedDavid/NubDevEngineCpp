#include "window.h"

namespace engine{
	namespace graphics{

		Window::Window(const char *name, int width, int height, Window *window){
			m_Name = name;
			m_Width = width;
			m_Height = height;
			m_Window = window ? window->m_Window : nullptr;
			if (!window_init()){
				glfwTerminate();
			}
		}

		Window::~Window(){
			glfwTerminate();
		}

		bool Window::window_init(){
			if (!glfwInit()){
				NUB_FATAL("[GLFW] INIT");
				return false;
			}
			NUB_SUCCESS("[GLFW] INIT");
			glfwWindowHint(GLFW_SAMPLES, 4);
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, m_Window);
			if (!m_Window){
				NUB_FATAL("[GLFW] WINDOW CREATION");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			NUB_SUCCESS("[GLFW] Window creation");

			if (glewInit() != GLEW_OK){
				NUB_FATAL("[GLEW] INIT");
				return false;
			}

			GlCheck(glEnable(GL_BLEND));
			GlCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			GlCheck(glEnable(GL_DEPTH_TEST));

			NUB_SUCCESS("[GLEW] INIT");
			NUB_INFO(std::string("[OpenGL] v") + (char*)glGetString(GL_VERSION));
			NUB_INFO(std::string("[GLSL] v") + (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

			return true;
		}

		void Window::clear() const{
			GlCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		}

		void Window::update() const{
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		bool Window::closed() const{
			return glfwWindowShouldClose(m_Window);
		}

		void window_resize(GLFWwindow *window, int width, int height){
			GlCheck(glViewport(0, 0, width, height));
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		bool Window::isKeyPressed(unsigned int key) const{
			if (key >= MAX_KEYS){
				NUB_ERROR("[Keys] " + std::to_string(key) + " has no code assigned");
				return false;
			}
			return m_Keys[key];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const{
			if (button >= MAX_BUTTONS){
				NUB_ERROR("[Buttons] " + std::to_string(button) + " has no code assigned");
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