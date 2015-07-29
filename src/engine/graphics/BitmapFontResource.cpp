#include "BitmapFontResource.hpp"

#include "..\resources\ResourceManager.hpp" // For reserving the sprite sheet associated to this bitmap font
#include "..\common\utility\XMLFileIO.hpp" // For reading and writing character mappings from and to bitmapfont files
#include "..\common\utility\PathConfig.hpp" // For retrieving the bitmapfonts path
#include <sstream> // For parsing commands in text strings

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

////////////////////////////////////////////////////////////////
// Character mapping										  //
////////////////////////////////////////////////////////////////

// Gets the character data for a text message
void Engine::BitmapFontResource::GetCharacterData(std::string text, std::vector<f2>& out_CharacterPositions, std::vector<unsigned int>& out_GlyphIndices)
{
	int x = 0;
	int y = 0;

	for (auto c : text)
	{
		// Start a new line on a newline character
		if (c == '\n') { y++; x = 0; continue; }

		out_CharacterPositions.push_back(f2(x, y));
		out_GlyphIndices.push_back(GetFrame(c));
		x++;
	}
}

// Gets the character data for a text message
// Gets the character data for a text message (also parses color tags)
void Engine::BitmapFontResource::GetCharacterDataAdvanced(std::string text, std::vector<f2>& out_CharacterPositions, std::vector<unsigned int>& out_GlyphIndices, std::vector<colorRGBA>& out_GlyphColors, const colorRGBA& defaultColor)
{
	int x = 0;
	int y = 0;
	colorRGBA color(defaultColor);

	for (auto it = text.begin(); it != text.end(); it++)
	{
		// Start a new line on a newline character
		if (*it == '\n') { y++; x = 0; continue; }

		// Parse tags (preceded by "##")
		if (*it == '#')
		{
			it++;

			// Not a tag, just display the # symbol
			if (*it != '#') { it--; goto normalChar; }

			it++; 

			// Color tag
			if (*it == 'c')
			{
				it += 2; // Skip the opening bracket "("
				int r, g, b, a;
				std::stringstream ss;
				while (true) 
				{ 
					if (*it == ',') { ss >> r; ss.clear(); ss.str(""); it++; break; }
					if (*it == ')') { ss >> r; ss.clear(); ss.str(""); goto parseGray; }
					ss << *it; it++; 
				}
				while (true) 
				{ 
					if (*it == ',') { ss >> g; ss.clear(); ss.str(""); it++; break; }
					ss << *it; it++; 
				}
				while (true) 
				{ 
					if (*it == ',') { ss >> b; ss.clear(); ss.str(""); it++; break; }
					if (*it == ')') { ss >> b; ss.clear(); ss.str(""); goto parseRGB; }
					ss << *it; it++; 
				}
				while (true) 
				{ 
					if (*it == ')') { ss >> a; ss.clear(); ss.str(""); goto parseRGBA; }
					ss << *it; it++; 
				}

			parseGray: color = colorRGBA(r); continue;
			parseRGB: color = colorRGBA(r, g, b); continue;
			parseRGBA: color = colorRGBA(r, g, b, a); continue;
			}
		}

	normalChar:

		out_CharacterPositions.push_back(f2(x, y));
		out_GlyphIndices.push_back(GetFrame(*it));
		out_GlyphColors.push_back(color);
		x++;
	}
}