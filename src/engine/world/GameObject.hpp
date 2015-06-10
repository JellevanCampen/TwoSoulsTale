#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECT_H
#define ENGINE_WORLD_GAMEOBJECT_H

#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop
#include "../common/utility/Transform3D.hpp" // For representing the transform of the GameObject

namespace Engine{

	// Typedef for game object globally unique IDs
	typedef unsigned long long GameObjectGUID;

	class GameObject{

	public:

		// Constructor (default)
		GameObject();

		// Constructor (with transform)
		GameObject(Transform3D transform);

		////////////////////////////////////////////////////////////////
		// Game loop functionality                                    //
		////////////////////////////////////////////////////////////////

		// Creates the game object
		virtual void Create() { };

		// Destroys the game object
		virtual void Destroy() { };

		// Updates the game object
		virtual void Update(const GameTime& gameTime) { };

		// Draws the game object
		virtual void Draw(const GameTime& gameTime) { };

		////////////////////////////////////////////////////////////////
		// Property setters and getters                               //
		////////////////////////////////////////////////////////////////

		// Gets the globally unique ID of the game object
		const GameObjectGUID& GetGUID() const;

		// Transform of the game object
		Transform3D m_Transform;

	private:

		// Globally unique ID of the game object
		const GameObjectGUID m_GUID;

		// Incrementing GUID counter
		static GameObjectGUID s_GUIDCounter;

	};
}

#endif