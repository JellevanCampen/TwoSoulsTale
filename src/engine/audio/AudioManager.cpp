#include "AudioManager.hpp"

// Initializes irrKlang
void Engine::AudioManager::Initialize()
{
	// Initilize the irrKlang sound engine
	m_SoundEngine = irrklang::createIrrKlangDevice();
}

// Terminates irrKlang
void Engine::AudioManager::Terminate()
{
	// Terminate the irrKlang sound engine
	m_SoundEngine->drop();
}