#include "WorldManager.hpp"

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
	for (std::pair<unsigned int, GameObject*> gameObject : m_GameObjects)
	{
		gameObject.second->Update(gameTime);
	}

	// Remove objects that have been marked for removal
	RemoveGameObjects();
}

// Draws all game objects in the game world
void Engine::WorldManager::Draw(const GameTime& gameTime)
{
	for (std::pair<unsigned int, GameObject*> gameObject : m_GameObjects)
	{
		gameObject.second->Draw(gameTime);
	}
}

// Adds a game object to the world and returns the handle
Engine::GameObjectHandle Engine::WorldManager::AddGameObject(GameObject* gameObject)
{
	// Generate a handle
	GameObjectHandle handle(m_Handles);
	m_Handles++;

	// Initialize the object and add it to the game world
	gameObject->Create();
	m_GameObjects.insert(std::pair<unsigned int, GameObject*>(handle.GetHandle(), gameObject));

	return handle;
}

// Removes a game object from the world 
void Engine::WorldManager::RemoveGameObject(GameObjectHandle gameObjectHandle)
{
	// Add the game object handle to the remove list
	m_GameObjectRemoveList.push_back(gameObjectHandle);
}

// Removes all game objects that have been marked for removal
void Engine::WorldManager::RemoveGameObjects()
{
	for (GameObjectHandle gameObjectHandle : m_GameObjectRemoveList)
	{
		// Delete the game object and remove it from the game world
		m_GameObjects.at(gameObjectHandle.GetHandle())->Destroy();
		delete m_GameObjects.at(gameObjectHandle.GetHandle());
		m_GameObjects.erase(gameObjectHandle.GetHandle());
	}
}