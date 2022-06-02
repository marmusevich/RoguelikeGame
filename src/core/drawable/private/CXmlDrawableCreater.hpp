#ifndef SCR_CORE_DRAWABLE_PRIVATE_CXMLDRAWABLECREATER_HPP
#define SCR_CORE_DRAWABLE_PRIVATE_CXMLDRAWABLECREATER_HPP

#include "core/drawable/IDrawableCreater.hpp"


#include <string>


namespace NDrawableCreater
{

/**
* 
*/
class CXmlDrawableCreater : public IDrawableCreater
{
public:

	bool setFile(const std::string& fileName);
	bool setString(const std::string& xml);

	/**
	*
	* \param
	* \return
	*/
	//virtual bool _(_) override;

};

} // namespace NDrawableCreater
#endif // SCR_CORE_DRAWABLE_PRIVATE_CXMLDRAWABLECREATER_HPP
