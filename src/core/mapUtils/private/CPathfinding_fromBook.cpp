#include "core/mapUtils/private/CPathfinding_fromBook.hpp"

#include <algorithm>
#include <cmath>

#include <plog/Log.h>

namespace NMapUtils
{
namespace
{

}

CPathfinding_fromBook::CPathfinding_fromBook(const sf::Vector2u& mapSize)
: mMapSize(mapSize)
, mMap()
{
}

std::list<sf::Vector2u> CPathfinding_fromBook::pathfinding(const sf::Vector2u from, const sf::Vector2u to) const
{
	//WA const_cast
	auto& t = const_cast<CPathfinding_fromBook&>(*this);
	return t.pathfinding(from, to);
}

void CPathfinding_fromBook::resetMap()
{
	for (uint32_t columnIndex = 0; columnIndex < mMapSize.x; ++columnIndex)
	{
		for (uint32_t rowIndex = 0; rowIndex < mMapSize.x; ++rowIndex)
		{
			auto& tile = mMap[columnIndex][rowIndex];
			tile.H = 0;
			tile.F = 0;
			tile.G = 0;
			tile.parentNode = nullptr;
		}
	}
}

std::list<sf::Vector2u> CPathfinding_fromBook::pathfinding(const sf::Vector2u from, const sf::Vector2u to)
{
	using Tile = CPathfinding_fromBook::Tile;

	// Store the start and goal nodes.
	Tile* startNode = &mMap[from.x][from.y];
	Tile* goalNode = &mMap[to.x][to.y];

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		return std::list<sf::Vector2u>{};
	}

	resetMap();

	// Create all variables.
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (std::size_t i = 0; i < mMapSize.x; i++)
	{
		for (std::size_t j = 0; j < mMapSize.y; j++)
		{
			uint32_t rowOffset, heightOffset;
			Tile* node = &mMap[i][j]; // TODO NOT CHEKED

			//std.abs
			heightOffset = (node->rowIndex > goalNode->rowIndex) ? (node->rowIndex - goalNode->rowIndex) : (goalNode->rowIndex - node->rowIndex);
			rowOffset = (node->columnIndex > goalNode->columnIndex) ? (node->columnIndex - goalNode->columnIndex) : (goalNode->columnIndex - node->columnIndex);
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
		node = &mMap[currentNode->columnIndex][currentNode->rowIndex - 1];
		if ((node != nullptr) && (node->type == eTILE_TYPE::FLOOR))
		{
			adjacentTiles.push_back(&mMap[currentNode->columnIndex][currentNode->rowIndex - 1]);
		}
		// Right.
		node = &mMap[currentNode->columnIndex + 1][currentNode->rowIndex];
		if ((node != nullptr) && (node->type == eTILE_TYPE::FLOOR))
		{
			adjacentTiles.push_back(&mMap[currentNode->columnIndex + 1][currentNode->rowIndex]);
		}
		// Bottom.
		node = &mMap[currentNode->columnIndex][currentNode->rowIndex + 1];
		if ((node != nullptr) && (node->type == eTILE_TYPE::FLOOR))
		{
			adjacentTiles.push_back(&mMap[currentNode->columnIndex][currentNode->rowIndex + 1]);
		}
		// Left.
		node = &mMap[currentNode->columnIndex - 1][currentNode->rowIndex];
		if ((node != nullptr) && (node->type == eTILE_TYPE::FLOOR))
		{
			adjacentTiles.push_back(&mMap[currentNode->columnIndex - 1][currentNode->rowIndex]);
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

	// 
	std::list<sf::Vector2u> ret;
	//ret.reverse(pathList.size());
	
	LOG_DEBUG << "node count = " << pathList.size();

	 
	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		ret.push_back({ tile->columnIndex, tile->rowIndex });
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(ret.begin(), ret.end());
	return ret;
}

CPathfinding_fromBook::~CPathfinding_fromBook()
{
	LOG_DEBUG << "~CPathfinding_fromBook";
}

} // namespace NMapUtils
