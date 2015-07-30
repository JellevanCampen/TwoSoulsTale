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
Engine::Image Engine::ResourceManager::ReserveImage(const std::string& filename)
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
Engine::SpriteSheet Engine::ResourceManager::ReserveSpriteSheet(const std::string& filename)
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

////////////////////////////////////////// Bitmap font resources

// Reserves a bitmap font, returning a handle to the resource
Engine::BitmapFont Engine::ResourceManager::ReserveBitmapFont(const std::string& filename)
{
	if (m_BitmapFontResources.count(filename) == 0)
	{
		// Resource is not loaded yet
		BitmapFontResource* bitmapFontResource = new BitmapFontResource(filename);
		if (!bitmapFontResource->Load())
		{
			LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to load bitmap font resource <" + filename + ">");
		}
		bitmapFontResource->AddReservation();
		m_BitmapFontResources.insert(std::pair<BitmapFont, BitmapFontResource*>(filename, bitmapFontResource));
	}
	else
	{
		// Resource is already loaded
		m_BitmapFontResources.at(filename)->AddReservation();
	}

	return filename;
}

// Frees a bitmap font, freeing up memory if no more reservations exist
void Engine::ResourceManager::FreeBitmapFont(BitmapFont bitmapFont)
{
	if (m_BitmapFontResources.count(bitmapFont) != 0)
	{
		BitmapFontResource* bitmapFontResource = m_BitmapFontResources.at(bitmapFont);
		bitmapFontResource->RemoveReservation();
		if (bitmapFontResource->GetNumReservations() <= 0)
		{
			if (!bitmapFontResource->Unload())
			{
				LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to unload bitmap font resource <" + bitmapFont + ">");
			}
			delete bitmapFontResource;
			m_BitmapFontResources.erase(bitmapFont);
		}
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "Tried to free bitmap font resource <" + bitmapFont + ">, while the resource is not loaded anymore");
	}
}

// Gets the bitmap font resource by its handle
Engine::BitmapFontResource& Engine::ResourceManager::GetBitmapFontResource(BitmapFont bitmapFont)
{
	return (*m_BitmapFontResources[bitmapFont]);
}