#ifndef SCR_CORE_RESOURCRLOADER_CRESOURCELOADERBUILDER_HPP
#define SCR_CORE_RESOURCRLOADER_CRESOURCELOADERBUILDER_HPP

#include "core/resourceLoader/IResourceLoader.hpp"

#include <string>
#include <memory>


namespace NResourceLoader
{
	using Ptr = std::shared_ptr<IResourceLoader>;

	/** create resource loader XML from file */
	Ptr getXmlLoaderFromFile(const std::string& fileName);
	/** create resource loader XML from string */
	Ptr getXmlLoaderFromString(const std::string& xml);

} // namespace NResourceLoader
#endif // SCR_CORE_RESOURCRLOADER_CRESOURCELOADERBUILDER_HPP
