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

/**************************************************************/
/* Graphics                                                   */
/**************************************************************/

// Sprite sheet resources //////////////////////////////////////

// Reserves a sprite sheet, returning a handle to the resource
SpriteSheet Engine::ResourceManager::ReserveSpriteSheet(std::string filename)
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
	return (*m_SpriteSheetResources.at(spriteSheet));
}