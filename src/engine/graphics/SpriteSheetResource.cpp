#include "SpriteSheetResource.hpp"

#include "..\resources\ResourceManager.hpp" // For reserving the image associated to this sprite sheet
#include "..\common\utility\XMLFileIO.hpp" // For reading and writing metadata from and to metadata files
#include "..\common\utility\PathConfig.hpp" // For retrieving the sprite sheet path

// Constructor, stores the filename of the sprite sheet
Engine::SpriteSheetResource::SpriteSheetResource(std::string filename)
	: m_Filename(filename)
{
	
}

// Loads the resource
bool Engine::SpriteSheetResource::Load()
{
	// Load the image associated to the sprite sheet
	m_Image = ResourceManager::GetInstance().ReserveImage(m_Filename);

	// Load the sprite sheet metadata
	std::string spriteSheetPath;
	Engine::PathConfig::GetPath("spritesheets", spriteSheetPath);
	std::string filenameMetadata = m_Filename.substr(0, m_Filename.find('.')) + ".spritesheet";
	ReadMetadataFromFile(spriteSheetPath + filenameMetadata);

	// Initialize OpenGL buffers
	InitializeBuffers();

	return true;
}

// Unloads the resource
bool Engine::SpriteSheetResource::Unload()
{
	// Unload the image associated to the sprite sheet
	ResourceManager::GetInstance().FreeImage(m_Image);

	// Destroy OpenGL buffers
	DestroyBuffers();

	return true;
}

// Initializes associated OpenGL attributes and buffers
bool Engine::SpriteSheetResource::InitializeBuffers()
{
	// Generate and bind a vertex attribute object
	glGenVertexArrays(1, &m_VertexAttributes);
	glBindVertexArray(m_VertexAttributes);

	// Generate and bind the vertex buffer
	glGenBuffers(1, &m_Vertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vertices);
	
	// Buffer vertex data
	// -- 6 (x,y) positions representing triangles that form the quad
	// -- 6 (u,v) UVs representing the sprite's location on the sprite sheet
	float left = -m_Metadata.m_SpriteOriginX;
	float right = -m_Metadata.m_SpriteOriginX + m_Metadata.m_SpriteWidth;
	float bottom = -m_Metadata.m_SpriteOriginY;
	float top = -m_Metadata.m_SpriteOriginY + m_Metadata.m_SpriteHeight;
	GLfloat vertexData[2 * 6][2] = 
	{
		{ left, bottom },
		{ right, bottom },
		{ left, top },
		{ right, top },
		{ left, top },
		{ right, bottom },

		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 0.0f }
	};
	glBufferData(GL_ARRAY_BUFFER, 2 * 6 * 2 * 4, &vertexData[0][0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position and UVs)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(6 * 2 * 4)); // UVs

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

// Destroys associated OpenGL attributes and buffers
bool Engine::SpriteSheetResource::DestroyBuffers()
{
	// Delete the vertex buffer and vertex attribute object
	glDeleteBuffers(1, &m_Vertices);
	glDeleteVertexArrays(1, &m_VertexAttributes);

	return true;
}

////////////////////////////////////////////////////////////////
// Metadata manipulation									  //
////////////////////////////////////////////////////////////////

// Calculates the bottom-left and top-right UVs based on the frame number
void Engine::SpriteSheetResource::CalculateUVs(unsigned int frame, f2& out_UV1, f2& out_UV2) const
{	
	// Calculate the coordinates in pixel space (y-axis pointing down, values in range [0, width] x [0, height])
	out_UV1.x((float)(m_Metadata.m_SheetLeft + (frame % m_Metadata.m_SheetColumns) * (m_Metadata.m_SheetSeparationX + m_Metadata.m_SpriteWidth)));
	out_UV2.x((float)(out_UV1.x() + m_Metadata.m_SpriteWidth));
	out_UV1.y((float)(m_Metadata.m_SheetTop + (int)(frame / m_Metadata.m_SheetColumns) * (m_Metadata.m_SheetSeparationY + m_Metadata.m_SpriteHeight)));
	out_UV2.y((float)(out_UV1.y() + m_Metadata.m_SpriteHeight));

	// Convert the coordinates to UV-space (y-axis pointing up, values in range [0, 1] x [0, 1])
	out_UV1.x() /= m_Metadata.m_SheetWidth;
	out_UV2.x() /= m_Metadata.m_SheetWidth;
	out_UV1.y(1.0f - (out_UV1.y() / m_Metadata.m_SheetHeight));
	out_UV2.y(1.0f - (out_UV2.y() / m_Metadata.m_SheetHeight));
}

// Writes the sprite sheet metadata to a file
void Engine::SpriteSheetResource::WriteMetadataToFile(std::string filename)
{
	// Create the file and open it
	XMLFile file;
	XMLFileIO::OpenFile(filename, file);

	// Write sheet layout metadata
	XMLElement elementSheet = XMLFileIO::AddElement(file, "SpriteSheet");
	XMLElement elementLayout = XMLFileIO::AddElement(elementSheet, "SheetLayout");
	XMLFileIO::SetAttributeValue(elementLayout, "SpriteWidth", std::to_string(m_Metadata.m_SpriteWidth));
	XMLFileIO::SetAttributeValue(elementLayout, "SpriteHeight", std::to_string(m_Metadata.m_SpriteHeight));
	XMLFileIO::SetAttributeValue(elementLayout, "SpriteOriginX", std::to_string(m_Metadata.m_SpriteOriginX));
	XMLFileIO::SetAttributeValue(elementLayout, "SpriteOriginY", std::to_string(m_Metadata.m_SpriteOriginY));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetWidth", std::to_string(m_Metadata.m_SheetWidth));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetHeight", std::to_string(m_Metadata.m_SheetHeight));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetRows", std::to_string(m_Metadata.m_SheetRows));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetColumns", std::to_string(m_Metadata.m_SheetColumns));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetSeparationX", std::to_string(m_Metadata.m_SheetSeparationX));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetSeparationY", std::to_string(m_Metadata.m_SheetSeparationY));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetLeft", std::to_string(m_Metadata.m_SheetLeft));
	XMLFileIO::SetAttributeValue(elementLayout, "SheetTop", std::to_string(m_Metadata.m_SheetTop));
	XMLFileIO::SetAttributeValue(elementLayout, "ColorTransparancyRed", std::to_string(m_Metadata.m_ColorTransparancyRed));
	XMLFileIO::SetAttributeValue(elementLayout, "ColorTransparancyGreen", std::to_string(m_Metadata.m_ColorTransparancyGreen));
	XMLFileIO::SetAttributeValue(elementLayout, "ColorTransparancyBlue", std::to_string(m_Metadata.m_ColorTransparancyBlue));
	XMLFileIO::SetAttributeValue(elementLayout, "ColorTransparancyAlpha", std::to_string(m_Metadata.m_ColorTransparancyAlpha));

	// Save the file and close it
	XMLFileIO::SaveFile(filename, file);
	XMLFileIO::CloseFile(file);
}

// Reads the sprite sheet metadata from a file
void Engine::SpriteSheetResource::ReadMetadataFromFile(std::string filename)
{
	// Open the file
	XMLFile file;
	XMLFileIO::OpenFile(filename, file);

	// Write sheet layout metadata
	XMLElement elementSheet = XMLFileIO::GetElement(file, "SpriteSheet");
	XMLElement elementLayout = XMLFileIO::GetElement(elementSheet, "SheetLayout");
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "SpriteWidth", m_Metadata.m_SpriteWidth);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "SpriteHeight", m_Metadata.m_SpriteHeight);
	XMLFileIO::GetAttributeAsInteger(elementLayout, "SpriteOriginX", m_Metadata.m_SpriteOriginX);
	XMLFileIO::GetAttributeAsInteger(elementLayout, "SpriteOriginY", m_Metadata.m_SpriteOriginY);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "SheetWidth", m_Metadata.m_SheetWidth);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "SheetHeight", m_Metadata.m_SheetHeight);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "SheetRows", m_Metadata.m_SheetRows);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "SheetColumns", m_Metadata.m_SheetColumns);
	XMLFileIO::GetAttributeAsInteger(elementLayout, "SheetSeparationX", m_Metadata.m_SheetSeparationX);
	XMLFileIO::GetAttributeAsInteger(elementLayout, "SheetSeparationY", m_Metadata.m_SheetSeparationY);
	XMLFileIO::GetAttributeAsInteger(elementLayout, "SheetLeft", m_Metadata.m_SheetLeft);
	XMLFileIO::GetAttributeAsInteger(elementLayout, "SheetTop", m_Metadata.m_SheetTop);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "ColorTransparancyRed", m_Metadata.m_ColorTransparancyRed);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "ColorTransparancyGreen", m_Metadata.m_ColorTransparancyGreen);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "ColorTransparancyBlue", m_Metadata.m_ColorTransparancyBlue);
	XMLFileIO::GetAttributeAsUnsignedInteger(elementLayout, "ColorTransparancyAlpha", m_Metadata.m_ColorTransparancyAlpha);

	// Close the file
	XMLFileIO::CloseFile(file);
}