#pragma once
#ifndef ENGINE_GRAPHICS_BITMAPFONTRESOURCE_H
#define ENGINE_GRAPHICS_BITMAPFONTRESOURCE_H

#include "../resources/Resource.hpp" // Interface for resources (implements reference counting)
#include "../graphics/SpriteSheetResource.hpp" // For storing the sprite sheet associated to the bitmap font
#include "../debugging/LoggingManager.hpp" // For reporting errors during character retrieval
#include "../common/utility/ColorTypes.hpp" // For representing an RGBA color

#include <string> // For representing a sprite sheet filename
#include <unordered_map> // For storing the mapping of characters to sprite sheet frames

namespace Engine
{
	// Typdef for a handle to a spritesheet
	typedef std::string BitmapFont;

	class ResourceManager;
	class GraphicsManager;

	class BitmapFontResource : public Resource
	{

	private:

		////////////////////////////////////////////////////////////////
		// Construction, loading and unloading                        //
		////////////////////////////////////////////////////////////////

		// Constructor, stores the filename of the bitmap font
		BitmapFontResource(const std::string& filename);

		// Destructor (private, only friend classes can destroy the resource)
		~BitmapFontResource() { }

		// Loads the resource
		virtual bool Load();

		// Unloads the resource
		virtual bool Unload();

		// Filename of the bitmap font resource
		std::string m_Filename;

		// Filename of the associated sprite sheet resource
		std::string m_FilenameSpriteSheet;

		// Image associated with the bitmap font
		SpriteSheet m_SpriteSheet;

		// Mapping of characters to frames within the sprite sheet
		std::unordered_map<char, unsigned int> m_CharacterMapping;

		////////////////////////////////////////////////////////////////
		// Character mapping										  //
		////////////////////////////////////////////////////////////////

		// Gets the frame of the specified character
		inline unsigned int GetFrame(char c) const 
		{
			auto i = m_CharacterMapping.find(c);
			if (i == m_CharacterMapping.end()) { LoggingManager::GetInstance().Log(LoggingManager::Warning, "[BitmapFont] Character <" + std::to_string(c) + "> is not available in the bitmap font"); return 0; }
			return i->second;
		}

		// Gets the character data for a text message
		void GetCharacterData(std::string text, std::vector<f2>& out_CharacterPositions, std::vector<unsigned int>& out_GlyphIndices, std::vector<colorRGBA>& out_GlyphColors);

		////////////////////////////////////////////////////////////////
		// Resource saving and loading								  //
		////////////////////////////////////////////////////////////////

		// Saves the bitmap font to a file
		void SaveFile(const std::string& filename) const;

		// Loads the bitmap font from a file
		void LoadFile(const std::string& filename);

		friend class ResourceManager;
		friend class GraphicsManager;

	};
}

#endif

