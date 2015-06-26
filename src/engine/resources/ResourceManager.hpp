#pragma once
#ifndef ENGINE_RESOURCES_RESOURCEMANAGER_H
#define ENGINE_RESOURCES_RESOURCEMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern

#include <string> // For representing resource filenames
#include <unordered_map> // For storing resources by ID

// Resources class includes
#include "../graphics/SpriteSheetResource.hpp"

// Typedefs for resources
typedef std::string SpriteSheet;

namespace Engine{

	class GraphicsManager;

	class ResourceManager : public Singleton<ResourceManager>{

	public:

		// Initializes the resources manager
		void Initialize();

		// Terminates the resource manager
		void Terminate();

		/**************************************************************/
		/* Graphics                                                   */
		/**************************************************************/

		// Sprite sheet resources //////////////////////////////////////

	public:

		// Reserves a sprite sheet, returning a handle to the resource
		SpriteSheet ReserveSpriteSheet(std::string filename);

		// Frees a sprite sheet, freeing up memory if no more reservations exist
		void FreeSpriteSheet(SpriteSheet spriteSheet);

	private:

		// Holds all sprite sheet resources
		std::unordered_map<std::string, SpriteSheetResource*> m_SpriteSheetResources;

		// Gets the sprite sheet resource by its handle
		SpriteSheetResource& GetSpriteSheetResource(SpriteSheet spriteSheet);

	public:

		friend class GraphicsManager;

	};
}

#endif