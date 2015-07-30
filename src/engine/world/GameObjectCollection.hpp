#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECTCOLLECTION_H
#define ENGINE_WORLD_GAMEOBJECTCOLLECTION_H

#include "GameObject.hpp" // For representing game objects
#include "../common/utility/IntervalTypes.hpp" // For representing location intervals

#include <unordered_set> // For representing a collection of game objects (with fast random removal)
#include <set> // For constructing a game object collection from a set of game objects

namespace Engine{

	class GameObjectCollection{

	private:

		// List of game objects
		std::unordered_set<GameObject*> m_GameObjects;

	public:

		// Constructors
		GameObjectCollection() { }
		GameObjectCollection(const std::unordered_set<GameObject*>& objects) { m_GameObjects = std::unordered_set<GameObject*>(objects.begin(), objects.end()); }
		GameObjectCollection(const std::set<GameObject*>& objects) { m_GameObjects = std::unordered_set<GameObject*>(objects.begin(), objects.end()); }

		////////////////////////////////////////////////////////////////
		// Collection access										  //
		////////////////////////////////////////////////////////////////

		// Returns all game objects in the collection
		inline std::unordered_set<GameObject*>& objects() { return m_GameObjects; }

		// Returns all game objects in the collection
		inline const std::unordered_set<GameObject*>& objects() const { return m_GameObjects; }

		////////////////////////////////////////////////////////////////
		// Collection manipulation									  //
		////////////////////////////////////////////////////////////////

		// Moves all elements of another game object collection to this one (removes elements from the other list)
		GameObjectCollection& merge(GameObjectCollection& other);

		// Operators
		inline GameObjectCollection operator+ (const GameObjectCollection& other) const 
		{ 
			// Filter out duplicate elements using a set
			std::unordered_set<GameObject*> s(m_GameObjects);
			for (GameObject* g : other.objects()) { s.insert(g); }

			// Add the merged collection to the list
			return GameObjectCollection(s);
		}

		////////////////////////////////////////////////////////////////
		// Filtering												  //
		////////////////////////////////////////////////////////////////

		// Filters out game objects that do not match the specified GUID
		GameObjectCollection& FilterByGUID(GameObjectGUID guid);

		// Filters out game objects that do not match the specified type
		GameObjectCollection& FilterByType(GameObjectType type);

		// Filters out game objects outside of the specified interval
		GameObjectCollection& FilterByLocation(const interval2Df& interval);

		// Filters out game objects outside of the specified interval
		GameObjectCollection& FilterByLocation(const interval3Df& interval);

		// Filters out game objects outside of the specified circle
		GameObjectCollection& FilterByLocation(const circlef& circle);

		// Filters out game objects outside of the specified sphere
		GameObjectCollection& FilterByLocation(const spheref& sphere);

		// Filters out game objects that do not overlap with the specified interval
		GameObjectCollection& FilterByOverlap(const interval2Df& interval);

		// Filters out game objects that do not overlap with the specified interval
		GameObjectCollection& FilterByOverlap(const interval3Df& interval);

		// Filters out game objects that do not overlap with the specified circle
		GameObjectCollection& FilterByOverlap(const circlef& circle);

		// Filters out game objects that do not overlap with the specified sphere
		GameObjectCollection& FilterByOverlap(const spheref& sphere);

	};
}

#endif