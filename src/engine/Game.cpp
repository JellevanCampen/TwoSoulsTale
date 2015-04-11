#include "Game.hpp"

#include <chrono> // Chrono for measuring time between frames
#include <thread> // Thread to synchronize the execution of the game loop to the desired framerate

// Initializes all engine components in the correct order
void Engine::Game::Initialize()
{
	m_FrameDurationMicros = 1000000 / 60;

	LoggingManager::Create();
	LoggingManager::GetInstance().Initialize();
	GraphicsManager::Create();
	GraphicsManager::GetInstance().Initialize();
}

// Starts the game loop
void Engine::Game::Start()
{
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
	GraphicsManager::GetInstance().Terminate();
	GraphicsManager::Destroy();
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
	
}

// Draws the game world
void Engine::Game::Draw()
{
	GraphicsManager& mngrGraphics = GraphicsManager::GetInstance();

	// Repaint the screen by swapping the buffers of the main window
	mngrGraphics.SwapWindowBuffers();
}