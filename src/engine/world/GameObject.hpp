#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECT_H
#define ENGINE_WORLD_GAMEOBJECT_H

#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop

namespace Engine{
	class GameObject{

	public:

		// Creates the game object
		virtual void Create() { };

		// Destroys the game object
		virtual void Destroy() { };

		// Updates the game object
		virtual void Update(const GameTime& gameTime) { };

		// Draws the game object
		virtual void Draw(const GameTime& gameTime) { };

	};
}

#endif