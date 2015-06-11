#pragma once
#ifndef ENGINE_WORLD_WORLDMANAGER_H
#define ENGINE_WORLD_WORLDMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "GameObject.hpp" // For representing game objects
#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop
#include "../common/utility/VectorTypes.hpp" // For representing 2D and 3D positions
#include "../common/utility/IntervalTypes.hpp" // For representing 2D and 3D AABBs

#include <unordered_map> // For holding the game objects in the game world
#include <list> // For holding the game objects that are marked for removal
#include <vector> // For returning lists of game objects

namespace Engine{

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

		////////////////////////////////////////////////////////////////
		// Game object creation and removal                           //
		////////////////////////////////////////////////////////////////

		// Adds a game object to the world and returns the handle
		GameObjectGUID AddGameObject(GameObject* gameObject);

		// Removes a game object from the world (based on its GUID)
		void RemoveGameObject(GameObjectGUID gameObjectGUID);

		// Removes a group of game objects from the world (based on their pointers)
		void RemoveGameObject(std::vector<GameObject*> gameObjects);

		// Removes a group of game objects from the world (based on their GUIDs)
		void RemoveGameObject(std::vector<GameObjectGUID> gameObjectGUIDs);

		////////////////////////////////////////////////////////////////
		// Game object retrieval                                      //
		////////////////////////////////////////////////////////////////

		// Retrieves all game objects in the world (returns the number of game objects found)
		size_t RetrieveAllGameObjects(std::vector<GameObject*>& out_GameObjects);

		// Retrieves the game object with the specified GUID (returns whether the game object was found)
		bool RetrieveGameObject(GameObjectGUID gameObjectGUID, GameObject*& out_GameObject);

		// Retrieves the nearest game object to the specified position considering x and y coordinates (returns whether a game object was found)
		bool RetrieveNearestGameObject(f2 position, GameObject*& out_GameObject);

		// Retrieves the nearest game object to the specified position considering x, y and z coordinates (returns whether a game object was found)
		bool RetrieveNearestGameObject(f3 position, GameObject*& out_GameObject);

		// Retrieves the k-nearest game object to the specified position considering x and y coordinates (returns the number of game objects found)
		size_t RetrieveKNearestGameObjects(f2 position, size_t k, std::vector<GameObject*>& out_GameObjects);

		// Retrieves the k-nearest game object to the specified position considering x, y and z coordinates (returns the number of game objects found)
		size_t RetrieveKNearestGameObjects(f3 position, size_t k, std::vector<GameObject*>& out_GameObjects);

		// Retrieves all game objects closer than the specified distance to a point considering x and y coordinates (returns the number of game objects found)
		size_t RetrieveGameObjectsNearPosition(f2 position, float maxDistance, std::vector<GameObject*>& out_GameObjects);

		// Retrieves all game objects closer than the specified distance to a point considering x, y and z coordinates(returns the number of game objects found)
		size_t RetrieveGameObjectsNearPosition(f3 position, float maxDistance, std::vector<GameObject*>& out_GameObjects);

		// Retrieves all game objects whose origin falls within the specified 2D AABB (returns the number of game objects found)
		size_t RetrieveGameObjectsInAABB(aabb2Df aabb, std::vector<GameObject*>& out_GameObjects);

		// Retrieves all game objects whose origin falls within the specified 3D AABB (returns the number of game objects found)
		size_t RetrieveGameObjectsInAABB(aabb3Df aabb, std::vector<GameObject*>& out_GameObjects);

	private:

		// Incrementing counter for handles
		unsigned int m_Handles;

		// Data structure holding the game world
		std::unordered_map<GameObjectGUID, GameObject*> m_GameObjects;

		// List of game objects that are marked to be removed
		std::list<GameObjectGUID> m_GameObjectRemoveList;

		// Removes all game objects that have been marked for removal
		void RemoveMarkedGameObjects();

	};
}

#endif