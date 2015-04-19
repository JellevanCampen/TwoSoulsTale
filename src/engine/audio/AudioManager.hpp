#pragma once
#ifndef ENGINE_AUDIO_AUDIOMANAGER_H
#define ENGINE_AUDIO_AUDIOMANAGER_H

#include "AudioResource.hpp" // For representing audio resources
#include <irrKlang.h> // irrKlang for playing audio samples
#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include <string> // For representing sound file names

namespace Engine{

	class AudioManager : public Singleton<AudioManager>
	{

	public:

		// Initializes irrKlang and sets the audio resource path
		void Initialize();

		// Terminates irrKlang
		void Terminate();

		// Loads an audio resource from the audio resource directory
		AudioResource* LoadAudioResource(std::string filename);

		// Unloads an audio resource
		void UnloadAudioResource(AudioResource* audioResource);

		// Plays a sound
		void Play(AudioResource* audioResource);

	private:

		// Path to the audio resources
		std::string m_AudioResourcePath;

		// The irrKlang audio engine
		irrklang::ISoundEngine* m_SoundEngine;

	};
}

#endif