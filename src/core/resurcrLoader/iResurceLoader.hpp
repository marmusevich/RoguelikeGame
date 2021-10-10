#ifndef SCR_CORE_RESURCRLOADER_IRESURCELOADER_HPP
#define SCR_CORE_RESURCRLOADER_IRESURCELOADER_HPP

#include "core/manager/ResurceManager.hpp"

namespace NResurceLoader
{
class iResurceLoader
{
public:

	virtual bool addResurce(NResursesManagement::ResurceManager& resurceManager) = 0;
	virtual ~iResurceLoader() = default;
};

} // namespace NResurceLoader
#endif // SCR_CORE_MANAGER_RESURCEMANAGER_HPP
