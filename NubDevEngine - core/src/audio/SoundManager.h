#pragma once

#include <vector>

#include "sound.h"

namespace engine{
	namespace audio{

		class SoundManager{

		private:
			friend class Sound;

			static std::vector<Sound*> m_Sounds;

			static gau_Manager *m_Mgr;
			static ga_Mixer *m_Mixer;

		public:
			static void init();
			static void add(Sound *sound);
			static Sound *get(const std::string &name);
			static void update();
			static void clean();

		private:
			SoundManager(){	}

		};

	}
}