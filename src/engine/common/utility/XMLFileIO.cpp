#include "XMLFileIO.hpp"

////////////////////////////////////////////////////////////////
// XML file IO												  //
////////////////////////////////////////////////////////////////

// Opens an XML file (returns whether successful)
bool Engine::XMLFileIO::OpenFile(std::string filename, XMLFile& out_XMLFile)
{
	tinyxml2::XMLError error = out_XMLFile.LoadFile(filename.c_str());
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Saves an XML file (returns whether successful)
bool Engine::XMLFileIO::SaveFile(std::string filename, XMLFile& XMLFile)
{
	tinyxml2::XMLError error = XMLFile.SaveFile(filename.c_str());
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Closes an XML file
void Engine::XMLFileIO::CloseFile(XMLFile& XMLFile)
{
	
}

////////////////////////////////////////////////////////////////
// XML file traversal										  //
////////////////////////////////////////////////////////////////

// Gets a top level element of the XML file
Engine::XMLElement Engine::XMLFileIO::GetElement(XMLFile& file, std::string childElement)
{
	return file.FirstChildElement(childElement.c_str());
}

// Gets a child element of the specified element
Engine::XMLElement Engine::XMLFileIO::GetElement(XMLElement element, std::string childElement)
{
	return element->FirstChildElement(childElement.c_str());
}

// Gets all child elements of the specified type of the specified element
size_t Engine::XMLFileIO::GetElements(XMLElement element, std::string childElement, std::vector<XMLElement>& out_Elements)
{
	size_t count = 0;	
	for (auto e = element->FirstChildElement(childElement.c_str()); e; e = e->NextSiblingElement())
	{
		out_Elements.push_back(e);
		count++;
	}

	return count;
}

////////////////////////////////////////////////////////////////
// XML file reading											  //
////////////////////////////////////////////////////////////////

// Gets the value of an attribute as a string (returns whether successful)
bool Engine::XMLFileIO::GetAttribute(XMLElement element, std::string attribute, std::string& out_String)
{
	if (!element->Attribute(attribute.c_str())) return false;
	out_String = element->Attribute(attribute.c_str());
	return true;
}

// Gets the value of an attribute as a signed integer (returns whether successful)
bool Engine::XMLFileIO::GetAttributeAsInteger(XMLElement element, std::string attribute, int& out_Value)
{
	tinyxml2::XMLError error = element->QueryIntAttribute(attribute.c_str(), &out_Value);
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Gets the value of an attribute as an unsigned integer (returns whether successful)
bool Engine::XMLFileIO::GetAttributeAsUnsignedInteger(XMLElement element, std::string attribute, unsigned int& out_Value)
{
	tinyxml2::XMLError error = element->QueryUnsignedAttribute(attribute.c_str(), &out_Value);
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Gets the value of an attribute as a boolean (returns whether successful)
bool Engine::XMLFileIO::GetAttributeAsBoolean(XMLElement element, std::string attribute, bool& out_Value)
{
	tinyxml2::XMLError error = element->QueryBoolAttribute(attribute.c_str(), &out_Value);
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Gets the value of an attribute as a double (returns whether successful)
bool Engine::XMLFileIO::GetAttributeAsDouble(XMLElement element, std::string attribute, double& out_Value)
{
	tinyxml2::XMLError error = element->QueryDoubleAttribute(attribute.c_str(), &out_Value);
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Gets the value of an attribute as a float (returns whether successful)
bool Engine::XMLFileIO::GetAttributeAsFloat(XMLElement element, std::string attribute, float& out_Value)
{
	tinyxml2::XMLError error = element->QueryFloatAttribute(attribute.c_str(), &out_Value);
	if (error == tinyxml2::XMLError::XML_NO_ERROR) return true;
	return false;
}

// Gets the textual content of an element as a string (returns whether successful)
bool Engine::XMLFileIO::GetText(XMLElement element, std::string& out_String)
{
	if (!element->GetText()) return false;
	out_String = element->GetText();
	return true;
}

// Gets the textual content of an element as an integer (returns whether successful)
bool Engine::XMLFileIO::GetTextAsInteger(XMLElement element, int& out_Value)
{
	tinyxml2::XMLError error = element->QueryIntText(&out_Value);
	if (error == tinyxml2::XMLError::XML_SUCCESS) return true;
	return false;
}

// Gets the textual content of an element as an unsigned integer (returns whether successful)
bool Engine::XMLFileIO::GetTextAsUnsignedInteger(XMLElement element, unsigned int& out_Value)
{
	tinyxml2::XMLError error = element->QueryUnsignedText(&out_Value);
	if (error == tinyxml2::XMLError::XML_SUCCESS) return true;
	return false;
}

// Gets the textual content of an element as a boolean (returns whether successful)
bool Engine::XMLFileIO::GetTextAsBoolean(XMLElement element, bool& out_Value)
{
	tinyxml2::XMLError error = element->QueryBoolText(&out_Value);
	if (error == tinyxml2::XMLError::XML_SUCCESS) return true;
	return false;
}

// Gets the textual content of an element as a double (returns whether successful)
bool Engine::XMLFileIO::GetTextAsDouble(XMLElement element, double& out_Value)
{
	tinyxml2::XMLError error = element->QueryDoubleText(&out_Value);
	if (error == tinyxml2::XMLError::XML_SUCCESS) return true;
	return false;
}

// Gets the textual content of an element as a float (returns whether successful)
bool Engine::XMLFileIO::GetTextAsFloat(XMLElement element, float& out_Value)
{
	tinyxml2::XMLError error = element->QueryFloatText(&out_Value);
	if (error == tinyxml2::XMLError::XML_SUCCESS) return true;
	return false;
}

////////////////////////////////////////////////////////////////
// XML file writing											  //
////////////////////////////////////////////////////////////////

// Sets the value of an attribute
void Engine::XMLFileIO::SetAttributeValue(XMLElement element, std::string attribute, std::string value)
{
	element->SetAttribute(attribute.c_str(), value.c_str());
}

// Sets the textual content of an elements
void Engine::XMLFileIO::SetText(XMLElement element, std::string string)
{
	element->SetText(string.c_str());
}

// Adds a new top level element to the file (returns the newly created element)
Engine::XMLElement Engine::XMLFileIO::AddElement(XMLFile& file, std::string childElement)
{
	XMLElement element = file.NewElement(childElement.c_str());
	file.InsertEndChild(element);
	return element;
}

// Adds a new child element to the element (returns the newly created element)
Engine::XMLElement Engine::XMLFileIO::AddElement(XMLElement element, std::string childElement)
{
	XMLElement newElement = element->GetDocument()->NewElement(childElement.c_str());
	element->InsertEndChild(newElement);
	return newElement;
}

// Deletes a top level element
void Engine::XMLFileIO::DeleteElement(XMLFile& file, std::string childElement)
{
	file.DeleteChild(file.FirstChildElement(childElement.c_str()));
}

// Deletes a child element of the element
void Engine::XMLFileIO::DeleteElement(XMLElement element, std::string childElement)
{
	element->DeleteChild(element->FirstChildElement(childElement.c_str()));
}

// Deletes an attribute of the element
void Engine::XMLFileIO::DeleteAttribute(XMLElement element, std::string attribute)
{
	element->DeleteAttribute(attribute.c_str());
}