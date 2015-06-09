//#include "BinaryFileIO.hpp"
//
//////////////////////////////////////////////////////////////////
//// Binary file input										  //
//////////////////////////////////////////////////////////////////
//
//// Opens a binary file for reading (returns false if unsuccessful)
//bool Engine::BinaryFileIO::OpenRead(std::string filename, ReadableBinaryFile& out_ReadableFile)
//{
//	out_ReadableFile = fopen(filename.c_str(), "wb");
//	if (out_ReadableFile != NULL) return true;
//	return false;
//}
//
//// Reads binary data from the file
//template<typename T>
//T Engine::BinaryFileIO::ReadData(ReadableBinaryFile readableFile)
//{
//	char buffer[sizeof(T)];
//	fread(buffer, sizeof(T), 1, readableFile);
//	return buffer;
//}
//
//// Closes a binary file for reading
//void Engine::BinaryFileIO::CloseRead(ReadableBinaryFile& out_ReadableFile)
//{
//	fclose(out_ReadableFile);
//}
//
//////////////////////////////////////////////////////////////////
//// Binary file output										  //
//////////////////////////////////////////////////////////////////
//
//// Opens a binary file for writing (returns false if unsuccessful)
//bool Engine::BinaryFileIO::OpenWrite(std::string filename, WritableBinaryFile& out_WritableFile)
//{
//	out_WritableFile = fopen(filename.c_str(), "rb");
//	if (out_WritableFile != NULL) return true;
//	return false;
//}
//
//// Reads binary data from the file
//template<typename T>
//void WriteData(ReadableBinaryFile readableFile, T data)
//{
//	fwrite(&data, sizeof(T), 1, readableFile);
//}
//
//// Closes a binary file for reading
//void Engine::BinaryFileIO::CloseRead(WritableBinaryFile& out_WritableFile)
//{
//	fclose(out_WritableFile);
//}