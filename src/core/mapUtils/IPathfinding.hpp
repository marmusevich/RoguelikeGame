#ifndef SCR_CORE_MAPUTILS_IPATHFINDING_HPP
#define SCR_CORE_MAPUTILS_IPATHFINDING_HPP

#include <list>
#include <SFML/System/Vector2.hpp>

namespace NMapUtils
{
/**
* 
*/
class IPathfinding
{
public:
	//work with tile cord
	virtual std::list<sf::Vector2u> pathfinding(const sf::Vector2u from, const sf::Vector2u to) const = 0;
	
	virtual ~IPathfinding() = default;
};

} // namespace NMapUtils
#endif // SCR_CORE_MAPUTILS_IPATHFINDING_HPP
