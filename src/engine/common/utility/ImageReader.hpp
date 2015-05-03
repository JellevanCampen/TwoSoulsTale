#pragma once
#ifndef ENGINE_COMMON_UTILITY_IMAGEREADER_H
#define ENGINE_COMMON_UTILITY_IMAGEREADER_H

#include "glew\glew.h" // For representing OpenGL texture IDs
#include "glfw\glfw3.h" // For representing OpenGL texture IDs

#include <string> // For representing image file names

namespace Engine{

	class ImageReader{

	public:

		// Generates an OpenGL texture from a PNG file
		static GLuint ReadPNG(std::string filename, bool singleChannel = false);

	};
}

#endif
