#pragma once

#include "..\utils\NubDevEngineGL.h"
#include "..\utils\Log.h"

#include <GLFW/glfw3.h>

#include "..\audio\SoundManager.h"
#include "..\graphics\FontManager.h"

namespace engine {
	namespace graphics{

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

		class Window{

		private:
			const char *m_Name;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_Buttons[MAX_BUTTONS];
			double mx = 0, my = 0;

		public:
			Window(const char *name, int width, int height, Window *window = nullptr);
			~Window();

			void clear() const;
			void update() const;
			bool closed() const;

			inline void setCurrent() const { glfwMakeContextCurrent(m_Window); }

			inline unsigned int getWidth() const { return m_Width; }
			inline unsigned int getHeight() const { return m_Height; }

			bool isKeyPressed(unsigned int key) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;

		private:
			bool window_init();

			friend void window_resize(GLFWwindow *window, int width, int height);

			friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}