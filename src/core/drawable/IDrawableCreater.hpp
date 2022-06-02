#ifndef SCR_CORE_DRAWABLE_IDRAWABLECREATER_HPP
#define SCR_CORE_DRAWABLE_IDRAWABLECREATER_HPP

#include "core/drawable/IDrawable.hpp"

#include <string>
#include <memory>



namespace NDrawableCreater
{

/**
* creator of object that can paint, i.e. from XML file
*/
class IDrawableCreater
{
public:
	
	;

	/**
	* get drawable obj - to investigate how return -by name and/or - by type
	* \param
	* \return
	*/
	//virtual NDrawable::Ptr getByName(const std::string& name) const;


	virtual ~IDrawableCreater() = default;
};

} // namespace NDrawableCreater
#endif // SCR_CORE_DRAWABLE_IDRAWABLECREATER_HPP
