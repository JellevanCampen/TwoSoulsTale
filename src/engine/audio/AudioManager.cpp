#include "AudioManager.hpp"

// Initializes irrKlang
void Engine::AudioManager::Initialize()
{
	m_AudioResourcePath = "../../resources/audio/";

	// Initialize the irrKlang sound engine
	m_SoundEngine = irrklang::createIrrKlangDevice();
}

// Terminates irrKlang
void Engine::AudioManager::Terminate()
{
	// Terminate the irrKlang sound engine
	m_SoundEngine->drop();
}

// Loads an audio resource from the audio resource directory
Engine::AudioResource* Engine::AudioManager::LoadAudioResource(std::string filename)
{
	irrklang::ISoundSource* soundSource = m_SoundEngine->addSoundSourceFromFile((m_AudioResourcePath + filename).c_str());
	return new AudioResource(soundSource);
}

// Unloads an audio resource
void Engine::AudioManager::UnloadAudioResource(AudioResource* audioResource)
{
	delete audioResource;
}

// Plays a sound
void Engine::AudioManager::Play(AudioResource* audioResource)
{
	irrklang::ISound* sound = m_SoundEngine->play2D(audioResource->m_SoundSource, false, false, true, true);
	audioResource->AddToPlayingSoundsQueue(sound);
}