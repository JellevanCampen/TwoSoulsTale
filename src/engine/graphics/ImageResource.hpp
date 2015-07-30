#pragma once
#ifndef ENGINE_GRAPHICS_IMAGERESOURCE_H
#define ENGINE_GRAPHICS_IMAGERESOURCE_H

#include "../resources/Resource.hpp" // Interface for resources (implements reference counting)

#include "glew\glew.h" // For representing OpenGL buffers
#include "glfw\glfw3.h" // For representing OpenGL buffers
#include "FreeImage.h" // For reading image files and processing images

#include "..\common\utility\VectorTypes.hpp" // For representing 2D positions

#include <string> // For representing an image filename

namespace Engine
{
	// Typedef for a handle to an Image
	typedef std::string Image;

	class ImageResource : public Resource
	{

	public:

		////////////////////////////////////////////////////////////////
		// Construction, loading and unloading                        //
		////////////////////////////////////////////////////////////////

		// Constructor (based on filename)
		ImageResource(const std::string& filename);

		// Loads the image from file
		virtual bool Load();

		// Unloads the image
		virtual bool Unload();

	private:

		// Filename of the image resource
		std::string m_Filename;

		// FreeImageBitmap used to store the image
		FIBITMAP* m_Image;

		// ID of the OpenGL texture buffer associated to this image
		GLuint m_TextureID;

		// Types of modifications that invalidate the texture buffer on the GPU
		enum class DirtyType
		{
			CLEAN,					// The image was not modified
			DIRTY_VALUES,			// The image values were modified, but the size is unchanged
			DIRTY_SIZE_AND_VALUES	// Both the image size and values were changed
		};

		// Stored in what way the image was modified since the last upload to the GPU
		DirtyType m_Dirty;

		// Supported internal representation of images
		enum class ImageFormat
		{
			INVALID,
			MONOCHROME,		// 1-bit per pixel, 1 component (monochrome)
			GRAYSCALE,  // 8-bit per pixel, 1 component (grayscale)
			RGB,		// 24-bit per pixel, 3 components (rgb)
			RGBA		// 32-bit per pixel, 4 components (rgba)
		};

		// Image format of the image resource
		ImageFormat m_ImageFormat;

		// Gets the internal ImageFormat from the FreeImage image format
		ImageFormat GetImageFormat(FREE_IMAGE_FORMAT freeImageImageFormat);

		// Converts the image to a suitable format for internal use
		void ConvertImageFormat();

	public:

		////////////////////////////////////////////////////////////////
		// Image metadata											  //
		////////////////////////////////////////////////////////////////

		// Gets the dimensions of the image
		i2 GetDimensions();

	private:

		////////////////////////////////////////////////////////////////
		// Texture generation										  //
		////////////////////////////////////////////////////////////////

		// Returns the ID of the OpenGL texture buffer associated to this image
		GLuint GetTexture();

		// Uploads the texture to the GPU (called automatically, but can be explicitely called to force an upload at a desired point in time)
		void UploadTexture();

	public:
		
		////////////////////////////////////////////////////////////////
		// Image manipulation										  //
		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////// Rotations

		// Available rotation angles
		enum class RotationAngle
		{
			CW_90, 
			CW_180, 
			CW_270,
			CCW_90,
			CCW_180,
			CCW_270
		};

		// Rotates the image (without affecting the size of the image)
		ImageResource& Rotate(RotationAngle angle);

		// Rotates the image (and resizes the image)
		ImageResource& Rotate(double angle);

		// Rotates the image (and resizes the image)
		ImageResource& Rotate(double angle, const f2& origin);

		// Flips the image horizontally
		ImageResource& FlipHorizontal();

		// Flips the image Vertically
		ImageResource& FlipVertical();

		//////////////////////////////////////////////////////// Scaling

		// Available resampling filters
		enum class ResampleFilter
		{
			NEAREST_NEIGHBOR, 
			BILINEAR, 
			BSPLINE, 
			BICUBIC, 
			CATMULLROM, 
			LANCZOS
		};

		// Available rescaling policies
		enum class RescalePolicy
		{
			MATCH_DIMENSIONS, 
			FIT_INSIDE_DIMENSIONS,
			COVER_DIMENSIONS
		};

		// Rescales the image to fit the specified dimensions
		ImageResource& Rescale(const i2& dstDimensions, RescalePolicy policy = RescalePolicy::MATCH_DIMENSIONS, ResampleFilter filter = ResampleFilter::NEAREST_NEIGHBOR);

	private:

		// Gets the FreeImage resampling filter from the internal ResampleFilter
		FREE_IMAGE_FILTER GetFilter(ResampleFilter filter);

	public:

		/////////////////////////////////////////////// Color adjustment

		// Adjusts the gamma of the image
		ImageResource& AdjustGamma(double gamma);

		// Adjusts the brightness of the image
		ImageResource& AdjustBrightness(double brightness);

		// Adjusts the contrast of the image
		ImageResource& AdjustContrast(double contrast);

		// Inverts the colors of the image
		ImageResource& InvertColors();

		friend class ResourceManager;
		friend class GraphicsManager;

	};
}

#endif

