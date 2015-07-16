#include "ImageResource.hpp"

#include "..\debugging\LoggingManager.hpp" // For reporting errors
#include "..\common\utility\PathConfig.hpp" // For retrieving the image path

////////////////////////////////////////////////////////////////
// Construction, loading and unloading                        //
////////////////////////////////////////////////////////////////

// Constructor (based on filename)
Engine::ImageResource::ImageResource(std::string filename) 
	: m_Filename(filename)
	, m_Image(NULL)
	, m_TextureID(-1)
	, m_Dirty(DirtyType::DIRTY_SIZE_AND_VALUES)
	, m_ImageFormat(ImageFormat::INVALID)
{

}

// Loads the image from file
bool Engine::ImageResource::Load()
{
	// Retrieve the full path to the image resource
	std::string path;
	Engine::PathConfig::GetPath("images", path);
	std::string file = path + m_Filename;

	// Get the filetype from the bit-layout (or from the filename)
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(file.c_str());
	if (format == FREE_IMAGE_FORMAT::FIF_UNKNOWN) { format = FreeImage_GetFIFFromFilename(file.c_str()); }
	m_ImageFormat = GetImageFormat(format);
	if (m_ImageFormat == ImageFormat::INVALID) { LoggingManager::GetInstance().Log(LoggingManager::Error, "Failed to load image resource <" + m_Filename + ">. File format is not supported or could not be determined. "); }
	
	// Load the file and convert it to a usable format
	FIBITMAP* image = FreeImage_Load(format, file.c_str(), 0);
	if (image == NULL) { LoggingManager::GetInstance().Log(LoggingManager::Error, "Failed to load image resource <" + m_Filename + ">. File could not be read or could not be found. "); }
	switch (m_ImageFormat)
	{
	case ImageFormat::MONOCHROME: m_Image = FreeImage_ConvertToGreyscale(image); break; // Note: 1 bit is stored as 8 bits in memory, could be 8 times more efficient if optimized
	case ImageFormat::GRAYSCALE: m_Image = FreeImage_ConvertToGreyscale(image); break;
	case ImageFormat::RGB: m_Image = FreeImage_ConvertTo24Bits(image); break;
	case ImageFormat::RGBA: m_Image = FreeImage_ConvertTo32Bits(image); break;
	}
	FreeImage_Unload(image);
	
	// Generate an OpenGL texture and upload the image to the GPU
	glGenTextures(1, &m_TextureID);
	UploadTexture();
	
	return true;
}

// Unloads the image
bool Engine::ImageResource::Unload()
{
	// Delete the OpenGL texture storing the image
	glDeleteTextures(1, &m_TextureID);

	// Unload the FreeImage image from memory
	FreeImage_Unload(m_Image);

	return true;
}

// Gets the internal ImageFormat from the FreeImage image format
Engine::ImageResource::ImageFormat Engine::ImageResource::GetImageFormat(FREE_IMAGE_FORMAT freeImageImageFormat)
{
	switch (freeImageImageFormat)
	{
	case FREE_IMAGE_FORMAT::FIF_BMP: return ImageFormat::RGB;
	case FREE_IMAGE_FORMAT::FIF_GIF: return ImageFormat::RGB;
	case FREE_IMAGE_FORMAT::FIF_JPEG: return ImageFormat::RGB;
	case FREE_IMAGE_FORMAT::FIF_J2K: return ImageFormat::RGB;
	case FREE_IMAGE_FORMAT::FIF_PBM: return ImageFormat::MONOCHROME;
	case FREE_IMAGE_FORMAT::FIF_PGM: return ImageFormat::GRAYSCALE;
	case FREE_IMAGE_FORMAT::FIF_PPM: return ImageFormat::RGB;
	case FREE_IMAGE_FORMAT::FIF_PNG: return ImageFormat::RGBA;
	case FREE_IMAGE_FORMAT::FIF_TARGA: return ImageFormat::RGB;
	case FREE_IMAGE_FORMAT::FIF_TIFF: return ImageFormat::RGB;
	default: return ImageFormat::INVALID;
	}
}

////////////////////////////////////////////////////////////////
// Image metadata											  //
////////////////////////////////////////////////////////////////

// Gets the dimensions of the image
Engine::i2 Engine::ImageResource::GetDimensions()
{
	return i2((int)FreeImage_GetWidth(m_Image), (int)FreeImage_GetHeight(m_Image));
}

////////////////////////////////////////////////////////////////
// Texture generation										  //
////////////////////////////////////////////////////////////////

// Returns the ID of the OpenGL texture buffer associated to this image
GLuint Engine::ImageResource::GetTexture()
{
	// If the image was changed since the last upload to the GPU, reupload it
	if (m_Dirty != DirtyType::CLEAN) { UploadTexture(); }
	return m_TextureID;
}

// Uploads the texture to the GPU (called automatically, but can be explicitely called to force an upload at a desired point in time)
void Engine::ImageResource::UploadTexture()
{
	// Get the image bit-data and metadata
	void* imageData = (void*)FreeImage_GetBits(m_Image);
	i2 dim = GetDimensions();

	// Bind the texture buffer and set sampling parameters
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Determine the texture buffer format based on the image format and upoad the data to the GPU
	switch (m_ImageFormat)
	{
	case ImageFormat::MONOCHROME: 
		if (m_Dirty == DirtyType::DIRTY_VALUES) { glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dim.x(), dim.y(), GL_RED, GL_UNSIGNED_BYTE, imageData); }
		if (m_Dirty == DirtyType::DIRTY_SIZE_AND_VALUES) { glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, dim.x(), dim.y(), 0, GL_RED, GL_UNSIGNED_BYTE, imageData); }
		break;
	case ImageFormat::GRAYSCALE: 
		if (m_Dirty == DirtyType::DIRTY_VALUES) { glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dim.x(), dim.y(), GL_RED, GL_UNSIGNED_BYTE, imageData); }
		if (m_Dirty == DirtyType::DIRTY_SIZE_AND_VALUES) { glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, dim.x(), dim.y(), 0, GL_RED, GL_UNSIGNED_BYTE, imageData); }
		break;
	case ImageFormat::RGB: 
		if (m_Dirty == DirtyType::DIRTY_VALUES) { glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dim.x(), dim.y(), GL_RED, GL_UNSIGNED_BYTE, imageData); }
		if (m_Dirty == DirtyType::DIRTY_SIZE_AND_VALUES) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, dim.x(), dim.y(), 0, GL_BGR, GL_UNSIGNED_BYTE, imageData); }
		break;
	case ImageFormat::RGBA: 
		if (m_Dirty == DirtyType::DIRTY_VALUES) { glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dim.x(), dim.y(), GL_RED, GL_UNSIGNED_BYTE, imageData); }
		if (m_Dirty == DirtyType::DIRTY_SIZE_AND_VALUES) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, dim.x(), dim.y(), 0, GL_BGRA, GL_UNSIGNED_BYTE, imageData); }
		break;
	}

	// Reset the dirty flag
	m_Dirty = DirtyType::CLEAN;
}

////////////////////////////////////////////////////////////////
// Image manipulation										  //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////// Rotations

// Rotates the image (without affecting the size of the image)
Engine::ImageResource& Engine::ImageResource::Rotate(RotationAngle angle)
{
	double angleDegrees;
	switch (angle)
	{
	case RotationAngle::CW_90: angleDegrees = 90.0; break;
	case RotationAngle::CW_180: angleDegrees = 180.0; break;
	case RotationAngle::CW_270: angleDegrees = 270.0; break;
	case RotationAngle::CCW_90: angleDegrees = -90.0; break;
	case RotationAngle::CCW_180: angleDegrees = -180.0; break;
	case RotationAngle::CCW_270: angleDegrees = -270.0; break;
	default: angleDegrees = 0.0; 
	}
	FIBITMAP* newImage = FreeImage_Rotate(m_Image, angleDegrees);

	FreeImage_Unload(m_Image);
	m_Image = newImage;

	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}

// Rotates the image (and resizes the image)
Engine::ImageResource& Engine::ImageResource::Rotate(double angle)
{
	f2 dim = GetDimensions();
	FIBITMAP* newImage = FreeImage_RotateEx(m_Image, angle, 0, 0, dim.x() / 2.0, dim.y() / 2.0, true);
	FreeImage_Unload(m_Image);
	m_Image = newImage;

	m_Dirty = DirtyType::DIRTY_SIZE_AND_VALUES;
	return *this;
}

// Rotates the image (and resizes the image)
Engine::ImageResource& Engine::ImageResource::Rotate(double angle, f2 origin)
{
	FIBITMAP* newImage = FreeImage_RotateEx(m_Image, angle, 0, 0, origin.x(), origin.y(), true);
	FreeImage_Unload(m_Image);
	m_Image = newImage;

	m_Dirty = DirtyType::DIRTY_SIZE_AND_VALUES;
	return *this;
}

// Flips the image horizontally
Engine::ImageResource& Engine::ImageResource::FlipHorizontal()
{
	FreeImage_FlipHorizontal(m_Image);
	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}

// Flips the image Vertically
Engine::ImageResource& Engine::ImageResource::FlipVertical()
{
	FreeImage_FlipVertical(m_Image);
	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}

//////////////////////////////////////////////////////// Scaling

// Rescales the image to fit the specified dimensions
Engine::ImageResource& Engine::ImageResource::Rescale(i2 dstDimensions, RescalePolicy policy, ResampleFilter filter)
{
	FIBITMAP* newImage;
	i2 currDimensions = GetDimensions();

	switch (policy)
	{
	case RescalePolicy::MATCH_DIMENSIONS:
		newImage = FreeImage_Rescale(m_Image, dstDimensions.x(), dstDimensions.y(), GetFilter(filter));
		break;
	case RescalePolicy::FIT_INSIDE_DIMENSIONS:
	{
		double widthRatio = (double)dstDimensions.x() / (double)currDimensions.x();
		double heightRatio = (double)dstDimensions.x() / (double)currDimensions.x();
		double ratio = fmin(widthRatio, heightRatio);
		newImage = FreeImage_Rescale(m_Image, currDimensions.x() * ratio, currDimensions.y() * ratio, GetFilter(filter));
	}
		break;
	case RescalePolicy::COVER_DIMENSIONS:
	{
		double widthRatio = (double)dstDimensions.x() / (double)currDimensions.x();
		double heightRatio = (double)dstDimensions.x() / (double)currDimensions.x();
		double ratio = fmax(widthRatio, heightRatio);
		newImage = FreeImage_Rescale(m_Image, currDimensions.x() * ratio, currDimensions.y() * ratio, GetFilter(filter));
	}
		break;
	}

	m_Dirty = DirtyType::DIRTY_SIZE_AND_VALUES;
	return *this;
}

// Gets the FreeImage resampling filter from the internal ResampleFilter
FREE_IMAGE_FILTER Engine::ImageResource::GetFilter(ResampleFilter filter)
{
	switch (filter)
	{
	case ResampleFilter::NEAREST_NEIGHBOR: return FREE_IMAGE_FILTER::FILTER_BOX;
	case ResampleFilter::BILINEAR: return FREE_IMAGE_FILTER::FILTER_BILINEAR;
	case ResampleFilter::BICUBIC: return FREE_IMAGE_FILTER::FILTER_BICUBIC;
	case ResampleFilter::BSPLINE: return FREE_IMAGE_FILTER::FILTER_BSPLINE;
	case ResampleFilter::CATMULLROM: return FREE_IMAGE_FILTER::FILTER_CATMULLROM;
	case ResampleFilter::LANCZOS: return FREE_IMAGE_FILTER::FILTER_LANCZOS3;
	}
}

/////////////////////////////////////////////// Color adjustment

// Adjusts the gamma of the image
Engine::ImageResource& Engine::ImageResource::AdjustGamma(double gamma)
{
	FreeImage_AdjustGamma(m_Image, gamma);
	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}

// Adjusts the brightness of the image
Engine::ImageResource& Engine::ImageResource::AdjustBrightness(double brightness)
{
	FreeImage_AdjustBrightness(m_Image, brightness);
	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}

// Adjusts the contrast of the image
Engine::ImageResource& Engine::ImageResource::AdjustContrast(double contrast)
{
	FreeImage_AdjustContrast(m_Image, contrast);
	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}

// Inverts the colors of the image
Engine::ImageResource& Engine::ImageResource::InvertColors()
{
	FreeImage_Invert(m_Image);
	m_Dirty = DirtyType::DIRTY_VALUES;
	return *this;
}