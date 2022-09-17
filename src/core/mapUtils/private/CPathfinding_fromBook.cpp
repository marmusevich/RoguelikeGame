#include "core/mapUtils/private/CPathfinding_fromBook.hpp"

#include <plog/Log.h>


namespace NMapUtils
{
namespace
{
//	struct Tile_PF
//	{
//		Tile_PF()
//			: columnIndex(0)
//			, rowIndex(0)
//			, H(0)
//			, G(0)
//			, F(0)
//			, parentNode(nullptr)
//		{}
//		explicit Tile_PF(const sf::Vector2i v)
//			: columnIndex(v.x)
//			, rowIndex(v.y)
//			, H(0)
//			, G(0)
//			, F(0)
//			, parentNode(nullptr)
//		{}
//		//eTILE type;							// The type of tile this is.
//		int columnIndex;					// The column index of the tile.
//		int rowIndex;						// The row index of the tile.
//		int H;								// Heuristic / movement cost to goal.
//		int G;								// Movement cost. (Total of entire path)
//		int F;								// Estimated cost for full path. (G + H)
//		//Tile_PF* parentNode;	// Node to reach this node.
//		//std::optional<Tile_PF*> parentNode;	// Node to reach this node.
//		//std::shared_ptr<Tile_PF*> parentNode;	// Node to reach this node.
////try it
//		std::optional<std::reference_wrapper<Tile_PF>> parentNode;
//		inline bool operator==(const Tile_PF& other) const
//		{
//			return columnIndex == other.columnIndex && rowIndex == other.rowIndex;
//		}
//		inline bool operator!=(const Tile_PF& other) const
//		{
//			return !(*this == other);
//		}
//		//Tile_PF&  operator=(const Tile_PF&) = default;
//		//Tile_PF(const Tile_PF&) = default;
//		Tile_PF& operator=(const Tile_PF& other)
//		{
//			columnIndex = other.columnIndex;
//			rowIndex = other.rowIndex;
//			H = other.H;
//			G = other.G;
//			F = other.F;
//			parentNode = other.parentNode;
//			return *this;
//		}
//		Tile_PF(const Tile_PF& other)
//			: columnIndex(other.columnIndex)
//			, rowIndex(other.rowIndex)
//			, H(other.H)
//			, G(other.G)
//			, F(other.F)
//			, parentNode(other.parentNode)
//		{}
//	};

}




CPathfinding_fromBook::CPathfinding_fromBook(const sf::Vector2u& mapSize)
: mMapSize(mapSize)
, mMap()
{

}

std::list<sf::Vector2u> CPathfinding_fromBook::pathfinding(const sf::Vector2u from, const sf::Vector2u to) const
{
	std::list<sf::Vector2u> ret;
	return ret;
}

/*
// Recalculates the enemies path finding.
std::list<sf::Vector2f> pathfinding_fromBook(const sf::Vector2f from, const sf::Vector2f to) const
void Enemy::UpdatePathfinding(const Level& level, sf::Vector2f playerPosition)
{
	//TODO ReFACT THIS UGLU
	// mast be util, find from - to


	// Create all variables.
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	// Reset all nodes.
	//WA const_cast
	const_cast<Level&>(level).ResetNodes();
	auto getTileV_WA = [&level](const sf::Vector2f& position) -> Tile*
	{
		return const_cast<Level&>(level).GetTile(position);
	};
	auto getTile_WA = [&level](const int columnIndex, const int rowIndex) -> Tile*
	{
		return const_cast<Level&>(level).GetTile(columnIndex, rowIndex);
	};

	// Store the start and goal nodes.
	auto* startNode = getTileV_WA(m_position);
	auto* goalNode = getTileV_WA(playerPosition);

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		// Clear the vector of target positions.
		m_targetPositions.clear();

		// Exit the function.
		return;
	}

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < level.GetSize().x; i++)
	{
		for (int j = 0; j < level.GetSize().y; j++)
		{
			int rowOffset, heightOffset;
			auto node = getTile_WA(i, j); // TODO NOT CHEKED

			heightOffset = abs(node->rowIndex - goalNode->rowIndex);
			rowOffset = abs(node->columnIndex - goalNode->columnIndex);

			node->H = heightOffset + rowOffset;
		}
	}

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		int lowestF = INT_MAX;

		for (Tile* tile : openList)
		{
			if (tile->F < lowestF)
			{
				lowestF = tile->F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		position = std::find(openList.begin(), openList.end(), currentNode);
		if (position != openList.end())
			openList.erase(position);

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile*> adjacentTiles;
		Tile* node;

		// Top.
		node = getTile_WA(currentNode->columnIndex, currentNode->rowIndex - 1);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(getTile_WA(currentNode->columnIndex, currentNode->rowIndex - 1));
		}

		// Right.
		node = getTile_WA(currentNode->columnIndex + 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(getTile_WA(currentNode->columnIndex + 1, currentNode->rowIndex));
		}

		// Bottom.
		node = getTile_WA(currentNode->columnIndex, currentNode->rowIndex + 1);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(getTile_WA(currentNode->columnIndex, currentNode->rowIndex + 1));
		}

		// Left.
		node = getTile_WA(currentNode->columnIndex - 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(getTile_WA(currentNode->columnIndex - 1, currentNode->rowIndex));
		}

		// For all adjacent nodes.
		for (Tile* node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node == goalNode)
			{
				// Parent the goal node to current.
				node->parentNode = currentNode;

				// Store the current path.
				while (node->parentNode != nullptr)
				{
					pathList.push_back(node);
					node = node->parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}
			else
			{
				// If the node is not in the closed list.
				position = std::find(closedList.begin(), closedList.end(), node);
				if (position == closedList.end())
				{
					// If the node is not in the open list.
					position = std::find(openList.begin(), openList.end(), node);
					if (position == openList.end())
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node->parentNode = currentNode;

						// Calculate G (total movement cost so far) cost.
						node->G = currentNode->G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node->F = node->G + node->H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode->G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node->G)
						{
							// Re-parent node to this one.
							node->parentNode = currentNode;
						}
					}
				}
			}
		}
	}

	// Clear the vector of target positions.
	m_targetPositions.clear();

	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		m_targetPositions.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(m_targetPositions.begin(), m_targetPositions.end());

*/

//	return std::list<sf::Vector2f>{};
//}

} // namespace NMapUtils
