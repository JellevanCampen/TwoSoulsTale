#include "SpriteSheetResource.hpp"

// Constructor, stores the filename of the sprite sheet
Engine::SpriteSheetResource::SpriteSheetResource(std::string filename)
{
	m_Filename = filename;
}

// Loads the resource
bool Engine::SpriteSheetResource::Load()
{
	// TODO: implement sprite sheet loading

	// Initialize OpenGL buffers
	InitializeBuffers();

	return true;
}

// Unloads the resource
bool Engine::SpriteSheetResource::Unload()
{
	// TODO: implement sprite sheet unloading

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
	float left = -m_SpriteOriginX;
	float right = -m_SpriteOriginX + m_SpriteWidth;
	float bottom = -m_SpriteOriginY;
	float top = -m_SpriteOriginY + m_SpriteHeight;
	GLfloat vertexData[2 * 6][2] = 
	{
		{ left, bottom },
		{ right, bottom },
		{ left, top },
		{ right, top },
		{ left, top },
		{ right, bottom },

		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
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
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

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