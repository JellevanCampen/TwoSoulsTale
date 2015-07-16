#pragma once
#ifndef ENGINE_GRAPHICS_SPRITESHEETRESOURCE_H
#define ENGINE_GRAPHICS_SPRITESHEETRESOURCE_H

#include "../resources/Resource.hpp" // Interface for resources (implements reference counting)
#include "../graphics/ImageResource.hpp" // For storing the image associated to the sprite sheet

#include "glew\glew.h" // For representing OpenGL buffers
#include "glfw\glfw3.h" // For representing OpenGL buffers

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
		SpriteSheetResource(std::string filename);

		// Loads the resource
		virtual bool Load();

		// Unloads the resource
		virtual bool Unload();

	private:

		// Filename of the sprite sheet resource
		std::string m_Filename;

		// Image associated to the sprite sheet
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

		// Vertex attribute object for this sprite sheet
		GLuint m_VertexAttributes;

		// Vertex buffer object for this sprite sheet
		GLuint m_Vertices;

		// Initializes associated OpenGL attributes and buffers
		bool InitializeBuffers();

		// Destroys associated OpenGL attributes and buffers
		bool DestroyBuffers();

	public:

		////////////////////////////////////////////////////////////////
		// Metadata manipulation									  //
		////////////////////////////////////////////////////////////////

		// Writes the sprite sheet metadata to a file
		void WriteMetadataToFile(std::string filename);

		// Reads the sprite sheet metadata from a file
		void ReadMetadataFromFile(std::string filename);

		friend class ResourceManager;
		friend class GraphicsManager;

	};
}

#endif

