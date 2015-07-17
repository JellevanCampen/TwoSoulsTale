#pragma once
#ifndef ENGINE_RESOURCES_RESOURCEMANAGER_H
#define ENGINE_RESOURCES_RESOURCEMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern

#include <string> // For representing resource filenames
#include <unordered_map> // For storing resources by ID

// Resources class includes
#include "../graphics/ImageResource.hpp"
#include "../graphics/SpriteSheetResource.hpp"

namespace Engine{

	class GraphicsManager;

	class ResourceManager : public Singleton<ResourceManager>{

	public:

		// Initializes the resources manager
		void Initialize();

		// Terminates the resource manager
		void Terminate();

		////////////////////////////////////////////////////////////////
		// Graphics                                                   //
		////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////// Image resources

	public:

		// Reserves an image, returning a handle to the resource
		Image ReserveImage(std::string filename);

		// Frees an image, freeing up memory if no more reservations exist
		void FreeImage(Image image);

		// Gets the image resource by its handle
		ImageResource& GetImageResource(Image image);

	private:

		// Holds all image resources
		std::unordered_map<Image, ImageResource*> m_ImageResources;

		///////////////////////////////////////// Sprite sheet resources

	public:

		// Reserves a sprite sheet, returning a handle to the resource
		SpriteSheet ReserveSpriteSheet(std::string filename);

		// Frees a sprite sheet, freeing up memory if no more reservations exist
		void FreeSpriteSheet(SpriteSheet spriteSheet);

		// Gets the sprite sheet resource by its handle
		SpriteSheetResource& GetSpriteSheetResource(SpriteSheet spriteSheet);

	private:

		// Holds all sprite sheet resources
		std::unordered_map<SpriteSheet, SpriteSheetResource*> m_SpriteSheetResources;

	public:

		friend class GraphicsManager;

	};
}

#endif