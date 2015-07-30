#include "PathConfig.hpp"

/**************************************************************/
/* Path getting and setting                                   */
/**************************************************************/

// Gets a configured path by pathname
bool Engine::PathConfig::GetPath(const std::string& pathName, std::string& out_Path)
{
	// Load if not loaded yet
	if (!m_Loaded)
	{
		LoadPathConfigFile();
	}

	if (m_PathMap.count(pathName) == 0)
	{
		// Unknown pathname
		return false;
	}
	
	// Known pathname
	out_Path = m_PathMap[pathName][0];
	return true;
}

// Sets the specified path
void Engine::PathConfig::SetPath(const std::string& pathName, const std::string& path)
{
	// Load if not loaded yet
	if (!m_Loaded)
	{
		LoadPathConfigFile();
	}

	// Set the path
	if (m_PathMap.count(pathName) == 0)
	{
		// New pathname
		std::vector<std::string> pathParam;
		pathParam.push_back(path);
		m_PathMap.insert(std::pair<std::string, std::vector<std::string>>(pathName, pathParam));
	}
	else
	{
		// Existing pathname
		m_PathMap[pathName][0] = path;
	}

	// Persist changes
	ParameterFileIO::WriteFile("PathConfig.txt", m_PathMap);
}

// Whether or not the path config file was loaded
bool Engine::PathConfig::m_Loaded = false;

// Loads the path config file, or creates a new one if it does not exist yet
void Engine::PathConfig::LoadPathConfigFile()
{
	if (ParameterFileIO::FileExists("PathConfig.txt"))
	{
		ParameterFileIO::ReadFile("PathConfig.txt", m_PathMap);
		if (SetDefaultPaths())
		{
			ParameterFileIO::WriteFile("PathConfig.txt", m_PathMap);
		}
	}
	else
	{
		SetDefaultPaths();
		ParameterFileIO::WriteFile("PathConfig.txt", m_PathMap);
	}

	m_Loaded = true;
}

// Sets default paths in the path config
bool Engine::PathConfig::SetDefaultPaths()
{
	bool pathsAdded = false;

	pathsAdded |= SetPathIfNotExistsLocally("images", "../resources/images/");
	pathsAdded |= SetPathIfNotExistsLocally("spritesheets", "../resources/spritesheets/");
	pathsAdded |= SetPathIfNotExistsLocally("bitmapfonts", "../resources/bitmapfonts/");
	pathsAdded |= SetPathIfNotExistsLocally("shaders", "../shaders/");

	return pathsAdded;
}

// Sets a path value if it does not exist yet
bool Engine::PathConfig::SetPathIfNotExistsLocally(const std::string& pathName, const std::string& path)
{
	if (m_PathMap.count(pathName) == 0)
	{
		std::vector<std::string> pathParam;
		pathParam.push_back(path);
		m_PathMap.insert(std::pair<std::string, std::vector<std::string>>(pathName, pathParam));
		return true;
	}

	return false;
}

// Holds all paths
Engine::ParameterMap Engine::PathConfig::m_PathMap;