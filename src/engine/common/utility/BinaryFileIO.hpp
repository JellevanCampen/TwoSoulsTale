//#pragma once
//#ifndef ENGINE_COMMON_UTILITY_BINARYFILEIO_H
//#define ENGINE_COMMON_UTILITY_BINARYFILEIO_H
//
//#include <string> // For representing image file names
//
//namespace Engine{
//
//	// Typedef for binary file handle
//	typedef FILE* ReadableBinaryFile;
//	typedef FILE* WritableBinaryFile;
//
//	class BinaryFileIO{
//
//	public:
//
//		////////////////////////////////////////////////////////////////
//		// Binary file input										  //
//		////////////////////////////////////////////////////////////////
//
//		// Opens a binary file for reading (returns false if unsuccessful)
//		static bool OpenRead(std::string filename, ReadableBinaryFile& out_ReadableFile);
//
//		// Reads binary data from the file
//		template<typename T>
//		static T ReadData(ReadableBinaryFile readableFile);
//
//		// Closes a binary file for reading
//		static void CloseRead(ReadableBinaryFile& out_ReadableFile);
//
//		////////////////////////////////////////////////////////////////
//		// Binary file output										  //
//		////////////////////////////////////////////////////////////////
//
//		// Opens a binary file for writing (returns false if unsuccessful)
//		static bool OpenWrite(std::string filename, WritableBinaryFile& out_WritableFile);
//
//		// Reads binary data from the file
//		template<typename T>
//		/static void WriteData(ReadableBinaryFile readableFile, T data);
//
//		// Closes a binary file for reading
//		static void CloseRead(WritableBinaryFile& out_WritableFile);
//
//	};
//}
//
//#endif
