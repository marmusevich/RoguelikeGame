#ifndef SCR_CORE_DRAWABLE_CDRAWABLECREATERBUILDER_HPP
#define SCR_CORE_DRAWABLE_CDRAWABLECREATERBUILDER_HPP

#include "core/drawable/IDrawableCreater.hpp"

#include <string>
#include <memory>

namespace NDrawableCreater
{
	/** make a drawable creater from XML file */
	std::shared_ptr<IDrawableCreater> getDrawableCreaterFromXmlFile(const std::string& fileName);
	/** make a drawable creater from XML string */
	std::shared_ptr<IDrawableCreater> getDrawableCreaterFromXmlString(const std::string& xml);
	/** make a drawable creater that makes directly */
	std::shared_ptr<IDrawableCreater> getDirectedDrawableCreater();

} // namespace NResourceLoader
#endif // SCR_CORE_DRAWABLE_CDRAWABLECREATERBUILDER_HPP
