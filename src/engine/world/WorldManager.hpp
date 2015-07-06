#pragma once
#ifndef ENGINE_WORLD_WORLDMANAGER_H
#define ENGINE_WORLD_WORLDMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "GameObject.hpp" // For representing game objects
#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop
#include "../common/utility/VectorTypes.hpp" // For representing 2D and 3D positions
#include "../common/utility/ShapeTypes.hpp" // For representing shapes

#include <unordered_map> // For holding the game objects in the game world
#include <list> // For holding the game objects that are marked for removal, and for indexing game objects
#include <vector> // For returning lists of game objects

namespace Engine{

	// GameObject type for 
	static const GameObjectType OBJ_INVALID = GameObjectType(0);

	// GameObject type for filtering by "any object" (i.e. no filtering is applied)
	static const GameObjectType OBJ_ANY = GameObjectType(1);

	// First valid GameObjectType index (to reserve lower indices for special meanings)
	static const GameObjectType OBJ_OFFSET = GameObjectType(16);

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

		// Removes a game object from the world (based on its pointer)
		void RemoveGameObject(GameObject* gameObject);
		
		// Removes a game object from the world (based on its GUID)
		void RemoveGameObject(GameObjectGUID gameObjectGUID);

		// Removes a group of game objects from the world (based on their pointers)
		void RemoveGameObject(std::vector<GameObject*> gameObjects);

		// Removes a group of game objects from the world (based on their GUIDs)
		void RemoveGameObject(std::vector<GameObjectGUID> gameObjectGUIDs);

		////////////////////////////////////////////////////////////////
		// Position-based game object retrieval                       //
		////////////////////////////////////////////////////////////////

		// Retrieves the game object with the specified GUID (returns whether the game object was found)
		bool RetrieveGameObject(GameObjectGUID gameObjectGUID, GameObject*& out_GameObject);

		// Retrieves all game objects in the world (returns the number of game objects found)
		size_t RetrieveAllGameObjects(std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves the nearest game object to the specified position considering x and y coordinates (returns whether a game object was found)
		bool RetrieveNearestGameObject(f2 position, GameObject*& out_GameObject, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves the nearest game object to the specified position considering x, y and z coordinates (returns whether a game object was found)
		bool RetrieveNearestGameObject(f3 position, GameObject*& out_GameObject, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves the k-nearest game object to the specified position considering x and y coordinates (returns the number of game objects found)
		size_t RetrieveKNearestGameObjects(f2 position, size_t k, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves the k-nearest game object to the specified position considering x, y and z coordinates (returns the number of game objects found)
		size_t RetrieveKNearestGameObjects(f3 position, size_t k, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves all game objects closer than the specified distance to a point considering x and y coordinates (returns the number of game objects found)
		size_t RetrieveGameObjectsNearPosition(f2 position, float maxDistance, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves all game objects closer than the specified distance to a point considering x, y and z coordinates(returns the number of game objects found)
		size_t RetrieveGameObjectsNearPosition(f3 position, float maxDistance, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves all game objects whose origin falls within the specified 2D AABB (returns the number of game objects found)
		size_t RetrieveGameObjectsInAABB(aabb2Df aabb, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves all game objects whose origin falls within the specified 3D AABB (returns the number of game objects found)
		size_t RetrieveGameObjectsInAABB(aabb3Df aabb, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		////////////////////////////////////////////////////////////////
		// Collision-based game object retrieval                      //
		////////////////////////////////////////////////////////////////

		// Retrieves all game objects whose AABBs overlap with the specified AABB and associated transform. Does not consider rotations (returns the number of game objects found)
		size_t RetrieveOverlappingAABBGameObjects2D(const aabb2Df& aabb, const transform2D& transform, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves all game objects whose AABBs overlap with the specified game object's AABB. Does not consider rotations (returns the number of game objects found)
		inline size_t RetrieveOverlappingAABBGameObjects2D(const GameObject& gameObject, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY))
		{
			return RetrieveOverlappingAABBGameObjects2D((Engine::aabb2Df)gameObject.m_AABB, (Engine::transform2D)gameObject.m_Transform, out_GameObjects, typeFilter);
		}

		// Retrieves all game objects whose AABBs overlap with the specified AABB and associated transform. Does not consider rotations (returns the number of game objects found)
		size_t RetrieveOverlappingAABBGameObjects3D(const aabb3Df& aabb, const transform3D& transform, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY));

		// Retrieves all game objects whose AABBs overlap with the specified game object's AABB. Does not consider rotations (returns the number of game objects found)
		inline size_t RetrieveOverlappingAABBGameObjects3D(const GameObject& gameObject, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter = GameObjectType(Engine::OBJ_ANY))
		{
			return RetrieveOverlappingAABBGameObjects3D(gameObject.m_AABB, gameObject.m_Transform, out_GameObjects, typeFilter);
		}

		////////////////////////////////////////////////////////////////
		// Collision-aware movement		                              //
		////////////////////////////////////////////////////////////////

		// Possible responses on collisions
		enum class CollisionResponse
		{
			IGNORE,		// Ignore collisions
			STOP,		// Stop moving on collision
			SLIDE		// Remove the motion component parallel to the collision normal
		};

	private:

		///////////////////////////////////////////////////////////// 2D

		// Move a game object along the specified motion vector, ignoring collisions
		template<typename valuetype>
		inline void MoveIgnore(GameObject& gameObject, vector2D<valuetype> motion)
		{
			gameObject.m_Transform.t() += motion;
		}

		// Move a game object along the specified motion vector, stopping at the first collision
		template<typename valuetype>
		inline bool MoveStop(GameObject& gameObject, vector2D<valuetype> motion, const std::vector<GameObject*>& other)
		{
			valuetype minProgression = 1.0f;
			vector2D<valuetype> minPosition(gameObject.m_Transform.t() + motion);

			valuetype currentProgression = 1.0f;
			vector2D<valuetype> currentPosition;
			vector2D<valuetype> currentNormal;

			CollisionManager c = CollisionManager::GetInstance();

			for (GameObject* g : other) {
				if (gameObject.GetGUID() == g->GetGUID()) { continue; }
				if (c.IsIntersecting(gameObject.m_AABB, g->m_AABB, motion, currentPosition, currentNormal, currentProgression))
				{
					if (currentProgression < minProgression) 
					{
						minProgression = currentProgression;
						minPosition = currentPosition;
					}
				}
			}

			MoveIgnore(gameObject, motion * minProgression);
		}

		// Move a game object along the specified motion vector, sliding along colliding objects
		template<typename valuetype>
		inline bool MoveSlide(GameObject& gameObject, vector2D<valuetype> motion, const std::vector<GameObject*>& other)
		{
			// TODO
		}

	public:

		// Moves a game object along the specified motion vector, resolving collisions on the way
		template<typename valuetype>
		inline bool Move(GameObject& gameObject, vector2D<valuetype> motion, CollisionResponse response, const std::vector<GameObject*>& other)
		{
			switch (response)
			{
			case CollisionResponse::IGNORE:
				MoveIgnore(gameObject, motion); 
				return false;
			case CollisionResponse::STOP:
				return MoveStop(gameObject, motion);
				break;
			case CollisionResponse::SLIDE:
				return MoveSlide(gameObject, motion);
				break;
			}
		}

		////////////////////////////////////////////////////////////////
		// Debug rendering                                            //
		////////////////////////////////////////////////////////////////

		// Draws the bounding boxes of all game objects
		void DrawBoundingBoxes() const;

	private:

		// Incrementing counter for handles
		unsigned int m_Handles;

		// Data structure holding all GameObjects (mapped by GUID)
		std::unordered_map<GameObjectGUID, GameObject*> m_GameObjects;

		// Data structure holding all GameObjects (mapped by GameObjectType)
		std::unordered_map<GameObjectType, std::list<GameObject*>> m_GameObjectsByType;

		// Adds a GameObject to the by-type indexed map
		void AddToByTypeMap(GameObject* gameObject);

		// Removes a GameObject from the by-type indexed map
		void RemoveFromByTypeMap(GameObject* gameObject);

		// List of game objects that are marked to be removed
		std::list<GameObjectGUID> m_GameObjectRemoveList;

		// Removes all game objects that have been marked for removal
		void RemoveMarkedGameObjects();

	};
}

#endif