#include "BitmapFontResource.hpp"

#include "..\resources\ResourceManager.hpp" // For reserving the sprite sheet associated to this bitmap font
#include "..\common\utility\XMLFileIO.hpp" // For reading and writing character mappings from and to bitmapfont files
#include "..\common\utility\PathConfig.hpp" // For retrieving the bitmapfonts path

////////////////////////////////////////////////////////////////
// Construction, loading and unloading                        //
////////////////////////////////////////////////////////////////

// Constructor, stores the filename of the bitmap font
Engine::BitmapFontResource::BitmapFontResource(const std::string& filename)
	: m_Filename(filename)
{

}

// Loads the resource
bool Engine::BitmapFontResource::Load()
{
	// Load the bitmap font data
	std::string bitmapFontPath;
	Engine::PathConfig::GetPath("bitmapfonts", bitmapFontPath);
	LoadFile(bitmapFontPath + m_Filename);
	
	// Load the associated sprite sheet
	m_SpriteSheet = ResourceManager::GetInstance().ReserveSpriteSheet(m_FilenameSpriteSheet);

	return true;
}

// Unloads the resource
bool Engine::BitmapFontResource::Unload()
{
	// Unload the associated sprite sheet
	ResourceManager::GetInstance().FreeSpriteSheet(m_SpriteSheet);

	return true;
}

////////////////////////////////////////////////////////////////
// Resource saving and loading								  //
////////////////////////////////////////////////////////////////

// Saves the bitmap font to a file
void Engine::BitmapFontResource::SaveFile(const std::string& filename) const
{
	// Create the file and open it
	XMLFile file;
	XMLFileIO::OpenFile(filename, file);

	// Write bitmap font data
	XMLElement elementBitmapFont = XMLFileIO::AddElement(file, "BitmapFont");
	XMLFileIO::SetAttributeValue(elementBitmapFont, "SpriteSheetResource", m_FilenameSpriteSheet);

	for (auto cm : m_CharacterMapping)
	{
		XMLElement elementCharacterMapping = XMLFileIO::AddElement(elementBitmapFont, "Character");
		XMLFileIO::SetAttributeValue(elementCharacterMapping, "C", std::to_string(cm.first));
		XMLFileIO::SetAttributeValue(elementCharacterMapping, "I", std::to_string(cm.second));
	}

	// Save the file and close it
	XMLFileIO::SaveFile(filename, file);
	XMLFileIO::CloseFile(file);
}

// Loads the bitmap font from a file
void Engine::BitmapFontResource::LoadFile(const std::string& filename)
{
	// Open the file
	XMLFile file;
	XMLFileIO::OpenFile(filename, file);

	// Read bitmap font data
	XMLElement elementBitmapFont = XMLFileIO::GetElement(file, "BitmapFont");
	XMLFileIO::GetAttribute(elementBitmapFont, "SpriteSheetResource", m_FilenameSpriteSheet);

	std::vector<XMLElement> characters;
	XMLFileIO::GetElements(elementBitmapFont, "Character", characters);
	
	std::string charCode;
	unsigned int charIndex;
	for (auto c : characters) 
	{ 
		XMLFileIO::GetAttribute(c, "C", charCode);
		XMLFileIO::GetAttributeAsUnsignedInteger(c, "I", charIndex);
		m_CharacterMapping.insert(std::pair<char, unsigned int>(charCode.c_str()[0], charIndex)); 
	}

	// Close the file
	XMLFileIO::CloseFile(file);
}