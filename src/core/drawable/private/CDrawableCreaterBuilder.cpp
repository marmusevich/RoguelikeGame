#include "core/drawable/CDrawableCreaterBuilder.hpp"

#include "core/drawable/private/CDirectedDrawableCreater.hpp"
#include "core/drawable/private/CXmlDrawableCreater.hpp"

namespace NDrawableCreater
{

Ptr getDrawableCreaterFromXmlFile(const std::string& fileName)
{
	auto loader = std::make_shared<CXmlDrawableCreater>();

	if (loader->setFile(fileName))
	{
		return loader;
	}
	return nullptr;
}

Ptr getDrawableCreaterFromXmlString(const std::string& xml)
{
	auto loader = std::make_shared<CXmlDrawableCreater>();

	if (loader->setString(xml))
	{
		return loader;
	}
	return nullptr;
}

Ptr getDirectedDrawableCreater()
{
	return std::make_shared<CDirectedDrawableCreater>();;
}

} // namespace NDrawableCreater
