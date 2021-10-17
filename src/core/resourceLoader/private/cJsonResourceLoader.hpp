#ifndef SCR_CORE_RESOURCELOADER_PRIVATE_CJSONRESOURCELOADER_HPP
#define SCR_CORE_RESOURCELOADER_PRIVATE_CJSONRESOURCELOADER_HPP

#include "core/resourceLoader/iResourceLoader.hpp"

#include <nlohmann_json/json.hpp>

#include <string>

namespace NResourceLoader
{
	
/**
* TODO invistigate :
* error handing, how disable exception and use "pure-C" aproucn
* develop format json file
* 
* https://github.com/nlohmann/json
* https://json.nlohmann.me/features/macros/
* https://stackoverflow.com/questions/50980563/c-nlohmann-json-get-name-of-array
* 
*
*/


class [[deprecated("this is NOT impliment !!!!!")]] cJsonResourceLoader : public iResourceLoader
{
public:
	cJsonResourceLoader();

	bool setFile(const std::string& fileName);
	bool setString(const std::string& json);

	virtual bool addResource(NResurceManagement::ResourceManager& resourceManager) override;

private:
	nlohmann::json  mDoc;
	bool mStatus;
};


} // namespace NResourceLoader
#endif // SCR_CORE_RESOURCELOADER_PRIVATE_CJSONRESOURCELOADER_HPP
