#include "WorldManager.hpp"

#include "../graphics/GraphicsManager.hpp" // For rendering object bounding boxes

#include <limits> // For initializing to the largest possible float value in NN and kNN search
#include <list> // For storing the k nearest neighbors to a point (constant time random insertion)

// Initializes the game world
void Engine::WorldManager::Initialize()
{
	// Initialize the handles counter at zero
	m_Handles = 0;
}

// Destroys the game world
void Engine::WorldManager::Terminate()
{

}

// Updates all game objects in the game world
void Engine::WorldManager::Update(const GameTime& gameTime)
{
	for (std::pair<GameObjectGUID, GameObject*> gameObject : m_GameObjects)
	{
		gameObject.second->Update(gameTime);
	}

	// Remove objects that have been marked for removal
	RemoveMarkedGameObjects();
}

// Draws all game objects in the game world
void Engine::WorldManager::Draw(const GameTime& gameTime)
{
	for (std::pair<GameObjectGUID, GameObject*> gameObject : m_GameObjects)
	{
		gameObject.second->Draw(gameTime);
	}
}

// Adds a game object to the world and returns the handle
Engine::GameObjectGUID Engine::WorldManager::AddGameObject(GameObject* gameObject)
{
	// Initialize the object and add it to the game world
	gameObject->Create();
	m_GameObjects.insert(std::pair<GameObjectGUID, GameObject*>(gameObject->GetGUID(), gameObject));
	AddToByTypeMap(gameObject);

	return gameObject->GetGUID();
}

// Removes a game object from the world (based on its pointer)
void Engine::WorldManager::RemoveGameObject(GameObject* gameObject)
{
	m_GameObjectRemoveList.push_back(gameObject->GetGUID());
}

// Removes a game object from the world (based on its GUID)
void Engine::WorldManager::RemoveGameObject(GameObjectGUID gameObjectGUID)
{
	// Add the game object GUID to the remove list
	m_GameObjectRemoveList.push_back(gameObjectGUID);
}

// Removes a group of game objects from the world (based on their pointers)
void Engine::WorldManager::RemoveGameObject(std::vector<GameObject*> gameObjects)
{
	// Add the game object GUIDs to the remove list
	for (auto gameObject : gameObjects) 
	{ 
		m_GameObjectRemoveList.push_back(gameObject->GetGUID()); 
	}
}

// Removes a group of game objects from the world (based on their GUIDs)
void Engine::WorldManager::RemoveGameObject(std::vector<GameObjectGUID> gameObjectGUIDs)
{
	// Add the game object GUIDs to the remove list
	m_GameObjectRemoveList.insert(m_GameObjectRemoveList.end(), gameObjectGUIDs.begin(), gameObjectGUIDs.end());
}

////////////////////////////////////////////////////////////////
// Position-based game object retrieval                       //
////////////////////////////////////////////////////////////////

// Retrieves the game object with the specified GUID (returns whether the game object was found)
bool Engine::WorldManager::RetrieveGameObject(GameObjectGUID gameObjectGUID, GameObject*& out_GameObject)
{
	if (m_GameObjects.count(gameObjectGUID) == 0)
	{
		return false;
	}

	out_GameObject = m_GameObjects[gameObjectGUID];
	return true;
}

// Retrieves all game objects in the world (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveAllGameObjects(std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			out_GameObjects.push_back(gameObject.second);
			count++;
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			out_GameObjects.push_back(gameObject);
			count++;
		}
	}

	return count;
}

// Retrieves the nearest game object to the specified position considering x and y coordinates (returns whether a game object was found)
bool Engine::WorldManager::RetrieveNearestGameObject(f2 position, GameObject*& out_GameObject, GameObjectType typeFilter)
{
	// Linear search nearest neighbor
	// TODO: this is slow, accelerate this using a dedicated data structure
	// http://en.wikipedia.org/wiki/Nearest_neighbor_search

	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	float smallestDistance = std::numeric_limits<float>::max();
	GameObject* closestGameObject = NULL; 

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			float distance = gameObject.second->m_Transform.t().xy().GetDistanceTo(position);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				closestGameObject = gameObject.second;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			float distance = gameObject->m_Transform.t().xy().GetDistanceTo(position);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				closestGameObject = gameObject;
			}
		}
	}

	if (closestGameObject == NULL) { return false; }

	out_GameObject = closestGameObject;
	return true;
}

// Retrieves the nearest game object to the specified position considering x, y and z coordinates (returns whether a game object was found)
bool Engine::WorldManager::RetrieveNearestGameObject(f3 position, GameObject*& out_GameObject, GameObjectType typeFilter)
{
	// Linear search nearest neighbor
	// TODO: this is slow, accelerate this using a dedicated data structure
	// http://en.wikipedia.org/wiki/Nearest_neighbor_search

	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	float smallestDistance = std::numeric_limits<float>::max();
	GameObject* closestGameObject = NULL;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			float distance = gameObject.second->m_Transform.t().GetDistanceTo(position);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				closestGameObject = gameObject.second;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			float distance = gameObject->m_Transform.t().GetDistanceTo(position);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				closestGameObject = gameObject;
			}
		}
	}
	

	if (closestGameObject == NULL) { return false; }

	out_GameObject = closestGameObject;
	return true;
}

// Retrieves the k-nearest game object to the specified position considering x and y coordinates (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveKNearestGameObjects(f2 position, size_t k, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// Linear search nearest neighbor
	// TODO: this is slow, accelerate this using a dedicated data structure
	// TODO: replace naive kNN implementation (better to quicksort and pick top k?)

	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	struct GameObjectDistance
	{
		GameObject* m_GameObject;
		float m_Distance;
	};

	std::list<GameObjectDistance> nearestGameObjects;
	
	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			// Iteratively insert elements in the correct order (elements are sorted in large-to-small distance)
			GameObjectDistance gameObjectDistanceNew;
			gameObjectDistanceNew.m_GameObject = gameObject.second;
			gameObjectDistanceNew.m_Distance = gameObject.second->m_Transform.t().xy().GetDistanceTo(position);

			bool inserted = false;
			for (auto gameObjectDistanceIt = nearestGameObjects.begin(); gameObjectDistanceIt != nearestGameObjects.end(); gameObjectDistanceIt++)
			{
				if (gameObjectDistanceNew.m_Distance > gameObjectDistanceIt->m_Distance)
				{
					nearestGameObjects.insert(gameObjectDistanceIt, gameObjectDistanceNew);
					inserted = true;
					break;
				}
			}
			if (!inserted) { nearestGameObjects.push_back(gameObjectDistanceNew); }

			// Cap the list at k element
			if (nearestGameObjects.size() > k) { nearestGameObjects.pop_front(); }
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			// Iteratively insert elements in the correct order (elements are sorted in large-to-small distance)
			GameObjectDistance gameObjectDistanceNew;
			gameObjectDistanceNew.m_GameObject = gameObject;
			gameObjectDistanceNew.m_Distance = gameObject->m_Transform.t().xy().GetDistanceTo(position);

			bool inserted = false;
			for (auto gameObjectDistanceIt = nearestGameObjects.begin(); gameObjectDistanceIt != nearestGameObjects.end(); gameObjectDistanceIt++)
			{
				if (gameObjectDistanceNew.m_Distance > gameObjectDistanceIt->m_Distance)
				{
					nearestGameObjects.insert(gameObjectDistanceIt, gameObjectDistanceNew);
					inserted = true;
					break;
				}
			}
			if (!inserted) { nearestGameObjects.push_back(gameObjectDistanceNew); }

			// Cap the list at k element
			if (nearestGameObjects.size() > k) { nearestGameObjects.pop_front(); }
		}
	}

	// Copy over the top k elements
	for (auto gameObjectDistanceIt = nearestGameObjects.rbegin(); gameObjectDistanceIt != nearestGameObjects.rend(); gameObjectDistanceIt++)
	{
		out_GameObjects.push_back(gameObjectDistanceIt->m_GameObject);
	}

	return nearestGameObjects.size();
}

// Retrieves the k-nearest game object to the specified position considering x, y and z coordinates (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveKNearestGameObjects(f3 position, size_t k, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// Linear search nearest neighbor
	// TODO: this is slow, accelerate this using a dedicated data structure
	// TODO: replace naive kNN implementation (better to quicksort and pick top k?)

	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	struct GameObjectDistance
	{
		GameObject* m_GameObject;
		float m_Distance;
	};

	std::list<GameObjectDistance> nearestGameObjects;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			// Iteratively insert elements in the correct order (elements are sorted in large-to-small distance)
			GameObjectDistance gameObjectDistanceNew;
			gameObjectDistanceNew.m_GameObject = gameObject.second;
			gameObjectDistanceNew.m_Distance = gameObject.second->m_Transform.t().GetDistanceTo(position);

			bool inserted = false;
			for (auto gameObjectDistanceIt = nearestGameObjects.begin(); gameObjectDistanceIt != nearestGameObjects.end(); gameObjectDistanceIt++)
			{
				if (gameObjectDistanceNew.m_Distance > gameObjectDistanceIt->m_Distance)
				{
					nearestGameObjects.insert(gameObjectDistanceIt, gameObjectDistanceNew);
					inserted = true;
					break;
				}
			}
			if (!inserted) { nearestGameObjects.push_back(gameObjectDistanceNew); }

			// Cap the list at k element
			if (nearestGameObjects.size() > k) { nearestGameObjects.pop_front(); }
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			// Iteratively insert elements in the correct order (elements are sorted in large-to-small distance)
			GameObjectDistance gameObjectDistanceNew;
			gameObjectDistanceNew.m_GameObject = gameObject;
			gameObjectDistanceNew.m_Distance = gameObject->m_Transform.t().GetDistanceTo(position);

			bool inserted = false;
			for (auto gameObjectDistanceIt = nearestGameObjects.begin(); gameObjectDistanceIt != nearestGameObjects.end(); gameObjectDistanceIt++)
			{
				if (gameObjectDistanceNew.m_Distance > gameObjectDistanceIt->m_Distance)
				{
					nearestGameObjects.insert(gameObjectDistanceIt, gameObjectDistanceNew);
					inserted = true;
					break;
				}
			}
			if (!inserted) { nearestGameObjects.push_back(gameObjectDistanceNew); }

			// Cap the list at k element
			if (nearestGameObjects.size() > k) { nearestGameObjects.pop_front(); }
		}
	}

	// Copy over the top k elements
	for (auto gameObjectDistanceIt = nearestGameObjects.rbegin(); gameObjectDistanceIt != nearestGameObjects.rend(); gameObjectDistanceIt++)
	{
		out_GameObjects.push_back(gameObjectDistanceIt->m_GameObject);
	}

	return nearestGameObjects.size();
}

// Retrieves all game objects closer than the specified distance to a point considering x and y coordinates (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveGameObjectsNearPosition(f2 position, float maxDistance, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// TODO: this is slow, accelerate this using a dedicated data structure

	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			if (gameObject.second->m_Transform.t().xy().GetDistanceTo(position) <= maxDistance)
			{
				out_GameObjects.push_back(gameObject.second);
				count++;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			if (gameObject->m_Transform.t().xy().GetDistanceTo(position) <= maxDistance)
			{
				out_GameObjects.push_back(gameObject);
				count++;
			}
		}
	}
	
	return count;
}

// Retrieves all game objects closer than the specified distance to a point considering x, y and z coordinates(returns the number of game objects found)
size_t Engine::WorldManager::RetrieveGameObjectsNearPosition(f3 position, float maxDistance, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// TODO: this is slow, accelerate this using a dedicated data structure
	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			if (gameObject.second->m_Transform.t().GetDistanceTo(position) <= maxDistance)
			{
				out_GameObjects.push_back(gameObject.second);
				count++;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			if (gameObject->m_Transform.t().GetDistanceTo(position) <= maxDistance)
			{
				out_GameObjects.push_back(gameObject);
				count++;
			}
		}
	}

	return count;
}

// Retrieves all game objects whose origin falls within the specified 2D AABB (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveGameObjectsInAABB(aabb2Df aabb, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// TODO: this is slow, accelerate this using a dedicated data structure
	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			if (aabb.Contains(gameObject.second->m_Transform.t().xy()))
			{
				out_GameObjects.push_back(gameObject.second);
				count++;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			if (aabb.Contains(gameObject->m_Transform.t().xy()))
			{
				out_GameObjects.push_back(gameObject);
				count++;
			}
		}
	}

	return count;
}

// Retrieves all game objects whose origin falls within the specified 3D AABB (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveGameObjectsInAABB(aabb3Df aabb, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// TODO: this is slow, accelerate this using a dedicated data structure
	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			if (aabb.Contains(gameObject.second->m_Transform.t()))
			{
				out_GameObjects.push_back(gameObject.second);
				count++;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			if (aabb.Contains(gameObject->m_Transform.t()))
			{
				out_GameObjects.push_back(gameObject);
				count++;
			}
		}
	}

	return count;
}

////////////////////////////////////////////////////////////////
// Collision-based game object retrieval                      //
////////////////////////////////////////////////////////////////

// Retrieves all game objects whose AABBs overlap with the specified AABB and associated transform. Does not consider rotations (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveOverlappingAABBGameObjects2D(const aabb2Df& aabb, const transform2D& transform, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// TODO: this is slow, accelerate this using a dedicated data structure
	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	aabb2Df aabbTf = aabb.GetTransformed(transform);

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			if (aabbTf.OverlapsStrict(gameObject.second->m_AABB.GetTransformed(gameObject.second->m_Transform)))
			{
				out_GameObjects.push_back(gameObject.second);
				count++;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			if (aabbTf.OverlapsStrict(gameObject->m_AABB.GetTransformed(gameObject->m_Transform)))
			{
				out_GameObjects.push_back(gameObject);
				count++;
			}
		}
	}

	return count;
}

// Retrieves all game objects whose AABBs overlap with the specified AABB and associated transform. Does not consider rotations (returns the number of game objects found)
size_t Engine::WorldManager::RetrieveOverlappingAABBGameObjects3D(const aabb3Df& aabb, const transform3D& transform, std::vector<GameObject*>& out_GameObjects, GameObjectType typeFilter)
{
	// TODO: this is slow, accelerate this using a dedicated data structure
	if (typeFilter != OBJ_ANY && m_GameObjectsByType.count(typeFilter) == 0) { return size_t(0); }

	size_t count = 0;

	aabb3Df aabbTf = aabb.GetTransformed(transform);

	if (typeFilter == OBJ_ANY)
	{
		for (auto gameObject : m_GameObjects)
		{
			if (aabbTf.OverlapsStrict(gameObject.second->m_AABB.GetTransformed(gameObject.second->m_Transform)))
			{
				out_GameObjects.push_back(gameObject.second);
				count++;
			}
		}
	}
	else
	{
		for (auto gameObject : m_GameObjectsByType.at(typeFilter))
		{
			if (aabbTf.OverlapsStrict(gameObject->m_AABB.GetTransformed(gameObject->m_Transform)))
			{
				out_GameObjects.push_back(gameObject);
				count++;
			}
		}
	}

	return count;
}

// Removes all game objects that have been marked for removal
void Engine::WorldManager::RemoveMarkedGameObjects()
{
	for (GameObjectGUID gameObjectGUID : m_GameObjectRemoveList)
	{
		// Check if the game object still exists
		if (m_GameObjects.count(gameObjectGUID) == 0) { continue; }

		// Delete the game object and remove it from the game world
		RemoveFromByTypeMap(m_GameObjects[gameObjectGUID]);
		m_GameObjects[gameObjectGUID]->Destroy();
		delete m_GameObjects[gameObjectGUID];
		m_GameObjects.erase(gameObjectGUID);
	}

	m_GameObjectRemoveList.clear();
}

////////////////////////////////////////////////////////////////
// Debug rendering                                            //
////////////////////////////////////////////////////////////////

// Draws the bounding boxes of all game objects
void Engine::WorldManager::DrawBoundingBoxes() const
{
	Engine::GraphicsManager& g = Engine::GraphicsManager::GetInstance();
	Engine::f4 c(0.8f, 0.2f, 0.2f, 1.0f);

	for (auto gameObject : m_GameObjects)
	{
		g.DrawRectangle((rectanglef)gameObject.second->m_AABB.GetTransformed(gameObject.second->m_Transform), c);
	}
}

// Adds a GameObject to the by-type indexed map
void Engine::WorldManager::AddToByTypeMap(GameObject* gameObject)
{
	if (m_GameObjectsByType.count(gameObject->GetType()) == 0)
	{
		std::list<GameObject*> gameObjectList;
		gameObjectList.push_back(gameObject);
		m_GameObjectsByType.insert(std::pair<GameObjectType, std::list<GameObject*>>(gameObject->GetType(), gameObjectList));
	}
	else
	{
		m_GameObjectsByType.at(gameObject->GetType()).push_back(gameObject);
	}
}

// Removes a GameObject from the by-type indexed map
void Engine::WorldManager::RemoveFromByTypeMap(GameObject* gameObject)
{
	if (m_GameObjectsByType.count(gameObject->GetType()) != 0)
	{
		m_GameObjectsByType[gameObject->GetType()].remove(gameObject);
	}
}