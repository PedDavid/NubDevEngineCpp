#pragma once

#include "window\window.h"
#include "utils\timer.h"

namespace engine{

	class NubDevEngine{

	private:
		graphics::Window* m_Window;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;

	protected:
		NubDevEngine() : m_FramesPerSecond(0), m_UpdatesPerSecond(0) {

		}

		virtual ~NubDevEngine(){
			delete m_Window;
		}

		graphics::Window* createWindow(const char *name, int width, int height){
			m_Window = new graphics::Window(name, width, height);
			return m_Window;
		}


		void start(){
			init();
			run();
		}

		// Runs once upon initialization
		virtual void init() = 0;
		// Runs once per second
		virtual void tick() { }
		// Runs a set amount of times per second
		virtual void update() { }
		// Runs as fast as possible(unless the frame rate is capped)
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }

	private:
		void run(){

			Timer timer;

			float updateTime = 0.0f;
			float tickTime = 0.0f;

			float updateBrake = 1.0f / 60.0f;
			float tickBrake = 1.0f;

			unsigned int frames;
			unsigned int updates;

			while (!m_Window->closed()){
				m_Window->clear();

				if ((timer.elapsed() - updateTime) > updateBrake){
					updateTime += updateBrake;
					updates++;
					update();
				}
				
				render();
				frames++;
				m_Window->update();

				if ((timer.elapsed() - tickTime) > tickBrake){
					tickTime += tickBrake;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}

	};

}