#include "SoundManager.h"

namespace engine{
	namespace audio{

		Sound::Sound(const std::string &name, const std::string &filePath)
			: m_Name(name), m_FilePath(filePath){

			std::vector<std::string> split = split_string(m_FilePath, '.');
			if (split.size() < 2)
			{
				NUB_ERROR("[Sound] Path: " + filePath + " is incorrect");
				return;
			}

			m_Sound = gau_load_sound_file(filePath.c_str(), split.back().c_str());

			if (!m_Sound){
				NUB_ERROR("[Sound] Load " + name + " | Path: " + filePath);
			}else{
				NUB_SUCCESS("[Sound] Load " + name + " | Path: " + filePath);
			}
		}

		Sound::~Sound(){
			ga_sound_release(m_Sound);
		}

		void Sound::play(){
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, 0, 0);
			ga_handle_play(m_Handle);
		}

		void Sound::loop(){
			gau_SampleSourceLoop* loopSrc;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, 0, 0, &loopSrc);
			ga_handle_play(m_Handle);
		}

		void Sound::resume(){
			ga_handle_play(m_Handle);
		}

		void Sound::pause(){
			ga_handle_stop(m_Handle);
		}

		void Sound::stop(){
			if (!ga_handle_playing(m_Handle)){
				NUB_WARN("[Sound] Can't Stop, no sound playing");
				return;
			}
			ga_handle_stop(m_Handle);
			ga_handle_destroy(m_Handle);
		}

		void Sound::setGain(float gain){
			if (!ga_handle_playing(m_Handle)){
				NUB_WARN("[Sound] Can't set Gain, no sound playing");
				return;
			}
			m_Gain = gain;
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Gain);
		}

		void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
		{
			ga_handle_destroy(in_handle);
		}
	}
}