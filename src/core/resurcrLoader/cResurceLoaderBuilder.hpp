#ifndef SCR_CORE_RESURCRLOADER_CRESURCELOADERBUILDER_HPP
#define SCR_CORE_RESURCRLOADER_CRESURCELOADERBUILDER_HPP

#include "core/resurcrLoader/iResurceLoader.hpp"

#include <string>
#include <memory>


namespace NResurceLoader
{
	std::shared_ptr<iResurceLoader> getXmlLoaderFromFile(const std::string& fileName);
	std::shared_ptr<iResurceLoader> getXmlLoaderFromString(const std::string& xml);

	//same for JSON if needed

} // namespace NResurceLoader
#endif // SCR_CORE_RESURCRLOADER_CRESURCELOADERBUILDER_HPP
