#include "ParameterFileIO.hpp"

#include <fstream> // For reading parameters from file

// Checks whether a file exists
bool Engine::ParameterFileIO::FileExists(const std::string& filename)
{
	if (FILE* file = fopen(filename.c_str(), "r"))
	{
		fclose(file);
		return true;
	}

	return false;
}

/**************************************************************/
/* Parameter File Parsing                                     */
/**************************************************************/

// Parses a text file into a list parameters names and values
bool Engine::ParameterFileIO::ReadFile(const std::string& filename,
	ParameterMap& out_Parameters)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	std::string line;
	std::vector<std::string>* currValues;

	while (std::getline(file, line))
	{
		// Parameter
		if (line[0] != '\t')
		{
			out_Parameters.insert(std::pair<std::string, std::vector<std::string>>(line.substr(0, line.find(":")), std::vector<std::string>()));
			currValues = &out_Parameters.at(line.substr(0, line.find(":")));
			continue;
		}

		// Value
		currValues->push_back(line.substr(1));
	}

	file.close();
	
	return true;
}

// Writss a ParameterMap to a file
bool Engine::ParameterFileIO::WriteFile(const std::string& filename, const ParameterMap& parameters)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	for (std::pair<std::string, std::vector<std::string>> parameter : parameters)
	{
		file << parameter.first << ":" << std::endl;
		for (std::string value : parameter.second)
		{
			file << "\t" << value << std::endl;
		}
	}

	file.close();

	return true;
}