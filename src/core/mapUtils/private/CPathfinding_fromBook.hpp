#ifndef SCR_CORE_MAPUTILS_PRIVATE_CPATHFINDING_FROMBOOK_HPP
#define SCR_CORE_MAPUTILS_PRIVATE_CPATHFINDING_FROMBOOK_HPP

#include "core/mapUtils/IPathfinding.hpp"
#include "core/mapUtils/types.hpp"

#include <vector>

namespace NMapUtils
{
//fwd 
struct CPathfindingBuilder;


/**
* 
*/
class CPathfinding_fromBook : public IPathfinding
{
public:
	std::list<sf::Vector2u> pathfinding(const sf::Vector2u from, const sf::Vector2u to) const override;

private:
	friend struct NMapUtils::CPathfindingBuilder;
	
	struct Tile
	{
		eTILE_TYPE type;					// The type of tile this is.
		uint32_t columnIndex;				// The column index of the tile.
		uint32_t rowIndex;					// The row index of the tile.
		//for path finding
		int H; //uint32_t ??								// Heuristic / movement cost to goal.
		int G; //uint32_t ??								// Movement cost. (Total of entire path)
		int F; //uint32_t ??								// Estimated cost for full path. (G + H)
		Tile* parentNode;					// Node to reach this node.
	};

	explicit CPathfinding_fromBook(const sf::Vector2u& mapSize);

	Tile* getTile(const uint32_t columnIndex, const uint32_t rowIndex);

	std::list<sf::Vector2u> pathfinding(const sf::Vector2u from, const sf::Vector2u to);

	void resetMap();

	const sf::Vector2u mMapSize;
	std::vector<std::vector<Tile>> mMap;
};

} // namespace NMapUtils
#endif // SCR_CORE_MAPUTILS_PRIVATE_CPATHFINDING_FROMBOOK_HPP
