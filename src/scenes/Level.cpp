#include "scenes/Level.hpp"
#include "utils/MathUtils.hpp"

#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"


Level::Level(const sf::Vector2u screenSize, const Scene& scene)
: m_origin({ 0, 0 })
, m_floorNumber(1)
, m_roomNumber(0)
, m_spawnLocation({ 0.f, 0.f })
, m_doorTileIndices({ 0, 0 })
, m_torches()
, m_textureMatch_WA(static_cast<int>(eTILE::COUNT))
, m_scene(scene)
{
	// Calculate the top left of the grid.
	m_origin.x = (screenSize.x - (GRID_WIDTH * TILE_SIZE));
	m_origin.x /= 2;

	m_origin.y = (screenSize.y - (GRID_HEIGHT * TILE_SIZE));
	m_origin.y /= 2;

	// Store the column and row information for each node.
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			auto cell = &m_grid[i][j];
			cell->columnIndex = i;
			cell->rowIndex = j;
		}
	}

	// Generate a random color and apply it to the level tiles.
	SetColor(RandomColor(100u, 201u));

	m_textureMatch_WA[eTILE::FLOOR_ALT] = "spr_tile_floor_alt";
	m_textureMatch_WA[eTILE::FLOOR] = "spr_tile_floor";
	m_textureMatch_WA[eTILE::WALL_TOP] = "spr_tile_wall_top";
	m_textureMatch_WA[eTILE::WALL_TOP_LEFT] = "spr_tile_wall_top_left";
	m_textureMatch_WA[eTILE::WALL_TOP_RIGHT] = "spr_tile_wall_top_right";
	m_textureMatch_WA[eTILE::WALL_TOP_T] = "spr_tile_wall_top_t";
	m_textureMatch_WA[eTILE::WALL_TOP_END] = "spr_tile_wall_top_end";
	m_textureMatch_WA[eTILE::WALL_BOTTOM_LEFT] = "spr_tile_wall_bottom_left";
	m_textureMatch_WA[eTILE::WALL_BOTTOM_RIGHT] = "spr_tile_wall_bottom_right";
	m_textureMatch_WA[eTILE::WALL_BOTTOM_T] = "spr_tile_wall_bottom_t";
	m_textureMatch_WA[eTILE::WALL_BOTTOM_END] = "spr_tile_wall_bottom_end";
	m_textureMatch_WA[eTILE::WALL_SIDE] = "spr_tile_wall_side";
	m_textureMatch_WA[eTILE::WALL_SIDE_LEFT_T] = "spr_tile_wall_side_left_t";
	m_textureMatch_WA[eTILE::WALL_SIDE_LEFT_END] = "spr_tile_wall_side_left_end";
	m_textureMatch_WA[eTILE::WALL_SIDE_RIGHT_T] = "spr_tile_wall_side_right_t";
	m_textureMatch_WA[eTILE::WALL_SIDE_RIGHT_END] = "spr_tile_wall_side_right_end";
	m_textureMatch_WA[eTILE::WALL_INTERSECTION] = "spr_tile_wall_intersection";
	m_textureMatch_WA[eTILE::WALL_SINGLE] = "spr_tile_wall_single";
	m_textureMatch_WA[eTILE::WALL_ENTRANCE] = "spr_tile_wall_entrance";
	m_textureMatch_WA[eTILE::WALL_DOOR_LOCKED] = "spr_tile_door_locked";
	m_textureMatch_WA[eTILE::WALL_DOOR_UNLOCKED] = "spr_tile_door_unlocked";
	m_textureMatch_WA[eTILE::TORCH] = "spr_torch";
}

// Checks if a given tile is passable
bool Level::IsSolid(const int columnIndex, const int rowIndex) const
{
	// Check that the tile is valid
	if (TileIsValid(columnIndex, rowIndex))
	{
		int tileIndex = static_cast<int>(m_grid[columnIndex][rowIndex].type);
		return (((tileIndex != static_cast<int>(eTILE::FLOOR)) 
			  && (tileIndex != static_cast<int>(eTILE::FLOOR_ALT))) 
			  && (tileIndex != static_cast<int>(eTILE::WALL_DOOR_UNLOCKED)));
	}
	else
		return false;
}

bool Level::IsSolid(const sf::Vector2f position) const
{
	const auto&& [tileColumn, tileRow] = locationToMapCord(position);
	return IsSolid(tileColumn, tileRow);
}

// Returns the position of the level relative to the application window.
sf::Vector2f Level::getPosition() const
{
	return sf::Vector2f(static_cast<float>(m_origin.x), static_cast<float>(m_origin.y));
}

// Returns the id of the given tile in the 2D level array.
eTILE Level::GetTileType(const int columnIndex, const int rowIndex) const
{
	// Check that the parameters are valid.
	if (!TileIsValid(columnIndex, rowIndex))
	{
		return eTILE::EMPTY; // failed
	}
	// Fetch the id.
	return m_grid[columnIndex][rowIndex].type;
}

eTILE Level::GetTileType(const sf::Vector2f position) const
{
	const auto&& [tileColumn, tileRow] = locationToMapCord(position);
	return GetTileType(tileColumn, tileRow);
}


// Sets the id of the given tile in the grid.
void Level::SetTile(int columnIndex, int rowIndex, eTILE tileType)
{
	// Check that the provided tile index is valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT))
	{
		return;
	}

	// check that the sprite index is valid
	if (tileType >= eTILE::COUNT)
	{
		return;
	}

	// change that tiles sprite to the new index
	m_grid[columnIndex][rowIndex].type = tileType;
	m_grid[columnIndex][rowIndex].sprite.setTexture(getTextureByTileTipe_WA(tileType));
}

// Sets the overlay color of the level tiles.
void Level::SetColor(sf::Color tileColor)
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			m_grid[i][j].sprite.setColor(tileColor);
		}
	}
}

// Gets the current floor number.
int Level::GetFloorNumber() const
{
	return m_floorNumber;
}

// Gets the current room number.
int Level::GetRoomNumber() const
{
	return m_roomNumber;
}

// Checks if a given tile is valid.
bool Level::TileIsValid(int column, int row) const
{
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}

// Gets the size of the level in terms of tiles.
sf::Vector2i Level::getSize() const
{
	return sf::Vector2i(GRID_WIDTH, GRID_HEIGHT);
}


// Gets the tile that the position lies on.
Tile* Level::GetTile(const sf::Vector2f position)
{
	const auto&&[tileColumn, tileRow] = locationToMapCord(position);
	return GetTile(tileColumn, tileRow);
}

//const std::optional<Tile> Level::GetTile(int columnIndex, int rowIndex) const
//{
//	if (TileIsValid(columnIndex, rowIndex))
//	{
//		return m_grid[columnIndex][rowIndex];
//	}
//	else
//	{
//		return {};
//	}
//}
Tile* Level::GetTile(int columnIndex, int rowIndex)
{
	if (TileIsValid(columnIndex, rowIndex))
	{
		return &( m_grid[columnIndex][rowIndex]);
	}
	else
	{
		return nullptr;
	}
}

sf::Vector2i Level::locationToMapCord(const sf::Vector2f position) const
{
	// Convert the position to relative to the level grid.
	sf::Vector2i pos{ position };
	pos -= m_origin;
	return pos / TILE_SIZE;
}

// Gets the actual location of a tile in the level.
sf::Vector2f Level::mapCordToLocation(const int columnIndex, const int rowIndex) const
{
	return sf::Vector2f
	{
		static_cast<float>(m_origin.x + (columnIndex * TILE_SIZE) + (TILE_SIZE / 2)),
		static_cast<float>(m_origin.y + (rowIndex * TILE_SIZE) + (TILE_SIZE / 2))
	};
}

sf::Vector2i Level::getRandomSpawnMapPos() const
{
	sf::Vector2i ret{ 0,0 };

	// Loop until we select a floor tile.
	while (!IsFloor(ret.x, ret.y))
	{
		// Generate a random index for the row and column.
		ret.x = Random(GRID_WIDTH - 1);
		ret.y = Random(GRID_HEIGHT - 1);
	}
	return ret;
}

// Returns a valid spawn location from the currently loaded level.
sf::Vector2f Level::GetRandomSpawnLocation() const
{
	const auto&&[rowIndex, columnIndex] = getRandomSpawnMapPos();
	// Convert the tile position to absolute position.
	sf::Vector2f tileLocation(mapCordToLocation(columnIndex, rowIndex));

	// Create a random offset.
	tileLocation.x += Random(10, 30);
	tileLocation.y += Random(10, 30);

	return tileLocation;
}

// Resets the A* data of all tiles.
//void Level::ResetNodes___willBeRemoved()
//{
//	for (int i = 0; i < GRID_WIDTH; i++)
//	{
//		for (int j = 0; j < GRID_HEIGHT; j++)
//		{
//			auto cell = &m_grid[i][j];
//			cell->parentNode = nullptr;
//			cell->H = 0;
//			cell->G = 0;
//			cell->F = 0;
//		}
//	}
//}

// Returns the spawn location for the current level.
sf::Vector2f Level::getPlayerSpawnLocation() const
{
	return m_spawnLocation;
}

// Checks if a given tile is a wall block.
bool Level::IsWall(const int columnIndex, const int rowIndex) const
{
	if (TileIsValid(columnIndex, rowIndex))
	{
		return m_grid[columnIndex][rowIndex].type <= eTILE::WALL_INTERSECTION;
	}
	return false;
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(int columnIndex, int rowIndex) const
{
	if (TileIsValid(columnIndex, rowIndex))
	{
		const Tile& tile = m_grid[columnIndex][rowIndex];
		return IsFloor(tile);
	}

	return false;
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(const Tile& tile) const
{
	return ((tile.type == eTILE::FLOOR) || (tile.type == eTILE::FLOOR_ALT));
}


// Gets the size of the tiles in the level.
int Level::getTileSize() const
{
	return TILE_SIZE;
}





/*
// Recalculates the enemies path finding.
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
}

*/


std::list<sf::Vector2f> Level::pathfinding(const sf::Vector2f from, const sf::Vector2f to)
{
	struct Tile_PF
	{
		Tile_PF()
			: columnIndex(0)
			, rowIndex(0)
			, H(0)
			, G(0)
			, F(0)
			, parentNode(nullptr)
		{}

		explicit Tile_PF(const sf::Vector2i v)
			: columnIndex(v.x)
			, rowIndex(v.y)
			, H(0)
			, G(0)
			, F(0)
			, parentNode(nullptr)
		{}

		//eTILE type;							// The type of tile this is.
		int columnIndex;					// The column index of the tile.
		int rowIndex;						// The row index of the tile.

		int H;								// Heuristic / movement cost to goal.
		int G;								// Movement cost. (Total of entire path)
		int F;								// Estimated cost for full path. (G + H)
		Tile_PF* parentNode;	// Node to reach this node.
		//std::optional<Tile_PF> parentNode;	// Node to reach this node.
	};



	// Store the start and goal nodes.
	const auto fromPos = locationToMapCord(from);
	const auto toPos = locationToMapCord(to);
	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (fromPos == toPos)
	{
		return std::list<sf::Vector2f>{};
	}

	std::array<std::array<Tile_PF, GRID_WIDTH>, GRID_HEIGHT> grid;

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < getSize().x; i++)
	{
		for (int j = 0; j < getSize().y; j++)
		{
			const auto& cell = m_grid[i][j];
			auto& node = grid[i][j];

			node.rowIndex = cell.rowIndex;
			node.columnIndex = cell.columnIndex;

			const int heightOffset = abs(cell.rowIndex - toPos.x);
			const int rowOffset = abs(cell.columnIndex - toPos.y);

			node.H = heightOffset + rowOffset;
		}
	}

	const Tile_PF startNode{ fromPos };


	// Create all variables.
	std::vector<Tile_PF/*&*/> openList;
	std::vector<Tile_PF/*&*/> closedList;
	std::vector<Tile_PF/*&*/> pathList;
	

	Tile_PF/*&*/ currentNode/* = startNode*/;

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		int lowestF = INT_MAX;

		//min algoritm ??
		for (/*const*/auto& tile : openList)
		{
			if (tile.F < lowestF)
			{
				lowestF = tile.F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		const auto it = std::find(openList.begin(), openList.end(), currentNode);
		if (it != openList.end())
		{
			openList.erase(it);
		}

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile_PF> adjacentTiles;
		{
			// Top.
			if ( IsFloor(currentNode.columnIndex, currentNode.rowIndex - 1))
			{
				adjacentTiles.push_back(grid[currentNode.columnIndex][currentNode.rowIndex - 1]);
			}
			// Right.
			if (IsFloor(currentNode.columnIndex + 1, currentNode.rowIndex))
			{
				adjacentTiles.push_back(grid[currentNode.columnIndex + 1][currentNode.rowIndex]);
			}

			// Bottom.
			if (IsFloor(currentNode.columnIndex, currentNode.rowIndex + 1))
			{
				adjacentTiles.push_back(grid[currentNode.columnIndex][currentNode.rowIndex + 1]);
			}

			// Left.
			if (IsFloor(currentNode.columnIndex - 1, currentNode.rowIndex))
			{
				adjacentTiles.push_back(grid[currentNode.columnIndex - 1][currentNode.rowIndex]);
			}
		}

		// For all adjacent nodes.
		for (auto node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node.columnIndex == toPos.x && node.rowIndex == toPos.y)
			{
				// Parent the goal node to current.
				//node.parentNode.emplace(currentNode);
				node.parentNode = &currentNode;

				// Store the current path.
				//while (node.parentNode.has_value())
				while (node.parentNode != nullptr)
				{
					pathList.push_back(node);
					node = *node.parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}
			else
			{
				// If the node is not in the closed list.
				if (std::find(closedList.begin(), closedList.end(), node) == closedList.end())
				{
					// If the node is not in the open list.
					if (std::find(openList.begin(), openList.end(), node) == openList.end())
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node.parentNode = &currentNode;

						// Calculate G (total movement cost so far) cost.
						node.G = currentNode.G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node.F = node.G + node.H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode.G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node.G)
						{
							// Re-parent node to this one.
							node.parentNode = &currentNode;
						}
					}
				}
			}
		}
	}

	// Store the node locations as the enemies target locations.
	std::list<sf::Vector2f> ret;
	for (const auto& tile : pathList)
	{
		ret.push_back(mapCordToLocation(tile.columnIndex, tile.rowIndex));
	}
	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(ret.begin(), ret.end());
	return ret;
}




// Unlocks the door in the level.
void Level::UnlockDoor()
{
	SetTile(m_doorTileIndices.x, m_doorTileIndices.y, eTILE::WALL_DOOR_UNLOCKED);
}

// Create a path between two tiles in the level grid.
void Level::CreatePath(int columnIndex, int rowIndex)
{
	// Store the current tile.
	Tile* currentTile = &m_grid[columnIndex][rowIndex];

	// Create a list of possible directions and sort randomly.
	sf::Vector2i directions[] = { { 0, -2 }, { 2, 0 }, { 0, 2 }, { -2, 0 } };
	//std::random_shuffle(std::begin(directions), std::end(directions));
	RandomShuffle(std::begin(directions), std::end(directions));

	// For each direction.
	for (int i = 0; i < 4; i++)
	{
		// Get the new tile position.
		int dx = currentTile->columnIndex + directions[i].x;
		int dy = currentTile->rowIndex + directions[i].y;

		// If the tile is valid.
		if (TileIsValid(dx, dy))
		{
			// Store the tile.
			Tile* tile = &m_grid[dx][dy];

			// If the tile has not yet been visited.
			if (tile->type == eTILE::EMPTY)
			{
				// Mark the tile as floor.
				tile->type = eTILE::FLOOR;

				tile->sprite.setTexture(getTextureByTileTipe_WA(eTILE::FLOOR));

				// Knock that wall down.
				int ddx = currentTile->columnIndex + (directions[i].x / 2);
				int ddy = currentTile->rowIndex + (directions[i].y / 2);

				Tile* wall = &m_grid[ddx][ddy];
				wall->type = eTILE::FLOOR;
				wall->sprite.setTexture(getTextureByTileTipe_WA(eTILE::FLOOR));

				// Recursively call the function with the new tile.
				CreatePath(dx, dy);
			}
		}
	}
}

// Adds a given number of randomly sized rooms to the level to create some open space.
void Level::CreateRooms(int roomCount)
{
	for (int i = 0; i < roomCount; i++)
	{
		// Generate a room size.
		int roomWidth = Random(1, 2);
		int roomHeight = Random(1, 2);

		// Choose a random starting location. without border
		// ??? std::rand() % (GRID_ - 2) + 1;
		int startI = Random(GRID_WIDTH - 2 - 1) + 1;
		int startY = Random(GRID_HEIGHT - 2 - 1) + 1;

		for (int j = -1; j < roomWidth; j++)
		{
			for (int z = -1; z < roomHeight; z++)
			{
				int newI = startI + j;
				int newY = startY + z;

				// Check if the tile is valid.
				if (TileIsValid(newI, newY))
				{
					// Check if the tile is not on an outer wall.
					if ((newI != 0) && (newI != (GRID_WIDTH - 1)) && (newY != 0) && (newY != (GRID_HEIGHT - 1)))
					{
						m_grid[newI][newY].type = eTILE::FLOOR;
						m_grid[newI][newY].sprite.setTexture(getTextureByTileTipe_WA(eTILE::FLOOR));
					}
				}
			}
		}
	}
}

// Calculates the correct texture for each tile in the level.
void Level::CalculateTextures()
{
	// For each tile in the grid.
	for (int i = 0; i < GRID_WIDTH; ++i)
	{
		for (int j = 0; j < GRID_HEIGHT; ++j)
		{
			// Check that the tile is a wall block.
			if (IsWall(i, j))
			{
				// Calculate bit mask.
				int value = 0;

				// Store the current type as default.
				eTILE type = m_grid[i][j].type;

				// Top.
				if (IsWall(i, j - 1))
				{
					value += 1;
				}

				// Right.
				if (IsWall(i + 1, j))
				{
					value += 2;
				}

				// Bottom.
				if (IsWall(i, j + 1))
				{
					value += 4;
				}

				// Left.
				if (IsWall(i - 1, j))
				{
					value += 8;
				}

				// Set the new type.
				m_grid[i][j].type = (eTILE)value;
				m_grid[i][j].sprite.setTexture(getTextureByTileTipe_WA(static_cast<eTILE>(value)));
			}
		}
	}
}

// Generates an entry and exit point for the given level.
void Level::GenerateEntryExit()
{
	// Calculates new start and end locations within the level.
	int startI, endI;
	startI = endI = -1;

	while (startI == -1)
	{
		int index = Random(GRID_WIDTH - 1);

		if (m_grid[index][GRID_HEIGHT - 1].type == eTILE::WALL_TOP)
		{
			startI = index;
		}
	}

	while (endI == -1)
	{
		int index = Random(GRID_HEIGHT - 1);

		if (m_grid[index][0].type == eTILE::WALL_TOP)
		{
			endI = index;
		}
	}

	// Set the tile textures for the entrance and exit tiles.
	SetTile(startI, GRID_HEIGHT - 1, eTILE::WALL_ENTRANCE);
	SetTile(endI, 0, eTILE::WALL_DOOR_LOCKED);

	// Save the location of the exit door.
	m_doorTileIndices = sf::Vector2i(endI, 0);

	// Calculate the spawn location.
	m_spawnLocation = mapCordToLocation(startI, GRID_HEIGHT - 2);
}

// Generates a random level.
void Level::GenerateLevel()
{
	// Create the initial grid pattern.
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			if ((i % 2 != 0) && (j % 2 != 0))
			{
				// Odd tiles, nothing.
				m_grid[i][j].type = eTILE::EMPTY;
			}
			else
			{
				m_grid[i][j].type = eTILE::WALL_TOP;
				m_grid[i][j].sprite.setTexture(getTextureByTileTipe_WA(eTILE::WALL_TOP));
			}

			// Set the position.
			m_grid[i][j].sprite.setPosition(static_cast<float>(m_origin.x + (TILE_SIZE * i)), static_cast<float>(m_origin.y + (TILE_SIZE * j)));
		}
	}

	// Make the first call to CarvePassage, starting the recursive backtracker algorithm.
	CreatePath(1, 1);

	// Add some rooms to the level to create some open space.
	CreateRooms(10);

	// Calculate the correct texture for each tile.
	CalculateTextures();

	// Increment our room/floor count and generate new effect if necessary.
	m_roomNumber++;

	if (m_roomNumber == 5)
	{
		// Move to next floor.
		m_roomNumber = 0;
		m_floorNumber++;

		// Generate a random color and apply it to the level tiles.
		SetColor(RandomColor(100u, 201u));
	}

	// Add entrance and exit tiles to the level.
	GenerateEntryExit();

	// Erase any existing torches and add new ones torches.
	m_torches.clear();
	SpawnTorches(5);

	// Change a selection of random tiles to the cracked tile sprite.
	SpawnRandomTiles(eTILE::FLOOR_ALT, 15);

}

// Spawns a given number of a given tile randomly in the level.
void Level::SpawnRandomTiles(eTILE tileType, int count)
{
	// Loop the number of tiles we need.
	for (int i = 0; i < count; i++)
	{
		const auto&& [rowIndex, columnIndex] = getRandomSpawnMapPos();
		// Now we change the selected tile.
		SetTile(columnIndex, rowIndex, tileType);
	}
}

// Spawns the given number of torches in the level.
void Level::SpawnTorches(int torchCount)
{
	// List of used tiles.
	std::vector<Tile*> usedTiles;

	bool tileFound;

	// For each torch.
	for (int i = 0; i < torchCount; i++)
	{
		tileFound = false;

		// Loop until we find a valid tile.
		while (!tileFound)
		{
			// Find a random tile.without border
			// ??? std::rand() % (GRID_ - 2) + 1;
			int columnIndex = Random(GRID_WIDTH - 2 - 1) + 1;
			int rowIndex = Random(GRID_HEIGHT - 2 - 1) + 1;

			Tile* tile = &m_grid[columnIndex][rowIndex];

			if (tile->type == eTILE::WALL_TOP)
			{
				if (std::find(usedTiles.begin(), usedTiles.end(), tile) == usedTiles.end())
				{
					std::shared_ptr<Torch> torch = std::make_shared<Torch>(m_scene);

    				torch->setSprite(getTextureByTileTipe_WA(eTILE::TORCH), false, 5, 12);
					torch->setPosition(mapCordToLocation(columnIndex, rowIndex));
					m_torches.push_back(torch);
					tileFound = true;
				}
			}
		}
	}
}



// Gets a vector of all torches in the level.
std::vector<std::shared_ptr<Torch>>& Level::GetTorches()
{
	return m_torches;
}



// Draws the level grid to the given render window.
void Level::draw(sf::RenderWindow& window, float timeDelta) const
{
	// Draw the level tiles.
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			window.draw(m_grid[i][j].sprite);
		}
	}

	// Draw all torches.
	for (auto& torch : m_torches)
	{
		torch->draw(window, timeDelta);
	}
}


const sf::Texture& Level::getTextureByTileTipe_WA(const eTILE tileType) const
{
	return m_scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>(m_textureMatch_WA.at(tileType));// throw std::out_of_range
}


