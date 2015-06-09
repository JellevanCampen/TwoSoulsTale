#pragma once
#ifndef ENGINE_COMMON_UTILITY_PATHCONFIG_H
#define ENGINE_COMMON_UTILITY_PATHCONFIG_H

#include "ParameterFileIO.hpp" // For reading and writing path config files

#include <string> // For representing parameter names and values

namespace Engine
{
	/*  Holds and retrieves the default paths for resources and files.
	*/
	class PathConfig
	{

	public:

		/**************************************************************/
		/* Path getting and setting                                   */
		/**************************************************************/

		// Gets a configured path by pathname
		static bool GetPath(const std::string& pathName, std::string& out_Path);

		// Sets the specified path
		static void SetPath(const std::string& pathName, std::string path);

	private:

		// Whether or not the path config file was loaded
		static bool m_Loaded;

		// Loads the path config file, or creates a new one if it does not exist yet
		static void LoadPathConfigFile();

		// Sets default paths in the path config
		static bool SetDefaultPaths();

		// Sets a path value if it does not exist yet (locally, without persisting to file)
		static bool SetPathIfNotExistsLocally(const std::string& pathName, std::string path);

		// Holds all paths
		static ParameterMap m_PathMap;

	};
}

#endif