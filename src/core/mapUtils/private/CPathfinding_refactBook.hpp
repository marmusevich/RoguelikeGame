#ifndef SCR_CORE_MAPUTILS_PRIVATE_CPATHFINDING_REFACTBOOK_HPP
#define SCR_CORE_MAPUTILS_PRIVATE_CPATHFINDING_REFACTBOOK_HPP

#include "core/mapUtils/IPathfinding.hpp"


namespace NMapUtils
{

	//pattern STRATEGIA стратегия


/**
* 
*/
class CPathfinding_refactBook : public IPathfinding
{
public:
	//explicit CPathfinding_refactBook(const sf::Vector2u& mapSize);

	std::list<sf::Vector2u> pathfinding(const sf::Vector2u from, const sf::Vector2u to) const override;

private:
	//const sf::Vector2u mMapSize;
};

} // namespace NMapUtils
#endif // SCR_CORE_MAPUTILS_PRIVATE_CPATHFINDING_REFACTBOOK_HPP
