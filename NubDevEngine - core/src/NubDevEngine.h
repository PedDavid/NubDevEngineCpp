#pragma once

#include "window\window.h"

#include "graphics\layers\layer.h"
#include "graphics\layers\group.h"
#include "graphics\renderables\sprite.h"
#include "graphics\renderables\label.h"

#include "audio\SoundManager.h"

#include "maths\maths.h"

#include "utils\timer.h"

namespace engine{

	using namespace graphics;
	using namespace audio;
	using namespace maths;

	class NubDevEngine{

	private:
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
		std::vector<Window*> m_Windows;

	protected:
		NubDevEngine() : m_FramesPerSecond(0), m_UpdatesPerSecond(0) {

		}

		virtual ~NubDevEngine(){
			for (Window *m_Window : m_Windows){
				delete m_Window;
			}
		}

		Window *createWindow(const char *name, int width, int height){
			m_Windows.push_back(new Window(name, width, height));
			return m_Windows.back();
		}


	public:
		void start(){
			init_services();
			init();
			run();
			terminate();
		}

	protected:
		//Runs once upon initialization
		virtual void init() = 0;
		//Runs once per second
		virtual void tick() { }
		//Runs a set amount of times per second
		virtual void update() { }
		//Runs as fast as possible(unless the frame rate is capped)
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }

	private:
		void init_services(){
			FontManager::init();
			SoundManager::init();
		}

		void run(){

			Timer timer;

			float updateTime = 0.0f;
			float tickTime = 0.0f;

			float updateBrake = 1.0f / 60.0f;
			float tickBrake = 1.0f;

			unsigned int frames = 0;
			unsigned int updates = 0;

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
				SoundManager::update();

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

		void terminate(){
			FontManager::clean();
			SoundManager::clean();
		}

	};

}