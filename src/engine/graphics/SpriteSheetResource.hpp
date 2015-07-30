#pragma once
#ifndef ENGINE_GRAPHICS_SPRITESHEETRESOURCE_H
#define ENGINE_GRAPHICS_SPRITESHEETRESOURCE_H

#include "../resources/Resource.hpp" // Interface for resources (implements reference counting)
#include "../graphics/ImageResource.hpp" // For storing the image associated to the sprite sheet

#include <string> // For representing a sprite sheet filename

namespace Engine
{
	// Typdef for a handle to a spritesheet
	typedef std::string SpriteSheet;

	class ResourceManager;
	class GraphicsManager;

	class SpriteSheetResource : public Resource
	{

	public:

		////////////////////////////////////////////////////////////////
		// Construction, loading and unloading                        //
		////////////////////////////////////////////////////////////////

		// Constructor, stores the filename of the sprite sheet
		SpriteSheetResource(const std::string& filename);

		// Loads the resource
		virtual bool Load();

		// Unloads the resource
		virtual bool Unload();

	private:

		// Filename of the sprite sheet resource
		std::string m_Filename;

		// Filename of the associated image resource
		std::string m_FilenameImage;

		// Image associated with the sprite sheet
		Image m_Image;

		// Struct describing the metadata of the sprite sheet
		typedef struct Metadata
		{
			// Sheet layout
			unsigned int m_SpriteWidth = 16;
			unsigned int m_SpriteHeight = 16;
			int m_SpriteOriginX = 0;
			int m_SpriteOriginY = 0;
			unsigned int m_SheetWidth = 256;
			unsigned int m_SheetHeight = 256;
			unsigned int m_SheetRows = 16;
			unsigned int m_SheetColumns = 16;
			int m_SheetSeparationX = 0;
			int m_SheetSeparationY = 0;
			int m_SheetLeft = 0;
			int m_SheetTop = 0;
			unsigned int m_ColorTransparancyRed = 255;
			unsigned int m_ColorTransparancyGreen = 255;
			unsigned int m_ColorTransparancyBlue = 255;
			unsigned int m_ColorTransparancyAlpha = 255;
		};

		// Sprite sheet specifications
		Metadata m_Metadata;

	public:

		////////////////////////////////////////////////////////////////
		// Image manipulation										  //
		////////////////////////////////////////////////////////////////

		// Gets the ID of the associated image to this sprite sheet
		inline Image& GetImage() { return m_Image; }

	private:

		////////////////////////////////////////////////////////////////
		// Metadata manipulation									  //
		////////////////////////////////////////////////////////////////

		// Calculates the bottom-left and top-right positions of the sprite in local coordinates to the sprite origin
		inline void CalculatePositions(f2& out_P1, f2& out_P2) const 
		{
			out_P1.x(- m_Metadata.m_SpriteOriginX);
			out_P1.y(-m_Metadata.m_SpriteOriginY);
			out_P2.x(m_Metadata.m_SpriteWidth - m_Metadata.m_SpriteOriginX);
			out_P2.y(m_Metadata.m_SpriteHeight - m_Metadata.m_SpriteOriginY);
		}

		// Calculates the bottom-left and top-right UVs based on the frame number
		void CalculateUVs(unsigned int frame, f2& out_UV1, f2& out_UV2) const;

		// Writes the sprite sheet metadata to a file
		void SaveFile(const std::string& filename);

		// Reads the sprite sheet metadata from a file
		void LoadFile(const std::string& filename);

		friend class ResourceManager;
		friend class GraphicsManager;

	};
}

#endif

