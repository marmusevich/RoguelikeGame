#include "core/resurcrLoader/cResurceLoaderBuilder.hpp"

#include "core/resurcrLoader/private/cXmlResurceLoader.hpp"

namespace NResurceLoader
{

std::shared_ptr<iResurceLoader> getXmlLoaderFromFile(const std::string& fileName)
{
	auto loader = std::make_shared<cXmlResurceLoader>();
	
	if (loader->setFile(fileName))
	{
		return loader;
	}
	return nullptr;
}

std::shared_ptr<iResurceLoader> getXmlLoaderFromString(const std::string& xml)
{
	auto loader = std::make_shared<cXmlResurceLoader>();

	if (loader->setxmlString(xml))
	{
		return loader;
	}
	return nullptr;
}

} // namespace NResurceLoader

