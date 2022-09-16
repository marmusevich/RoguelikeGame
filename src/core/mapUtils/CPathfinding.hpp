#ifndef SCR_CORE_MAPUTILS_CPATHFINDING_HPP
#define SCR_CORE_MAPUTILS_CPATHFINDING_HPP

#include <list>

#include <SFML/System/Vector2.hpp>

namespace NMapUtils
{

	//pattern STRATEGIA стратегия


/**
* 
*/
class CPathfinding
{
public:
	explicit CPathfinding(const sf::Vector2i& mapSize);

	std::list<sf::Vector2f> pathfinding(const sf::Vector2f from, const sf::Vector2f to) const;

private:

	std::list<sf::Vector2f> pathfinding_fromBook(const sf::Vector2f from, const sf::Vector2f to) const;
	std::list<sf::Vector2f> pathfinding_refact(const sf::Vector2f from, const sf::Vector2f to) const;

	const sf::Vector2i mMapSize;
};

} // namespace NMapUtils
#endif // SCR_CORE_MAPUTILS_CPATHFINDING_HPP
