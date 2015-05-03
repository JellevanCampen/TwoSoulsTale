#pragma once
#ifndef ENGINE_GRAPHICS_SPRITESHEETRESOURCE_H
#define ENGINE_GRAPHICS_SPRITESHEETRESOURCE_H

#include "../resources/Resource.hpp" // Interface for resources (implements reference counting)

#include "glew\glew.h" // For representing OpenGL buffers
#include "glfw\glfw3.h" // For representing OpenGL buffers

#include <string> // For representing a sprite sheet filename

namespace Engine
{
	class ResourceManager;
	class GraphicsManager;

	class SpriteSheetResource : public Resource
	{

	public:

		// Constructor, stores the filename of the sprite sheet
		SpriteSheetResource(std::string filename);

	private:

		// Sprite sheet specifications
		// TODO: Remove initialization of values
		unsigned int m_SpriteWidth = 34;
		unsigned int m_SpriteHeight = 31;
		int m_SpriteOriginX = 17;
		int m_SpriteOriginY = 0;
		unsigned int m_SheetWidth = 238;
		unsigned int m_SheetHeight = 198;
		unsigned int m_SheetColumns = 6;
		unsigned int m_SheetRows = 6;
		int m_SheetSeparationX = 2;
		int m_SheetSeparationY = 2;
		int m_SheetLeft = 1;
		int m_SheetTop = 1;

		// Vertex attribute object for this sprite sheet
		GLuint m_VertexAttributes;

		// Vertex buffer object for this sprite sheet
		GLuint m_Vertices;

		// Texture buffer for this sprite sheet
		GLuint m_Texture;

		// Filename of the sprite sheet resource
		std::string m_Filename;

		// Loads the resource
		virtual bool Load();

		// Unloads the resource
		virtual bool Unload();

		// Initializes and loads the sprite sheet texture
		bool InitializeTexture();

		// Destroys the sprite sheet texture
		bool DestroyTexture();

		// Initializes associated OpenGL attributes and buffers
		bool InitializeBuffers();

		// Destroys associated OpenGL attributes and buffers
		bool DestroyBuffers();

	public:

		friend class ResourceManager;
		friend class GraphicsManager;

	};
}

#endif

