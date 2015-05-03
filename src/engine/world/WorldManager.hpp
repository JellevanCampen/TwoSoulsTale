#pragma once
#ifndef ENGINE_WORLD_WORLDMANAGER_H
#define ENGINE_WORLD_WORLDMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "GameObject.hpp" // For representing game objects
#include <map> // For holding the game objects in the game world

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
		void Update();

		// Draws all game objects in the game world
		void Draw();

		// Adds a game object to the world and returns the handle
		GameObjectHandle AddGameObject(GameObject* gameObject);

		// Removes a game object from the world 
		void RemoveGameObject(GameObjectHandle gameObjectHandle);

	private:

		// Incrementing counter for handles
		unsigned int m_Handles;

		// Data structure holding the game world
		std::map<unsigned int, GameObject*> m_GameObjects;

	};
}

#endif