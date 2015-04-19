#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECT_H
#define ENGINE_WORLD_GAMEOBJECT_H

namespace Engine{
	class GameObject{

	public:

		// Creates the game object
		virtual void Create() { };

		// Destroys the game object
		virtual void Destroy() { };

		// Updates the game object
		virtual void Update() { };

		// Draws the game object
		virtual void Draw() { };

	};
}

#endif