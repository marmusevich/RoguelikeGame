#include "core/resourceLoader/private/CXmlResourceLoader.hpp"

namespace NResourceLoader
{

CXmlResourceLoader::CXmlResourceLoader()
: mDoc()
, mStatus(tinyxml2::XMLError::XML_ERROR_PARSING)
{

}
	
bool CXmlResourceLoader::setFile(const std::string& fileName)
{
	mDoc.ClearError();
	mDoc.Clear();
	mStatus = tinyxml2::XMLError::XML_SUCCESS;
	mStatus = mDoc.LoadFile(fileName.c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		//LOG
		throw std::runtime_error("CXmlResourceLoader::setFile - Can't parse file '" + fileName + "' with error #" 
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return ret;
}

bool CXmlResourceLoader::setString(const std::string& xml)
{
	mDoc.ClearError();
	mDoc.Clear();
	mStatus = mDoc.Parse(xml.c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		//LOG
		throw std::runtime_error("CXmlResourceLoader::setString - Can't parse string with error #"
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return ret;
}
	
namespace
{

namespace NXMLToken
{
	//xml elements
	const char* ROOT = "Resurces";
	const char* TEXTURE = "Texture";
	const char* IMAGE = "Image";
	const char* FONT = "Font";
	const char* SHADER = "Shader";
	const char* SOUND = "Sound";

	//xml atributes
	const char* FILE_NAME = "file_name";
	const char* ID = "id";
}

template <typename TResourceHolder>
bool addResourcefromNode(const tinyxml2::XMLElement* root, const char* elementName, TResourceHolder& holder)
{
	bool ret = true;

	for (auto element = root->FirstChildElement(elementName); ret && element != nullptr; element = element->NextSiblingElement(elementName))
	{
		const auto fn = element->Attribute(NXMLToken::FILE_NAME);
		const auto id = element->Attribute(NXMLToken::ID);

		ret = fn != nullptr && id != nullptr;
		if (ret)
		{
			static_cast<void>( holder->loadFromFile(id, fn) ); // ignore result
		}
	}
	return ret;
}
}

bool CXmlResourceLoader::addResources(NResurceManagement::ResourceManager& resourceManager)
{
	if (mStatus != tinyxml2::XMLError::XML_SUCCESS)
	{
		return false;
	}
	
	auto root = mDoc.FirstChildElement(NXMLToken::ROOT);
	bool ret = root != nullptr;
	ret = ret && addResourcefromNode(root, NXMLToken::FONT, resourceManager.mFonts);
	ret = ret && addResourcefromNode(root, NXMLToken::TEXTURE, resourceManager.mTexture);
	ret = ret && addResourcefromNode(root, NXMLToken::IMAGE, resourceManager.mImage);
	ret = ret && addResourcefromNode(root, NXMLToken::SOUND, resourceManager.mSound);
	//ret = ret && addResourcefromNode(root, NXMLToken::SHADER, resourceManager.mShader);
	return ret;
}
	
} // namespace NResourceLoader

