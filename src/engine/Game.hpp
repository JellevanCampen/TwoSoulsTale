#pragma once
#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager

namespace Engine{
	class Game{

	public:

		// Initializes all engine components in the correct order
		void Initialize();

		// Starts the game loop
		void Start();

		// Stops the game loop
		void Stop();

		// Terminates all engine components in the correct order
		void Terminate();

	private:

		// Whether or not the game is still running
		bool m_Running;

		// Desired duration between updates
		long m_FrameDurationMicros;

		// Executes the game loop
		void Run();

		// Updates the game world
		void Update();

		// Draws the game world
		void Draw();

	};
}

#endif