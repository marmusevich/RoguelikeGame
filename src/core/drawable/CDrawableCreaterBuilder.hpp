#ifndef SCR_CORE_DRAWABLE_CDRAWABLECREATERBUILDER_HPP
#define SCR_CORE_DRAWABLE_CDRAWABLECREATERBUILDER_HPP

#include "core/drawable/IDrawableCreater.hpp"

#include <string>
#include <memory>

namespace NDrawableCreater
{
	using Ptr = std::shared_ptr<IDrawableCreater>;

	/** make a drawable creater from XML file */
	Ptr getDrawableCreaterFromXmlFile(const std::string& fileName);
	/** make a drawable creater from XML string */
	Ptr getDrawableCreaterFromXmlString(const std::string& xml);
	/** make a drawable creater that makes directly */
	Ptr getDirectedDrawableCreater();

} // namespace NResourceLoader
#endif // SCR_CORE_DRAWABLE_CDRAWABLECREATERBUILDER_HPP
