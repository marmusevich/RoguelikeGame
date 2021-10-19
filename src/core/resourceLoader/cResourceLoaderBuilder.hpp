#ifndef SCR_CORE_RESOURCRLOADER_CRESOURCELOADERBUILDER_HPP
#define SCR_CORE_RESOURCRLOADER_CRESOURCELOADERBUILDER_HPP

#include "core/resourceLoader/iResourceLoader.hpp"

#include <string>
#include <memory>


namespace NResourceLoader
{
	/** create resource loader XML from file */
	std::shared_ptr<iResourceLoader> getXmlLoaderFromFile(const std::string& fileName);
	/** create resource loader XML from string */
	std::shared_ptr<iResourceLoader> getXmlLoaderFromString(const std::string& xml);

} // namespace NResourceLoader
#endif // SCR_CORE_RESOURCRLOADER_CRESOURCELOADERBUILDER_HPP
