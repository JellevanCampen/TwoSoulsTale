#pragma once
#ifndef ENGINE_COMMON_UTILITY_XMLFILEIO_H
#define ENGINE_COMMON_UTILITY_XMLFILEIO_H

#include "tinyxml2\tinyxml2.h" // For reading and writing XML files

#include <string> // For representing file names

namespace Engine{

	// Typedef for XML file handle
	typedef tinyxml2::XMLDocument XMLFile;
	typedef tinyxml2::XMLElement XMLElement;

	class XMLFileIO{

	public:

		////////////////////////////////////////////////////////////////
		// XML file IO												  //
		////////////////////////////////////////////////////////////////

		// Opens an XML file (returns whether successful)
		static bool OpenFile(std::string filename, XMLFile& out_File);

		// Saves an XML file (returns whether successful)
		static bool SaveFile(std::string filename, XMLFile& file);

		// Closes an XML file
		static void CloseFile(XMLFile& file);

		////////////////////////////////////////////////////////////////
		// XML file traversal										  //
		////////////////////////////////////////////////////////////////

		// Gets a top level element of the XML file
		static XMLElement& GetElement(XMLFile& file, std::string childElement);

		// Gets a child element of the specified element
		static XMLElement& GetElement(XMLElement& element, std::string childElement);

		////////////////////////////////////////////////////////////////
		// XML file reading											  //
		////////////////////////////////////////////////////////////////

		// Gets the value of an attribute as a string (returns whether successful)
		static bool GetAttribute(XMLElement& element, std::string attribute, std::string& out_String);

		// Gets the value of an attribute as a signed integer (returns whether successful)
		static bool GetAttributeAsInteger(XMLElement& element, std::string attribute, int& out_Value);

		// Gets the value of an attribute as an unsigned integer (returns whether successful)
		static bool GetAttributeAsUnsignedInteger(XMLElement& element, std::string attribute, unsigned int& out_Value);

		// Gets the value of an attribute as a boolean (returns whether successful)
		static bool GetAttributeAsBoolean(XMLElement& element, std::string attribute, bool& out_Value);

		// Gets the value of an attribute as a double (returns whether successful)
		static bool GetAttributeAsDouble(XMLElement& element, std::string attribute, double& out_Value);

		// Gets the value of an attribute as a float (returns whether successful)
		static bool GetAttributeAsFloat(XMLElement& element, std::string attribute, float& out_Value);

		// Gets the textual content of an element as a string (returns whether successful)
		static bool GetText(XMLElement& element, std::string& out_String);

		// Gets the textual content of an element as an integer (returns whether successful)
		static bool GetTextAsInteger(XMLElement& element, int& out_Value);

		// Gets the textual content of an element as an unsigned integer (returns whether successful)
		static bool GetTextAsUnsignedInteger(XMLElement& element, unsigned int& out_Value);

		// Gets the textual content of an element as a boolean (returns whether successful)
		static bool GetTextAsBoolean(XMLElement& element, bool& out_Value);

		// Gets the textual content of an element as a double (returns whether successful)
		static bool GetTextAsDouble(XMLElement& element, double& out_Value);

		// Gets the textual content of an element as a float (returns whether successful)
		static bool GetTextAsFloat(XMLElement& element, float& out_Value);

		////////////////////////////////////////////////////////////////
		// XML file writing											  //
		////////////////////////////////////////////////////////////////

		// Sets the value of an attribute
		static void SetAttributeValue(XMLElement& element, std::string attribute, std::string value);

		// Sets the textual content of an elements
		static void SetText(XMLElement& element, std::string string);

		// Adds a new top level element to the file (returns the newly created element)
		static XMLElement& AddElement(XMLFile& file, std::string childElement);

		// Adds a new child element to the element (returns the newly created element)
		static XMLElement& AddElement(XMLElement& element, std::string childElement);

		// Deletes a child element of the element
		static void DeleteElement(XMLElement& element, std::string childElement);

		// Deletes an attribute of the element
		static void DeleteAttribute(XMLElement& element, std::string attribute);

	};
}

#endif
