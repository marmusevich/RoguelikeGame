#include "core/drawable/CDrawableCreaterBuilder.hpp"

#include "core/drawable/private/CDirectedDrawableCreater.hpp"
#include "core/drawable/private/CXmlDrawableCreater.hpp"

namespace NDrawableCreater
{
std::shared_ptr<IDrawableCreater> getDrawableCreaterFromXmlFile(const std::string& fileName)
{
	return nullptr;
}

std::shared_ptr<IDrawableCreater> getDrawableCreaterFromXmlString(const std::string& xml)
{
	return nullptr;
}

std::shared_ptr<IDrawableCreater> getDirectedDrawableCreater()
{
	return nullptr;
}

} // namespace NDrawableCreater
