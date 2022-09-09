#ifndef SCR_CORE_RESOURCELOADER_PRIVATE_CXMLRESOURCELOADER_HPP
#define SCR_CORE_RESOURCELOADER_PRIVATE_CXMLRESOURCELOADER_HPP

#include "core/resourceLoader/IResourceLoader.hpp"

#include <tinyxml2/tinyxml2.h>

#include <string>
#include <filesystem>

namespace NResourceLoader
{
/*
	<Resource_tipe_name file_name = "" />
		Resource_tipe_name one from {Texture, Image, Font, Shader, Sound}
		file_name - the path to the resource files is relative to the directory where the 'resource.xml' (THIS)  file is located
		id - ID resource, if not set = file name without extension
*/

class CXmlResourceLoader : public IResourceLoader
{
public:
	CXmlResourceLoader();

	bool setFile(const std::filesystem::path& fileName);
	bool setString(const std::string& xml);

	virtual bool addResources(NResurceManagement::ResourceManager& resourceManager) override;

private:
	tinyxml2::XMLDocument mDoc;
	tinyxml2::XMLError mStatus;
	std::filesystem::path mRootDir;
};

} // namespace NResourceLoader
#endif // SCR_CORE_RESOURCELOADER_PRIVATE_CXMLRESOURCELOADER_HPP
