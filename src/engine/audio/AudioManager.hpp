#pragma once
#ifndef ENGINE_AUDIO_AUDIOMANAGER_H
#define ENGINE_AUDIO_AUDIOMANAGER_H

#include <irrKlang.h> // irrKlang for playing audio samples
#include "../common/patterns/Singleton.hpp" // Singleton pattern

namespace Engine{
	class AudioManager : public Singleton<AudioManager>{

	public:

		// Initializes irrKlang
		void Initialize();

		// Terminates irrKlang
		void Terminate();

	private:

		// The irrKlang audio engine
		irrklang::ISoundEngine* m_SoundEngine;

	};
}

#endif