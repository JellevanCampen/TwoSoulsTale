#include "ResourceManager.hpp"

#include "../debugging/LoggingManager.hpp" // Logging manager for reporting statuses

// Initializes the resources manager
void Engine::ResourceManager::Initialize()
{

}

// Terminates the resource manager
void Engine::ResourceManager::Terminate()
{

}

////////////////////////////////////////////////////////////////
// Graphics                                                   //
////////////////////////////////////////////////////////////////

//////////////////////////////////////////////// Image resources

// Reserves an image, returning a handle to the resource
Engine::Image Engine::ResourceManager::ReserveImage(std::string filename)
{
	if (m_ImageResources.count(filename) == 0)
	{
		// Resource is not loaded yet
		ImageResource* imageResource = new ImageResource(filename);
		if (!imageResource->Load())
		{
			LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to load image resource <" + filename + ">");
		}
		imageResource->AddReservation();
		m_ImageResources.insert(std::pair<Image, ImageResource*>(filename, imageResource));
	}
	else
	{
		// Resource is already loaded
		m_ImageResources.at(filename)->AddReservation();
	}

	return filename;
}

// Frees an image, freeing up memory if no more reservations exist
void Engine::ResourceManager::FreeImage(Image image)
{
	if (m_ImageResources.count(image) != 0)
	{
		ImageResource* imageResource = m_ImageResources.at(image);
		imageResource->RemoveReservation();
		if (imageResource->GetNumReservations() <= 0)
		{
			if (!imageResource->Unload())
			{
				LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to unload image resource <" + image + ">");
			}
			delete imageResource;
			m_ImageResources.erase(image);
		}
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "Tried to free image resource <" + image + ">, while the resource is not loaded anymore");
	}
}

// Gets the image resource by its handle
Engine::ImageResource& Engine::ResourceManager::GetImageResource(Image image)
{
	return (*m_ImageResources[image]);
}

///////////////////////////////////////// Sprite sheet resources

// Reserves a sprite sheet, returning a handle to the resource
Engine::SpriteSheet Engine::ResourceManager::ReserveSpriteSheet(std::string filename)
{
	if (m_SpriteSheetResources.count(filename) == 0)
	{
		// Resource is not loaded yet
		SpriteSheetResource* spriteSheetResource = new SpriteSheetResource(filename);
		if (!spriteSheetResource->Load())
		{
			LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to load sprite sheet resource <" + filename + ">");
		}
		spriteSheetResource->AddReservation();
		m_SpriteSheetResources.insert(std::pair<SpriteSheet, SpriteSheetResource*>(filename, spriteSheetResource));
	}
	else
	{
		// Resource is already loaded
		m_SpriteSheetResources.at(filename)->AddReservation();
	}

	return filename;
}

// Frees a sprite sheet, freeing up memory if no more reservations exist
void Engine::ResourceManager::FreeSpriteSheet(SpriteSheet spriteSheet)
{
	if (m_SpriteSheetResources.count(spriteSheet) != 0)
	{
		SpriteSheetResource* spriteSheetResource = m_SpriteSheetResources.at(spriteSheet);
		spriteSheetResource->RemoveReservation();
		if (spriteSheetResource->GetNumReservations() <= 0)
		{
			if (!spriteSheetResource->Unload())
			{
				LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to unload sprite sheet resource <" + spriteSheet + ">");
			}
			delete spriteSheetResource;
			m_SpriteSheetResources.erase(spriteSheet);
		}
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "Tried to free sprite sheet resource <" + spriteSheet + ">, while the resource is not loaded anymore");
	}
}

// Gets the sprite sheet resource by its handle
Engine::SpriteSheetResource& Engine::ResourceManager::GetSpriteSheetResource(SpriteSheet spriteSheet)
{
	return (*m_SpriteSheetResources[spriteSheet]);
}