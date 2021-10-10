#ifndef SCR_CORE_RESURCRLOADER_CRESURCELOADERBUILDER_HPP
#define SCR_CORE_RESURCRLOADER_CRESURCELOADERBUILDER_HPP

#include "core/resurcrLoader/iResurceLoader.hpp"

#include <string>

namespace NResurceLoader
{
	static const iResurceLoader* getXmlLoaderFromFile(const std::string& fileName);
	static const iResurceLoader* getXmlLoaderFromString(const std::string& xml);

} // namespace NResurceLoader
#endif // SCR_CORE_RESURCRLOADER_CRESURCELOADERBUILDER_HPP
