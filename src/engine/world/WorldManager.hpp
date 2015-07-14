#pragma once
#ifndef ENGINE_WORLD_WORLDMANAGER_H
#define ENGINE_WORLD_WORLDMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "GameObject.hpp" // For representing game objects
#include "GameObjectCollection.hpp" // For representing a collection of game objects
#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop
#include "../common/utility/VectorTypes.hpp" // For representing 2D and 3D positions
#include "../common/utility/ShapeTypes.hpp" // For representing shapes
#include "CollisionManager.hpp" // For collision checking

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

		// Adds a group of game objects to the world 
		void AddGameObjects(const GameObjectCollection& gameObjects);

		// Removes a game object from the world
		void RemoveGameObject(GameObject* gameObject);

		// Removes a group of game objects from the world
		void RemoveGameObjects(const GameObjectCollection& gameObjects);

		////////////////////////////////////////////////////////////////
		// Game object retrieval									  //
		////////////////////////////////////////////////////////////////

		// Retrieves all game objects
		size_t RetrieveAll(GameObjectCollection& out_GameObjectCollection) const;

		// Retrieves the game object that matches the specified GUID
		size_t RetrieveByGUID(GameObjectGUID guid, GameObjectCollection& out_GameObjectCollection) const;

		// Retrieves all game objects that matchs the specified type
		size_t RetrieveByType(GameObjectType type, GameObjectCollection& out_GameObjectCollection) const;

		///////////////////////////////////////////////////////// Legacy

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

		////////////////////////////////////////////////////////////////
		// Collision-aware movement		                              //
		////////////////////////////////////////////////////////////////

		// Possible responses on collisions
		enum class CollisionResponse
		{
			IGNORE,		// Ignore collisions
			STOP,		// Stop moving on collision
			SLIDE,		// Remove the motion component parallel to the collision normal (removes speed)
			REDIRECT,	// Redirects the motion to move perpendicular to the collision normal (does not remove speed, except for perpendicular collisions)
			REFLECT		// Reflects the object of the colliding surface (does not remove speed)
		};

	private:

		// Maximum number of iterations in movement solver
		static const unsigned char s_MaxMovementIterations;

		// Minimum separation distance to keep between objects
		//		NOTE: when a collision occurs, the moving object is pushed back out 
		//		of the colliding object by this distance. Placing objects next to 
		//		each other with a separation of 0 units is not compatible with the 
		//		ray-casting approach used for collision detection as an inter-distance 
		//		of 0 units is registered as a collision.
		static const float s_ObjectSeparationDistance;

		///////////////////////////////////////////////////////////// 2D

		// Pushes an object out of a colliding object along the motion vector
		template<typename valuetype>
		inline void PushOut2D(GameObject& gameObject, vector2D<valuetype> motion)
		{
			gameObject.t() -= (motion * s_ObjectSeparationDistance) / motion.length();
		}

		// Finds the nearest collision along a specified motion vector
		template<typename valuetype>
		inline bool FindFirstCollision2D(GameObject& gameObject, vector2D<valuetype> motion, const GameObjectCollection& other, vector2D<valuetype>& out_Position, vector2D<valuetype>& out_Normal, valuetype& out_Progression)
		{
			// Initialize to full motion (1.0 progression)
			out_Position = gameObject.t2D() + motion;
			out_Progression = 1.0f;

			vector2D<valuetype> currentPosition;
			vector2D<valuetype> currentNormal;
			valuetype currentProgression = 1.0f;

			bool collision = false;

			// Ray cast all other objects to find the nearest collision
			CollisionManager c = CollisionManager::GetInstance();

			for (GameObject* g : other.objects()) {
				if (gameObject.guid() == g->guid()) { continue; }
				if (c.IsIntersecting(gameObject.aabb2D_world(), g->aabb2D_world(), motion, currentPosition, currentNormal, currentProgression))
				{
					if (currentProgression < out_Progression)
					{
						out_Progression = currentProgression;
						out_Position = currentPosition;
						out_Normal = currentNormal;
						collision = true;
						if (currentProgression == 0.0f) { return true; }
					}
				}
			}

			return collision;
		}

		// Move a game object along the specified motion vector, ignoring collisions
		template<typename valuetype>
		inline void MoveIgnore2D(GameObject& gameObject, vector2D<valuetype> motion)
		{
			gameObject.t() += motion;
		}

		// Move a game object along the specified motion vector, stopping at the first collision
		template<typename valuetype>
		inline bool MoveStop2D(GameObject& gameObject, vector2D<valuetype> motion, const GameObjectCollection& other, bool updateVelocity)
		{
			vector2D<valuetype> position;
			vector2D<valuetype> normal;
			valuetype progression;

			// Move the object and push it out of colliding objects
			bool collision = FindFirstCollision2D(gameObject, motion, other, position, normal, progression);
			if (progression == 0.0f) { gameObject.velocity(f3(0.0)); return true; }
			gameObject.t() += motion * progression;
			if (collision) { PushOut2D(gameObject, motion); if (updateVelocity) { gameObject.velocity(f3(0.0)); } }
			
			return collision;
		}

		// Move a game object along the specified motion vector, sliding along colliding objects
		template<typename valuetype>
		inline bool MoveSlide2D(GameObject& gameObject, vector2D<valuetype> motion, const GameObjectCollection& other)
		{
			vector2D<valuetype> position;
			vector2D<valuetype> normal;
			valuetype progression;

			unsigned char iteration = 0;
			bool collision = false;

			do
			{
				// Move the object and push it out of colliding objects
				bool collisionCurrent = FindFirstCollision2D(gameObject, motion, other, position, normal, progression);
				if (progression == 0.0f) { return true; }
				gameObject.t() += motion * progression;
				collision |= collisionCurrent;
				if (!collisionCurrent) {  return collision; }
				PushOut2D(gameObject, motion);

				// Calculate the new motion vector to have sliding behavior
				motion = motion * (1.0f - progression);
				motion = motion - motion.project(normal);
				iteration++;

			} while (iteration < s_MaxMovementIterations);

			return collision;
		}

		// Move a game object along the specified motion vector, redirecting motion along colliding objects
		template<typename valuetype>
		inline bool MoveRedirect2D(GameObject& gameObject, vector2D<valuetype> motion, const GameObjectCollection& other, bool updateVelocity)
		{
			vector2D<valuetype> position;
			vector2D<valuetype> normal;
			valuetype progression;

			unsigned char iteration = 0;
			bool collision = false;

			do
			{
				// Move the object and push it out of colliding objects
				bool collisionCurrent = FindFirstCollision2D(gameObject, motion, other, position, normal, progression);
				if (progression == 0.0f) { return true; }
				gameObject.t() += motion * progression;
				collision |= collisionCurrent;
				if (!collisionCurrent) { return collision; }
				PushOut2D(gameObject, motion);

				// Calculate the new motion vector to have redirecting behavior
				motion = motion * (1.0f - progression);
				vector2D<valuetype> direction = motion - motion.project(normal);
				motion = motion.align(direction);
				if (updateVelocity) { gameObject.velocity(gameObject.velocity2D().align(motion)); }
				iteration++;

			} while (iteration < s_MaxMovementIterations);

			return collision;
		}

		// Move a game object along the specified motion vector, reflecting of colliding objects
		template<typename valuetype>
		inline bool MoveReflect2D(GameObject& gameObject, vector2D<valuetype> motion, const GameObjectCollection& other, bool updateVelocity)
		{
			vector2D<valuetype> position;
			vector2D<valuetype> normal;
			valuetype progression;

			unsigned char iteration = 0;
			bool collision = false;

			do
			{
				// Move the object and push it out of colliding objects
				bool collisionCurrent = FindFirstCollision2D(gameObject, motion, other, position, normal, progression);
				if (progression == 0.0f) { return true; }
				gameObject.t() += motion * progression;
				collision |= collisionCurrent;
				if (!collisionCurrent) { return collision; }
				PushOut2D(gameObject, motion);

				// Calculate the new motion vector to have redirecting behavior
				motion = (motion.reflect(normal)) * (1.0f - progression);
				if (updateVelocity) { gameObject.velocity(gameObject.velocity2D().align(motion)); }
				iteration++;

			} while (iteration < s_MaxMovementIterations);

			return collision;
		}

	public:

		// Moves a game object along the specified motion vector, resolving collisions on the way
		template<typename valuetype>
		inline bool Move2D(GameObject& gameObject, vector2D<valuetype> motion, CollisionResponse response, const GameObjectCollection& other, bool updateVelocity = false)
		{
			// If collisions should be ignored, skip broadphase filtering
			if (response == CollisionResponse::IGNORE) { MoveIgnore2D(gameObject, motion); return false; }

			// Broadphase filtering based on AABB sweep
			CollisionManager& c(CollisionManager::GetInstance());
			aabb2D<valuetype> sweep(gameObject.aabb2D_world().sweep(motion));
			GameObjectCollection g(other);
			g.FilterByOverlap(sweep);

			// Move the object based on the specified collision response
			switch (response)
			{
			case CollisionResponse::STOP:
				return MoveStop2D(gameObject, motion, g, updateVelocity);
			case CollisionResponse::SLIDE:
				return MoveSlide2D(gameObject, motion, g);
			case CollisionResponse::REDIRECT:
				return MoveRedirect2D(gameObject, motion, g, updateVelocity);
			case CollisionResponse::REFLECT:
				return MoveReflect2D(gameObject, motion, g, updateVelocity);
			}
		}

		// Moves the game object based on its velocity, resolving collisions on the way
		template<typename valuetype>
		inline bool Move2D(GameObject& gameObject, valuetype deltaTimeSeconds, CollisionResponse response, const GameObjectCollection& other, bool updateVelocity = true)
		{
			// Calculate the motion vector from the velocity and delta time
			vector2D<valuetype> motion = gameObject.velocity2D() * deltaTimeSeconds;

			return Move2D(gameObject, motion, response, other, updateVelocity);
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