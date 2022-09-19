#include "core/resourceLoader/private/CXmlResourceLoader.hpp"

#include <plog/Log.h>

namespace NResourceLoader
{

CXmlResourceLoader::CXmlResourceLoader()
: mDoc()
, mStatus(tinyxml2::XMLError::XML_ERROR_PARSING)
, mRootDir()
{

}
	
bool CXmlResourceLoader::setFile(const std::filesystem::path& fileName)
{
	namespace fs = std::filesystem;
	if (fileName.is_relative())
	{
		mRootDir = fs::absolute(fs::current_path()) / fileName.parent_path();
	}
	else
	{
		mRootDir = fileName.parent_path();
	}

	mDoc.ClearError();
	mDoc.Clear();
	mStatus = tinyxml2::XMLError::XML_SUCCESS;
	mStatus = mDoc.LoadFile(fileName.string().c_str());

	const bool ret = mStatus == tinyxml2::XMLError::XML_SUCCESS;
	if (!ret)
	{
		LOG_FATAL << "CXmlResourceLoader::setFile - Can't parse file '" + fileName.string() + "' with error #"
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr();

		throw std::runtime_error("CXmlResourceLoader::setFile - Can't parse file '" + fileName.string() + "' with error #"
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
		LOG_FATAL << "CXmlResourceLoader::setString - Can't parse string with error #"
			+ std::to_string(mStatus) + " : " + mDoc.ErrorStr();

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
bool addResourcefromNode(const tinyxml2::XMLElement* root, const char* elementName, const std::filesystem::path& rootPath, TResourceHolder& holder)
{
	namespace fs = std::filesystem;

	for (auto element = root->FirstChildElement(elementName); element != nullptr; element = element->NextSiblingElement(elementName))
	{
		const auto fileName = element->Attribute(NXMLToken::FILE_NAME);
		const auto id = element->Attribute(NXMLToken::ID);
		if (!fileName)
		{
			LOG_ERROR << "Parset XML element is NULL";
			return false;
		}

		const auto fullFileName = rootPath / fileName;
		if(!fs::exists(fullFileName))
		{
			LOG_ERROR << "File is not exist :" << fullFileName;
			//todo log ? if file res is not exist
			return false;
		}

		if (!id || id== "")
		{
			(void)holder->loadFromFile(fullFileName.stem().string(), fullFileName.generic_string()); // ignore result
		}
		else
		{
			(void)holder->loadFromFile(std::string{ id }, fullFileName.generic_string()); // ignore result
		}
	}
	return true;
}
}

bool CXmlResourceLoader::addResources(NResurceManagement::ResourceManager& resourceManager)
{
	if (mStatus != tinyxml2::XMLError::XML_SUCCESS)
	{
		//LOG_ERROR <<
		return false;
	}
	
	auto root = mDoc.FirstChildElement(NXMLToken::ROOT);
	bool ret = root != nullptr;
	ret = ret && addResourcefromNode(root, NXMLToken::FONT, mRootDir, resourceManager.mFonts);
	ret = ret && addResourcefromNode(root, NXMLToken::TEXTURE, mRootDir, resourceManager.mTexture);
	ret = ret && addResourcefromNode(root, NXMLToken::IMAGE, mRootDir, resourceManager.mImage);
	ret = ret && addResourcefromNode(root, NXMLToken::SOUND, mRootDir, resourceManager.mSound);
	//ret = ret && addResourcefromNode(root, NXMLToken::SHADER, resourceManager.mShader);
	return ret;
}
	
} // namespace NResourceLoader

