#include "core/resourceLoader/cResourceLoaderBuilder.hpp"

#include "core/resourceLoader/private/cXmlResourceLoader.hpp"


namespace NResourceLoader
{

std::shared_ptr<iResourceLoader> getXmlLoaderFromFile(const std::string& fileName)
{
	auto loader = std::make_shared<cXmlResourceLoader>();
	
	if (loader->setFile(fileName))
	{
		return loader;
	}
	return nullptr;
}

std::shared_ptr<iResourceLoader> getXmlLoaderFromString(const std::string& xml)
{
	auto loader = std::make_shared<cXmlResourceLoader>();

	if (loader->setString(xml))
	{
		return loader;
	}
	return nullptr;
}


} // namespace NResurceLoader
