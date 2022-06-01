#ifndef SCR_CORE_RESOURCELOADER_PRIVATE_CXMLRESOURCELOADER_HPP
#define SCR_CORE_RESOURCELOADER_PRIVATE_CXMLRESOURCELOADER_HPP

#include "core/resourceLoader/IResourceLoader.hpp"

#include <tinyxml2/tinyxml2.h>

#include <string>

namespace NResourceLoader
{
	
class CXmlResourceLoader : public IResourceLoader
{
public:
	CXmlResourceLoader();

	bool setFile(const std::string& fileName);
	bool setString(const std::string& xml);

	virtual bool addResource(NResurceManagement::ResourceManager& resourceManager) override;

private:
	tinyxml2::XMLDocument mDoc;
	tinyxml2::XMLError mStatus;
};

void NewFunction(tinyxml2::XMLElement* root);

} // namespace NResourceLoader
#endif // SCR_CORE_RESOURCELOADER_PRIVATE_CXMLRESOURCELOADER_HPP
