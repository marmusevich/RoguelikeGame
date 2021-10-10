#include "core/resurcrLoader/cResurceLoaderBuilder.hpp"

#include "core/resurcrLoader/private/cXmlResurceLoader.hpp"

#include <memory>


namespace NResurceLoader
{

const iResurceLoader* getXmlLoaderFromFile(const std::string& fileName)
{
	std::unique_ptr<cXmlResurceLoader> reader;
	if (reader->setFile(fileName))
	{
		return reader.release();
	}
	return nullptr;

}
const iResurceLoader* getXmlLoaderFromString(const std::string& xml)
{
	std::unique_ptr<cXmlResurceLoader> reader;
	if (reader->setxmlString(xml))
	{
		return reader.release();
	}
	return nullptr;

}

} // namespace NResurceLoader

