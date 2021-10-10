#include "core/resurcrLoader/private/cXmlResurceLoader.hpp"

namespace NResurceLoader
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
		const char* RECTANGLE = "rectangle";
		
		//xml atributes
		const char* FILE_NAME = "file_name";
		const char* ID = "id";
		const char* RECTANGLE_X = "x";
		const char* RECTANGLE_Y = "y";
		const char* RECTANGLE_W = "w";
		const char* RECTANGLE_H = "h";

	}

cXmlResurceLoader::cXmlResurceLoader()
: mDoc()
, mStatus(tinyxml2::XMLError::XML_ERROR_PARSING)
{

}
	
bool cXmlResurceLoader::setFile(const std::string& fileName)
{
	mDoc.ClearError();
	mDoc.Clear();
	mStatus = tinyxml2::XMLError::XML_SUCCESS;
	mStatus = mDoc.LoadFile(fileName.c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		//LOG
		throw std::runtime_error("cXmlResurceLoader::setFile - Can't parse file '" + fileName + "' with error #" 
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return ret;
}

bool cXmlResurceLoader::setxmlString(const std::string& xml)
{
	mDoc.ClearError();
	mDoc.Clear();
	mStatus = mDoc.Parse(xml.c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		//LOG
		throw std::runtime_error("cXmlResurceLoader::setFile - Can't parse string with error #"
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return ret;
}
	
bool cXmlResurceLoader::addResurce(NResursesManagement::ResurceManager& resurceManager)
{
	if (mStatus != tinyxml2::XMLError::XML_SUCCESS)
	{
		return false;
	}


	//parse and add ress here

	resurceManager.mFonts->loadFromFile("font", "resources/fonts/ADDSBP__.TTF");



	return false;
}
	
} // namespace NResurceLoader

