#include "GameObjectCollection.hpp"

#include "CollisionManager.hpp" // For checking collisions
#include <set> // For removing duplicate elements while merging game object collections

////////////////////////////////////////////////////////////////
// Collection manipulation									  //
////////////////////////////////////////////////////////////////

// Moves all elements of another game object collection to this one (removes elements from the other list)
Engine::GameObjectCollection& Engine::GameObjectCollection::merge(GameObjectCollection& other)
{
	// Filter out duplicate elements using a set
	for (GameObject* g : other.objects()) { m_GameObjects.insert(g); }
	return *this;
}

////////////////////////////////////////////////////////////////
// Filtering												  //
////////////////////////////////////////////////////////////////

// Filters out game objects that do not match the specified GUID
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByGUID(GameObjectGUID guid)
{
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if ((*i)->guid() == guid) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects that do not match the specified type
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByType(GameObjectType type)
{
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if ((*i)->type() == type) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects outside of the specified interval
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByLocation(const interval2Df& interval)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->t2D(), interval)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects outside of the specified interval
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByLocation(const interval3Df& interval)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->t(), interval)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects outside of the specified circle
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByLocation(const circlef& circle)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->t2D(), circle)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects outside of the specified sphere
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByLocation(const spheref& sphere)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->t(), sphere)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects that do not overlap with the specified interval
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByOverlap(const interval2Df& interval)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->aabb2D_world(), interval)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects that do not overlap with the specified interval
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByOverlap(const interval3Df& interval)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->aabb_world(), interval)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects that do not overlap with the specified circle
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByOverlap(const circlef& circle)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->aabb2D_world(), circle)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}

// Filters out game objects that do not overlap with the specified sphere
Engine::GameObjectCollection& Engine::GameObjectCollection::FilterByOverlap(const spheref& sphere)
{
	CollisionManager& c = CollisionManager::GetInstance();
	for (auto i = m_GameObjects.begin(); i != m_GameObjects.end();)
	{
		if (c.IsIntersecting((*i)->aabb_world(), sphere)) { i++; continue; }
		i = m_GameObjects.erase(i);
	}
	return (*this);
}