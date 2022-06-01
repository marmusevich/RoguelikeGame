#include "core/resourceLoader/CResourceLoaderBuilder.hpp"

#include "core/resourceLoader/private/CXmlResourceLoader.hpp"


namespace NResourceLoader
{

std::shared_ptr<IResourceLoader> getXmlLoaderFromFile(const std::string& fileName)
{
	auto loader = std::make_shared<CXmlResourceLoader>();
	
	if (loader->setFile(fileName))
	{
		return loader;
	}
	return nullptr;
}

std::shared_ptr<IResourceLoader> getXmlLoaderFromString(const std::string& xml)
{
	auto loader = std::make_shared<CXmlResourceLoader>();

	if (loader->setString(xml))
	{
		return loader;
	}
	return nullptr;
}


} // namespace NResurceLoader

