#include "core/resourceLoader/private/cXmlResourceLoader.hpp"

namespace NResourceLoader
{
	namespace NXMLToken
	{
		//xml elements
		const char* ROOT = "resurces";
		const char* TEXTURE = "texture";
		const char* IMAGE = "image";
		const char* FONT = "font";
		const char* SHADER = "shader";
		const char* SOUND = "sound";
		
		//xml atributes
		const char* FILE_NAME = "file_name";
		const char* ID = "id";
	}

cXmlResourceLoader::cXmlResourceLoader()
: mDoc()
, mStatus(tinyxml2::XMLError::XML_ERROR_PARSING)
{

}
	
bool cXmlResourceLoader::setFile(const std::string& fileName)
{
	mDoc.ClearError();
	mDoc.Clear();
	mStatus = tinyxml2::XMLError::XML_SUCCESS;
	mStatus = mDoc.LoadFile(fileName.c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		//LOG
		throw std::runtime_error("cXmlResourceLoader::setFile - Can't parse file '" + fileName + "' with error #" 
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return ret;
}

bool cXmlResourceLoader::setxmlString(const std::string& xml)
{
	mDoc.ClearError();
	mDoc.Clear();
	mStatus = mDoc.Parse(xml.c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		//LOG
		throw std::runtime_error("cXmlResourceLoader::setFile - Can't parse string with error #"
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return ret;
}
	
bool cXmlResourceLoader::addResource(NResurceManagement::ResourceManager& resourceManager)
{
	if (mStatus != tinyxml2::XMLError::XML_SUCCESS)
	{
		return false;
	}


	//parse and add ress here

	resourceManager.mFonts->loadFromFile("font", "resources/fonts/ADDSBP__.TTF");



	return false;
}
	
} // namespace NResourceLoader

