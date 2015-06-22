#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECT_H
#define ENGINE_WORLD_GAMEOBJECT_H

#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop
#include "../common/utility/TransformTypes.hpp" // For representing the transform of the GameObject
#include "../common/utility/IntervalTypes.hpp" // For representing AABBs

namespace Engine{

	// Typedef for game object globally unique IDs
	typedef unsigned long long GameObjectGUID;

	// Typedef for game object types
	typedef unsigned int GameObjectType;

	class GameObject{

	public:

		// Constructor (default)
		GameObject();

		// Constructor (with transform)
		GameObject(transform3D transform);

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

		// Gets the type of the game object
		virtual GameObjectType GetType() const = 0;
		
		// Transform of the game object
		transform3D m_Transform;

		// AABB of the game object (in local coordinates)
		aabb2Df m_AABB;

	private:

		// Globally unique ID of the game object
		const GameObjectGUID m_GUID;

		// Incrementing GUID counter
		static GameObjectGUID s_GUIDCounter;

	};
}

#endif