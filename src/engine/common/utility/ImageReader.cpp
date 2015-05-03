#include "ImageReader.hpp"

#include "FreeImage.h" // FreeImage for reading image files

// Generates an OpenGL texture from a PNG file
GLuint Engine::ImageReader::ReadPNG(std::string filename, bool singleChannel)
{
	// Load the file
	FIBITMAP* imageSource = FreeImage_Load(FIF_PNG, filename.c_str(), 0);
	FIBITMAP* image = FreeImage_ConvertTo32Bits(imageSource);
	void* imageData = (void*)FreeImage_GetBits(image);

	unsigned int bpp = FreeImage_GetBPP(image);
	unsigned int redmask = FreeImage_GetRedMask(image);
	unsigned int width = FreeImage_GetWidth(image);
	unsigned int height = FreeImage_GetHeight(image);

	// Generate an OpenGL texture and copy the data into it
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	GLenum internalFormat = (singleChannel) ? GL_R8 : GL_RGBA8;

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, imageData);

	FreeImage_Unload(imageSource);
	FreeImage_Unload(image);

	return texture;
}