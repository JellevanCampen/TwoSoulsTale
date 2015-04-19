#include "AudioResource.hpp"

// Constructor; sets the sound source
Engine::AudioResource::AudioResource(irrklang::ISoundSource* soundSource)
{
	m_SoundSource = soundSource;
}

// Adds a sound to the playing queue
void Engine::AudioResource::AddToPlayingSoundsQueue(irrklang::ISound* sound)
{
	m_PlayingSounds.push(sound);
}

// Cleans up the queue of playing sounds
void Engine::AudioResource::CleanPlayingSoundsQueue()
{
	bool isFinished = true;

	// Check the elements in old-to-new other for whether they have finished playing
	while ((m_PlayingSounds.size() > 0) && isFinished)
	{
		isFinished = m_PlayingSounds.front()->isFinished();
		if (isFinished)
		{
			m_PlayingSounds.pop();
		}
	}
}