#include "Game.hpp"

#include "debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager
#include "input\InputManager.hpp" // [INPUT] Input Manager
#include "audio\AudioManager.hpp" // [AUDIO] Audio Manager
#include "timing\TimingManager.hpp" // [TIMING] Timing Manager
#include "world\WorldManager.hpp" // [WORLD] World Manager
#include "resources\ResourceManager.hpp" // [RESOURCES] Resource Manager

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
	TimingManager::Create();
	TimingManager::GetInstance().Initialize();
	WorldManager::Create();
	WorldManager::GetInstance().Initialize();
	ResourceManager::Create();
	ResourceManager::GetInstance().Initialize();
}

// Starts the game loop
void Engine::Game::Start()
{
	m_Running = true;
	// RunVariableFramerate();
	RunFixedFramerate();
}

// Stops the game loop
void Engine::Game::Stop()
{
	m_Running = false;
}

// Terminates all engine components in the correct order
void Engine::Game::Terminate()
{
	ResourceManager::GetInstance().Terminate();
	ResourceManager::Destroy();
	TimingManager::GetInstance().Terminate();
	TimingManager::Destroy();
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

////////////////////////////////////////////////////////////////
// Options													  //
////////////////////////////////////////////////////////////////

// Toggles bounding box rendering
void Engine::Game::ToggleBoundingBoxRendering(bool enabled)
{
	m_RenderBoundingBoxes = enabled;
}

// Executes the game loop in fixed framerate mode
void Engine::Game::RunFixedFramerate()
{
	// Holds the desired duration between two updates
	std::chrono::microseconds frameDuration(m_FrameDurationMicros);

	// Holds the desired time point for the next update
	std::chrono::time_point<std::chrono::high_resolution_clock> nextUpdate;
	nextUpdate = std::chrono::high_resolution_clock::now();

	// Reset the timing information
	m_GameTime.deltaTimeMicros = m_FrameDurationMicros;
	m_GameTime.frameCount = 0;
	m_GameTime.totalTimeMicros = 0;

	while (m_Running)
	{
		Update(m_GameTime);
		Draw(m_GameTime);

		// Update the timing information
		m_GameTime.frameCount++;
		m_GameTime.totalTimeMicros += m_FrameDurationMicros;

		// Schedule the next update
		nextUpdate += frameDuration;
		std::this_thread::sleep_until(nextUpdate);
	}
}

// Executes the game loop in variable framerate mode
void Engine::Game::RunVariableFramerate()
{
	// Timer for measuring delta times (in microseconds)
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime(std::chrono::high_resolution_clock::now());

	// Reset the timing information
	m_GameTime.deltaTimeMicros = 0;
	m_GameTime.frameCount = 0;
	m_GameTime.totalTimeMicros = 0;

	while (m_Running)
	{
		Update(m_GameTime);
		Draw(m_GameTime);

		// Update the timing information
		m_GameTime.deltaTimeMicros = (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - previousTime).count();
		m_GameTime.frameCount++;
		m_GameTime.totalTimeMicros += m_GameTime.deltaTimeMicros;
		previousTime = std::chrono::high_resolution_clock::now();
	}
}

// Updates the game world
void Engine::Game::Update(const GameTime& gameTime)
{
	// Check for input 
	TimingManager::GetInstance().Update(gameTime); // Update timing and launch time related callbacks
	InputManager::GetInstance().PollInputEvents(); // Launch event-based input callbacks
	InputManager::GetInstance().Update(gameTime); // Launch polling-based input calbacks

	// Update the game world
	WorldManager::GetInstance().Update(gameTime);
}

// Draws the game world
void Engine::Game::Draw(const GameTime& gameTime)
{
	// Draw the game world
	WorldManager::GetInstance().Draw(gameTime);

	// Draw object bounding boxes
	WorldManager::GetInstance().DrawBoundingBoxes();

	// Repaint the screen by swapping the buffers of the main window
	GraphicsManager::GetInstance().SwapWindowBuffers();
}