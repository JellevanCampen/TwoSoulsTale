#include "Game.hpp"

#include "debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager
#include "input\InputManager.hpp" // [INPUT] Input Manager
#include "audio\AudioManager.hpp" // [AUDIO] Audio Manager
#include "world\WorldManager.hpp" // [WORLD] World Manager

#include <chrono> // Chrono for measuring time between frames
#include <thread> // Thread to synchronize the execution of the game loop to the desired framerate

// TESTING
#include "..\game\test\TestObject.hpp" // Test Object
// TESTING

// Initializes all engine components in the correct order
void Engine::Game::Initialize()
{
	m_FrameDurationMicros = 1000000 / 60;

	LoggingManager::Create();
	LoggingManager::GetInstance().Initialize();
	AudioManager::Create();
	AudioManager::GetInstance().Initialize();
	GraphicsManager::Create();
	GraphicsManager::GetInstance().Initialize();
	InputManager::Create();
	InputManager::GetInstance().Initialize();
	WorldManager::Create();
	WorldManager::GetInstance().Initialize();
}

// Starts the game loop
void Engine::Game::Start()
{
	// TESTING
	WorldManager::GetInstance().AddGameObject(new GameContent::TestObject());
	// TESTING

	m_Running = true;
	Run();
}

// Stops the game loop
void Engine::Game::Stop()
{
	m_Running = false;
}

// Terminates all engine components in the correct order
void Engine::Game::Terminate()
{
	WorldManager::GetInstance().Terminate();
	WorldManager::Destroy();
	InputManager::GetInstance().Terminate();
	InputManager::Destroy();
	GraphicsManager::GetInstance().Terminate();
	GraphicsManager::Destroy();
	AudioManager::GetInstance().Destroy();
	AudioManager::Destroy();
	LoggingManager::GetInstance().Terminate();
	LoggingManager::Destroy();
}

// Executes the game loop
void Engine::Game::Run()
{
	// Holds the desired duration between two updates
	std::chrono::microseconds frameDuration(m_FrameDurationMicros);

	// Holds the desired time point for the next update
	std::chrono::time_point<std::chrono::high_resolution_clock> nextUpdate;
	nextUpdate = std::chrono::high_resolution_clock::now();

	while (m_Running)
	{
		Update();
		Draw();

		nextUpdate += frameDuration;
		std::this_thread::sleep_until(nextUpdate);
	}
}

// Updates the game world
void Engine::Game::Update()
{
	// Check for input 
	InputManager::GetInstance().PollInputEvents(); // Launch event-based input callbacks
	InputManager::GetInstance().Update(); // Launch polling-based input calbacks

	// Update the game world
	WorldManager::GetInstance().Update();
}

// Draws the game world
void Engine::Game::Draw()
{
	// Draw the game world
	WorldManager::GetInstance().Update();

	// Repaint the screen by swapping the buffers of the main window
	GraphicsManager::GetInstance().SwapWindowBuffers();
}