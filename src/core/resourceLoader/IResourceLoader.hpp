#ifndef SCR_CORE_RESOURCELOADER_IRESOURCELOADER_HPP
#define SCR_CORE_RESOURCELOADER_IRESOURCELOADER_HPP

#include "core/manager/ResourceManager.hpp"

namespace NResourceLoader
{

/**
* Parse resource config (file or string) and load resources.
* One string in config present one resource in memory
* (even do the if a resource file is texture atlas, it presents as one resource. Split to sprites will do in other mechanism).
*/
class IResourceLoader
{
public:
	/**
	* Add resource from config.
	* \param resourceManager - where resource will be stored
	* \return true if success	 
	*/
	virtual bool addResources(NResurceManagement::ResourceManager&) = 0;

	virtual ~IResourceLoader() = default;
};

} // namespace NResourceLoader
#endif // SCR_CORE_RESOURCELOADER_IRESOURCELOADER_HPP
