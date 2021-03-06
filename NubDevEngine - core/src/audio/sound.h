#pragma once

#include <queue>

#include "../utils/Log.h"
#include "../utils/StringUtils.h"

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace engine{
	namespace audio{

		class Sound{

		private:
			std::string m_Name;
			std::string m_FilePath;

			ga_Sound* m_Sound;
			ga_Handle* m_Handle;

			float m_Gain;

		public:
			Sound(const std::string &name, const std::string &filePath);
			~Sound();

			void play();
			void loop();
			void resume();
			void pause();
			void stop();

			void setGain(float gain);

			inline float getGain() const { return m_Gain; }
			inline const std::string &getName() const { return m_Name; }
			inline const std::string &getFilePath() const { return m_FilePath; }

			friend void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
		};

	}
}