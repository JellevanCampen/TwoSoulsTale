#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECTCOLLECTION_H
#define ENGINE_WORLD_GAMEOBJECTCOLLECTION_H

#include "GameObject.hpp" // For representing game objects
#include "../common/utility/IntervalTypes.hpp" // For representing location intervals

#include <list> // For representing a collection of game objects (with fast random removal)

namespace Engine{

	class GameObjectCollection{

	private:

		// List of game objects
		std::list<GameObject*> m_GameObjects;

	public:

		// Constructors
		GameObjectCollection() { }

		////////////////////////////////////////////////////////////////
		// Collection access										  //
		////////////////////////////////////////////////////////////////

		// Returns the list of game objects
		inline std::list<GameObject*>& list() { return m_GameObjects; }

		// Returns the list of game objects
		inline const std::list<GameObject*>& list() const { return m_GameObjects; }

		////////////////////////////////////////////////////////////////
		// Filtering												  //
		////////////////////////////////////////////////////////////////

		// Filters out game objects that do not match the specified GUID
		GameObjectCollection& FilterByGUID(GameObjectGUID guid);

		// Filters out game objects that do not match the specified type
		GameObjectCollection& FilterByType(GameObjectType type);

		// Filters out game objects outside of the specified interval
		GameObjectCollection& FilterByLocation(interval2Df interval);

		// Filters out game objects outside of the specified interval
		GameObjectCollection& FilterByLocation(interval3Df interval);

		// Filters out game objects outside of the specified circle
		GameObjectCollection& FilterByLocation(circlef circle);

		// Filters out game objects outside of the specified sphere
		GameObjectCollection& FilterByLocation(spheref sphere);

		// Filters out game objects that do not overlap with the specified interval
		GameObjectCollection& FilterByOverlap(interval2Df interval);

		// Filters out game objects that do not overlap with the specified interval
		GameObjectCollection& FilterByOverlap(interval3Df interval);

		// Filters out game objects that do not overlap with the specified circle
		GameObjectCollection& FilterByOverlap(circlef circle);

		// Filters out game objects that do not overlap with the specified sphere
		GameObjectCollection& FilterByOverlap(spheref sphere);

	};
}

#endif