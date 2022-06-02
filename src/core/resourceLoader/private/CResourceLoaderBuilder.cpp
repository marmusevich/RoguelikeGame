#include "core/resourceLoader/CResourceLoaderBuilder.hpp"

#include "core/resourceLoader/private/CXmlResourceLoader.hpp"


namespace NResourceLoader
{

	Ptr getXmlLoaderFromFile(const std::string& fileName)
{
	auto loader = std::make_shared<CXmlResourceLoader>();
	
	if (loader->setFile(fileName))
	{
		return loader;
	}
	return nullptr;
}

Ptr getXmlLoaderFromString(const std::string& xml)
{
	auto loader = std::make_shared<CXmlResourceLoader>();

	if (loader->setString(xml))
	{
		return loader;
	}
	return nullptr;
}


} // namespace NResurceLoader

