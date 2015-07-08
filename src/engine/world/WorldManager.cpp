#include "WorldManager.hpp"

#include "../graphics/GraphicsManager.hpp" // For rendering object bounding boxes
#include "../world/CollisionManager.hpp" // For querying objects by intersection

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

////////////////////////////////////////////////////////////////
// Game object creation and removal                           //
////////////////////////////////////////////////////////////////

// Adds a game object to the world and returns the handle
Engine::GameObjectGUID Engine::WorldManager::AddGameObject(GameObject* gameObject)
{
	// Initialize the object and add it to the game world
	gameObject->Create();
	m_GameObjects.insert(std::pair<GameObjectGUID, GameObject*>(gameObject->guid(), gameObject));
	AddToByTypeMap(gameObject);

	return gameObject->guid();
}

// Removes a game object from the world (based on its pointer)
void Engine::WorldManager::RemoveGameObject(GameObject* gameObject)
{
	m_GameObjectRemoveList.push_back(gameObject->guid());
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
		m_GameObjectRemoveList.push_back(gameObject->guid()); 
	}
}

// Removes a group of game objects from the world (based on their GUIDs)
void Engine::WorldManager::RemoveGameObject(std::vector<GameObjectGUID> gameObjectGUIDs)
{
	// Add the game object GUIDs to the remove list
	m_GameObjectRemoveList.insert(m_GameObjectRemoveList.end(), gameObjectGUIDs.begin(), gameObjectGUIDs.end());
}

////////////////////////////////////////////////////////////////
// Game object retrieval									  //
////////////////////////////////////////////////////////////////

// Retrieves all game objects
size_t Engine::WorldManager::RetrieveAll(GameObjectCollection& out_GameObjectCollection) const
{
	size_t count = 0;
	for (auto o : m_GameObjects) { out_GameObjectCollection.list().push_back(o.second); count++; }
	return count;
}

// Retrieves the game object that matches the specified GUID
size_t Engine::WorldManager::RetrieveByGUID(GameObjectGUID guid, GameObjectCollection& out_GameObjectCollection) const
{
	auto object = m_GameObjects.find(guid);
	if (object == m_GameObjects.end()) { return size_t(0); }
	out_GameObjectCollection.list().push_back(object->second);
	return size_t(1);
}

// Retrieves all game objects that matchs the specified type
size_t Engine::WorldManager::RetrieveByType(GameObjectType type, GameObjectCollection& out_GameObjectCollection) const
{
	if (type == OBJ_INVALID) { return size_t(0); }
	if (type == OBJ_ANY) { return RetrieveAll(out_GameObjectCollection); }

	size_t count = 0;
	auto objects = m_GameObjectsByType.find(type);
	if (objects == m_GameObjectsByType.end()) { return size_t(0); }
	for (auto o : objects->second) { out_GameObjectCollection.list().push_back(o); count++; }
	return count;
}

////////////////////////////////////////////////////////////////
// Position-based game object retrieval                       //
////////////////////////////////////////////////////////////////

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
			float distance = gameObject.second->t().xy().distance(position);
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
			float distance = gameObject->t2D().distance(position);
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
			float distance = gameObject.second->t().distance(position);
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
			float distance = gameObject->t().distance(position);
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
			gameObjectDistanceNew.m_Distance = gameObject.second->t2D().distance(position);

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
			gameObjectDistanceNew.m_Distance = gameObject->t2D().distance(position);

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
			gameObjectDistanceNew.m_Distance = gameObject.second->t().distance(position);

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
			gameObjectDistanceNew.m_Distance = gameObject->t().distance(position);

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
			if (gameObject.second->t2D().distance(position) <= maxDistance)
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
			if (gameObject->t2D().distance(position) <= maxDistance)
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
			if (gameObject.second->t().distance(position) <= maxDistance)
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
			if (gameObject->t().distance(position) <= maxDistance)
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
	Engine::colorRGBA c(0.8f, 0.2f, 0.2f, 1.0f);

	for (auto gameObject : m_GameObjects)
	{
		g.DrawRectangle(gameObject.second->aabb2D_world(), c);
	}
}

// Adds a GameObject to the by-type indexed map
void Engine::WorldManager::AddToByTypeMap(GameObject* gameObject)
{
	if (m_GameObjectsByType.count(gameObject->type()) == 0)
	{
		std::list<GameObject*> gameObjectList;
		gameObjectList.push_back(gameObject);
		m_GameObjectsByType.insert(std::pair<GameObjectType, std::list<GameObject*>>(gameObject->type(), gameObjectList));
	}
	else
	{
		m_GameObjectsByType.at(gameObject->type()).push_back(gameObject);
	}
}

// Removes a GameObject from the by-type indexed map
void Engine::WorldManager::RemoveFromByTypeMap(GameObject* gameObject)
{
	if (m_GameObjectsByType.count(gameObject->type()) != 0)
	{
		m_GameObjectsByType[gameObject->type()].remove(gameObject);
	}
}