#pragma once
#ifndef ENGINE_AUDIO_AUDIORESOURCE_H
#define ENGINE_AUDIO_AUDIORESOURCE_H

#include <irrKlang.h> // irrKlang for representing audio sources
#include <string> // For representing filenames
#include <queue> // For storing all playing sounds from this resource

namespace Engine
{
	class AudioManager;

	class AudioResource
	{

	public:

		// Constructor; sets the sound source
		AudioResource(irrklang::ISoundSource* soundSource);

	private:

		// irrKlang sound source associated with this audio resource
		irrklang::ISoundSource* m_SoundSource;

		// Currently playing sounds of this audio resource
		std::queue<irrklang::ISound*> m_PlayingSounds;

		// Adds a sound to the playing queue
		void AddToPlayingSoundsQueue(irrklang::ISound* sound);

		// Cleans up the queue of playing sounds
		void CleanPlayingSoundsQueue();

	public:

		friend class AudioManager;

	};
}

#endif

