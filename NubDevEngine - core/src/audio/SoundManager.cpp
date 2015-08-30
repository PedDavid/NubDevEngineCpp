#include "SoundManager.h"

namespace engine{
	namespace audio{

		std::vector<Sound*> SoundManager::m_Sounds;

		gau_Manager *SoundManager::m_Mgr = nullptr;
		ga_Mixer *SoundManager::m_Mixer = nullptr;

		void SoundManager::init(){
			gc_initialize(0);
			m_Mgr = gau_manager_create();
			m_Mixer = gau_manager_mixer(m_Mgr);
			std::cout << "[SoundManager] Init Success" << std::endl;
		}

		void SoundManager::add(Sound *sound){
			m_Sounds.push_back(sound);
		}

		Sound *SoundManager::get(const std::string &name){
			for (Sound *sound : m_Sounds){
				if (sound->getName() == name){
					return sound;
				}
			}
			return nullptr;
		}

		void SoundManager::update(){
			gau_manager_update(m_Mgr);
		}

		void SoundManager::clean(){
			for (int i = 0; i < m_Sounds.size(); i++){
				delete m_Sounds[i];
			}
			gau_manager_destroy(m_Mgr);
			gc_shutdown();
			std::cout << "[SoundManager] Closed" << std::endl;
		}

	}
}