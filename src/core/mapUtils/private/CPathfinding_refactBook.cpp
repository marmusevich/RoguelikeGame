#include "core/mapUtils/private/CPathfinding_refactBook.hpp"

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




//CPathfinding_refactBook::CPathfinding_refactBook(const sf::Vector2i& mapSize)
//: mMapSize(mapSize)
//{
//
//}

std::list<sf::Vector2u> CPathfinding_refactBook::pathfinding(const sf::Vector2u from, const sf::Vector2u to) const
{
	std::list<sf::Vector2u> ret;
	return ret;
}


//std::list<sf::Vector2f> CPathfinding::pathfinding_refact(const sf::Vector2f from, const sf::Vector2f to) const
//{
//	//#define fn(t) \
//	//std::string{ " [ " } + std::to_string(t.columnIndex) + ", " + std::to_string(t.rowIndex) + " ] " \
//	//+ "parentNode: " + (t.parentNode ? " NULL " : \
//	//	+ " [ " + std::to_string(t.parentNode->columnIndex) + ",  " + std::to_string(t.parentNode->rowIndex) + " ] ")


//	const Tile_PF t{};
//	LOG_DEBUG << "before currentNode = " <<
//		std::string{ " [ " } + std::to_string(t.columnIndex) + ", " + std::to_string(t.rowIndex) + " ] " \
//		+ "parentNode: " + (t.parentNode ? " NULL " : \
//			+ " [ " + std::to_string(t.parentNode->columnIndex) + ",  " + std::to_string(t.parentNode->rowIndex) + " ] ")
//		;




//	// Store the start and goal nodes.
//	const auto fromPos = locationToMapCord(from);
//	const auto toPos = locationToMapCord(to);
//	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
//	if (fromPos == toPos)
//	{
//		return std::list<sf::Vector2f>{};
//	}

//	std::array<std::array<Tile_PF, GRID_WIDTH>, GRID_HEIGHT> grid;

//	// Pre-compute our H cost (estimated cost to goal) for each node.
//	for (int i = 0; i < getSize().x; i++)
//	{
//		for (int j = 0; j < getSize().y; j++)
//		{
//			const auto& cell = m_grid[i][j];
//			auto& node = grid[i][j];

//			node.rowIndex = cell.rowIndex;
//			node.columnIndex = cell.columnIndex;

//			const int heightOffset = abs(cell.rowIndex - toPos.x);
//			const int rowOffset = abs(cell.columnIndex - toPos.y);

//			node.H = heightOffset + rowOffset;
//		}
//	}

//	const Tile_PF startNode{ fromPos };

//	// Create all variables.
//	std::vector<Tile_PF> openList;
//	std::vector<Tile_PF> closedList;
//	std::vector<Tile_PF> pathList;

//	Tile_PF currentNode = startNode;

//	// Add the start node to the open list.
//	openList.push_back(startNode);

//	// While we have values to check in the open list.
//	while (!openList.empty())
//	{
//		// Find the node in the open list with the lowest F value and mark it as current.
//		int lowestF = INT_MAX;

//		//min algoritm ??
//		for (/*const*/auto& tile : openList)
//		{
//			if (tile.F < lowestF)
//			{
//				lowestF = tile.F;

//				LOG_DEBUG << "before currentNode = " << fn(currentNode);
//				currentNode = tile;
//				LOG_DEBUG << "after  currentNode = " << fn(currentNode);
//			}
//		}

//		// Remove the current node from the open list and add it to the closed list.
//		const auto it = std::find(openList.begin(), openList.end(), currentNode);
//		if (it != openList.end())
//		{
//			openList.erase(it);
//		}

//		closedList.push_back(currentNode);

//		// Find all valid adjacent nodes.
//		std::vector<Tile_PF> adjacentTiles;
//		{
//			// Top.
//			if (IsFloor(currentNode.columnIndex, currentNode.rowIndex - 1))
//			{
//				adjacentTiles.push_back(grid[currentNode.columnIndex][currentNode.rowIndex - 1]);
//			}
//			// Right.
//			if (IsFloor(currentNode.columnIndex + 1, currentNode.rowIndex))
//			{
//				adjacentTiles.push_back(grid[currentNode.columnIndex + 1][currentNode.rowIndex]);
//			}
//			// Bottom.
//			if (IsFloor(currentNode.columnIndex, currentNode.rowIndex + 1))
//			{
//				adjacentTiles.push_back(grid[currentNode.columnIndex][currentNode.rowIndex + 1]);
//			}
//			// Left.
//			if (IsFloor(currentNode.columnIndex - 1, currentNode.rowIndex))
//			{
//				adjacentTiles.push_back(grid[currentNode.columnIndex - 1][currentNode.rowIndex]);
//			}
//		}

//		// For all adjacent nodes.
//		for (auto node : adjacentTiles)
//		{
//			// If the node is our goal node.
//			if (node.columnIndex == toPos.x && node.rowIndex == toPos.y)
//			{
//				LOG_DEBUG << "=======================================================";
//				LOG_DEBUG << "";
//				LOG_DEBUG << "OK";


//				// Parent the goal node to current.
//				//node.parentNode.emplace(currentNode);
//				node.parentNode = &currentNode;

//				// Store the current path.
//				//while (node.parentNode.has_value())
//				while (node.parentNode != nullptr)
//				{
//					LOG_DEBUG << "node =             " << fn(node);
//					LOG_DEBUG << "*node.parentNode = " << fn((*node.parentNode));

//					pathList.push_back(node);
//					node = *node.parentNode;

//					if (node == *node.parentNode)
//						break;

//				}

//				// Empty the open list and break out of our for loop.
//				openList.clear();
//				break;
//			}
//			else
//			{
//				// If the node is not in the closed list.
//				if (std::find(closedList.begin(), closedList.end(), node) == closedList.end())
//				{
//					// If the node is not in the open list.
//					if (std::find(openList.begin(), openList.end(), node) == openList.end())
//					{
//						// Add the node to the open list.
//						//openList.push_back(node);

//						// Set the parent of the node to the current node.

//						LOG_DEBUG << "node =        " << fn(node);
//						LOG_DEBUG << "currentNode = " << fn(currentNode);
//						node.parentNode = &currentNode;

//						// Calculate G (total movement cost so far) cost.
//						node.G = currentNode.G + 10;

//						// Calculate the F (total movement cost + heuristic) cost.
//						node.F = node.G + node.H;

//						// Add the node to the open list.
//						openList.push_back(node);

//						LOG_DEBUG << "node =            " << fn(node);
//						LOG_DEBUG << "openList.back() = " << fn((openList.back()));
//					}
//					else
//					{
//						// Check if this path is quicker that the other.
//						int tempG = currentNode.G + 10;

//						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
//						if (tempG < node.G)
//						{
//							// Re-parent node to this one.
//							LOG_DEBUG << "node =        " << fn(node);
//							LOG_DEBUG << "currentNode = " << fn(currentNode);
//							node.parentNode = &currentNode;
//						}
//					}
//				}
//			}
//		}
//	}

	// Store the node locations as the enemies target locations.
	//std::list<sf::Vector2f> ret;
	//for (const auto& tile : pathList)
	//{
	//	ret.push_back(mapCordToLocation(tile.columnIndex, tile.rowIndex));
	//}
	//// Reverse the target position as we read them from goal to origin and we need them the other way around.
	//std::reverse(ret.begin(), ret.end());
	//return ret;





//	return std::list<sf::Vector2f>{};
//}

} // namespace NMapUtils
