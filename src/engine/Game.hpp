#pragma once
#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "common\utility\GameTime.hpp" // For representing timing information of the game loop

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

		////////////////////////////////////////////////////////////////
		// Options													  //
		////////////////////////////////////////////////////////////////

		// Toggles bounding box rendering
		void ToggleBoundingBoxRendering(bool enabled);

	private:

		// Whether or not the game is still running
		bool m_Running;

		// Desired duration between updates
		long m_FrameDurationMicros;

		// Holds timing information, passed on update and draw calls
		GameTime m_GameTime;

		// Executes the game loop in fixed framerate mode
		void RunFixedFramerate();

		// Executes the game loop in variable framerate mode
		void RunVariableFramerate();

		// Updates the game world
		void Update(const GameTime& gameTime);

		// Draws the game world
		void Draw(const GameTime& gameTime);

		// Whether or not to render object bounding boxes
		bool m_RenderBoundingBoxes = false;

	};
}

#endif