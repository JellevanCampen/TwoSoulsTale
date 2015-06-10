#pragma once
#ifndef ENGINE_WORLD_WORLDMANAGER_H
#define ENGINE_WORLD_WORLDMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "GameObject.hpp" // For representing game objects
#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop

#include <unordered_map> // For holding the game objects in the game world
#include <list> // For holding the game objects that are marked for removal

namespace Engine{

	class GameObjectHandle
	{

	public:

		// Constructor
		GameObjectHandle(unsigned int handle) { m_Handle = handle; }

		// Gets the handle to the game object
		unsigned int GetHandle()
		{
			return m_Handle;
		}

	private:

		// Handle to the gameobject
		unsigned int m_Handle;

	};

	class WorldManager : public Singleton<WorldManager>
	{

	public:

		// Initializes the game world
		void Initialize();

		// Destroys the game world
		void Terminate();

		// Updates all game objects in the game world
		void Update(const GameTime& gameTime);

		// Draws all game objects in the game world
		void Draw(const GameTime& gameTime);

		// Adds a game object to the world and returns the handle
		GameObjectHandle AddGameObject(GameObject* gameObject);

		// Removes a game object from the world 
		void RemoveGameObject(GameObjectHandle gameObjectHandle);

	private:

		// Incrementing counter for handles
		unsigned int m_Handles;

		// Data structure holding the game world
		std::unordered_map<unsigned int, GameObject*> m_GameObjects;

		// List of game objects that are marked to be removed
		std::list<GameObjectHandle> m_GameObjectRemoveList;

		// Removes all game objects that have been marked for removal
		void RemoveGameObjects();

	};
}

#endif