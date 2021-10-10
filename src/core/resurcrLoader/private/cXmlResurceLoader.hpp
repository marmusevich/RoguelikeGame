#ifndef SCR_CORE_RESURCRLOADER_PRIVATE_CXMLRESURCELOADER_HPP
#define SCR_CORE_RESURCRLOADER_PRIVATE_CXMLRESURCELOADER_HPP

#include "core/resurcrLoader/iResurceLoader.hpp"

#include <tinyxml2/tinyxml2.h>

#include <string>

namespace NResurceLoader
{
	
class cXmlResurceLoader : public iResurceLoader
{
public:
	cXmlResurceLoader();

	bool setFile(const std::string& fileName);
	bool setxmlString(const std::string& xml);

	virtual bool addResurce(NResursesManagement::ResurceManager& resurceManager) override;

private:
	tinyxml2::XMLDocument mDoc;
	tinyxml2::XMLError mStatus;
};

} // namespace NResurceLoader
#endif // SCR_CORE_RESURCRLOADER_PRIVATE_CXMLRESURCELOADER_HPP
