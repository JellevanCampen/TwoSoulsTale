#pragma once
#ifndef ENGINE_COMMON_UTILITY_PARAMETERFILEIO_H
#define ENGINE_COMMON_UTILITY_PARAMETERFILEIO_H

#include <unordered_map> // For passing the parameters from a file
#include <vector> // For listing parameter values
#include <string> // For representing parameter names and values

namespace Engine
{
	typedef std::unordered_map<std::string, std::vector<std::string>> ParameterMap;

	/*  Parses a text file into a key-value pairs, where one key can be associated with one or more string values.
	 *		- Expected file format:
	 *			parameter one:
	 *			\t	value one
	 *			\t  value two
	 *			parameter two:
	 *			\t  value three
	 *			\t	value four
	 */
	class ParameterFileIO
	{

	public:

		// Checks whether a file exists
		static bool FileExists(std::string filename);

		////////////////////////////////////////////////////////////////
		// Parameter file parsing                                     //
		////////////////////////////////////////////////////////////////

		// Parses a text file into a list parameters names and values
		static bool ReadFile(std::string filename, 
			ParameterMap& out_Parameters);

		// Writss a ParameterMap to a file
		static bool WriteFile(std::string filename, const ParameterMap& parameters);

	};
}

#endif