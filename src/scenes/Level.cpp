//#include "PCH.hpp"
#include "scenes/Level.hpp"
#include "utils/MathUtils.hpp"

#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"


// Constructor.
Level::Level(const sf::Vector2u screenSize, const Scene& scene)
: m_origin({ 0, 0 })
, m_floorNumber(1)
, m_roomNumber(0)
, m_spawnLocation({ 0.f, 0.f })
, m_doorTileIndices({ 0, 0 })
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
}

void Level::initTiles()
{
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
bool Level::IsSolid(int i, int j)
{
	// Check that the tile is valid
	if (TileIsValid(i, j))
	{
		int tileIndex = static_cast<int>(m_grid[i][j].type);
		return (((tileIndex != static_cast<int>(eTILE::FLOOR)) && (tileIndex != static_cast<int>(eTILE::FLOOR_ALT))) && (tileIndex != static_cast<int>(eTILE::WALL_DOOR_UNLOCKED)));
	}
	else
		return false;
}

// Returns the position of the level relative to the application window.
sf::Vector2f Level::getPosition() const
{
	return sf::Vector2f(static_cast<float>(m_origin.x), static_cast<float>(m_origin.y));
}

// Returns the id of the given tile in the 2D level array.
eTILE Level::GetTileType(int columnIndex, int rowIndex) const
{
	// Check that the parameters are valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT))
	{
		return eTILE::EMPTY; // failed
	}

	// Fetch the id.
	return m_grid[columnIndex][rowIndex].type;
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
bool Level::TileIsValid(int column, int row)
{
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}

// Gets the size of the level in terms of tiles.
sf::Vector2i Level::GetSize() const
{
	return sf::Vector2i(GRID_WIDTH, GRID_HEIGHT);
}

// Gets the tile that the position lies on.
Tile* Level::GetTile(sf::Vector2f position)
{
	// Convert the position to relative to the level grid.
	position.x -= m_origin.x;
	position.y -= m_origin.y;

	// Convert to a tile position.
	int tileColumn, tileRow;

	tileColumn = static_cast<int>(position.x) / TILE_SIZE;
	tileRow = static_cast<int>(position.y) / TILE_SIZE;

	return &m_grid[tileColumn][tileRow];
}

// Returns a pointer to the tile at the given index.
Tile* Level::GetTile(int columnIndex, int rowIndex)
{
	if (TileIsValid(columnIndex, rowIndex))
	{
		return &m_grid[columnIndex][rowIndex];
	}
	else
	{
		return nullptr;
	}
}

// Gets the actual location of a tile in the level.
sf::Vector2f Level::GetActualTileLocation(int columnIndex, int rowIndex)
{
	sf::Vector2f location;

	location.x = static_cast<float>(m_origin.x + (columnIndex * TILE_SIZE) + (TILE_SIZE / 2));
	location.y = static_cast<float>(m_origin.y + (rowIndex * TILE_SIZE) + (TILE_SIZE / 2));

	return location;
}

// Returns a valid spawn location from the currently loaded level.
sf::Vector2f Level::GetRandomSpawnLocation()
{
	// Declare the variables we need.
	int rowIndex(0), columnIndex(0);

	// Loop until we select a floor tile.
	while (!IsFloor(columnIndex, rowIndex))
	{
		// Generate a random index for the row and column.
		columnIndex = Random(GRID_WIDTH - 1);
		rowIndex = Random(GRID_HEIGHT - 1);
	}

	// Convert the tile position to absolute position.
	sf::Vector2f tileLocation(GetActualTileLocation(columnIndex, rowIndex));

	// Create a random offset.
	tileLocation.x += Random(10, 30);
	tileLocation.y += Random(10, 30);

	return tileLocation;
}

// Resets the A* data of all tiles.
void Level::ResetNodes()
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			auto cell = &m_grid[i][j];
			cell->parentNode = nullptr;
			cell->H = 0;
			cell->G = 0;
			cell->F = 0;
		}
	}
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
		int startI = Random(GRID_WIDTH - 2 -1) + 1;
		int startY = Random(GRID_HEIGHT - 2 -1) + 1;

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
	m_spawnLocation = GetActualTileLocation(startI, GRID_HEIGHT - 2);
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
}

// Returns the spawn location for the current level.
sf::Vector2f Level::SpawnLocation() const
{
	return m_spawnLocation;
}

// Checks if a given tile is a wall block.
bool Level::IsWall(int i, int j)
{
	if (TileIsValid(i, j))
		return m_grid[i][j].type <= eTILE::WALL_INTERSECTION;
	else
		return false;
}

// Unlocks the door in the level.
void Level::UnlockDoor()
{
	SetTile(m_doorTileIndices.x, m_doorTileIndices.y, eTILE::WALL_DOOR_UNLOCKED);
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
					std::shared_ptr<Torch> torch = std::make_shared<Torch>();

    				torch->setSprite(getTextureByTileTipe_WA(eTILE::TORCH), false, 5, 12);

					//wall->sprite.setTexture(getTextureByTileTipe_WA(eTILE::FLOOR));
					//torch->setSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(eTILE::TORCH)]), false, 5, 12);


					torch->setPosition(GetActualTileLocation(columnIndex, rowIndex));
					m_torches.push_back(torch);
					tileFound = true;
				}
			}
		}
	}
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(int columnIndex, int rowIndex)
{
	Tile* tile = &m_grid[columnIndex][rowIndex];

	return ((tile->type == eTILE::FLOOR) || (tile->type == eTILE::FLOOR_ALT));
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(const Tile& tile)
{
	return ((tile.type == eTILE::FLOOR) || (tile.type == eTILE::FLOOR_ALT));
}

// Gets the size of the tiles in the level.
int Level::GetTileSize() const
{
	return TILE_SIZE;
}

// Gets a vector of all torches in the level.
std::vector<std::shared_ptr<Torch>>* Level::GetTorches()
{
	return &m_torches;
}

// Draws the level grid to the given render window.
void Level::draw(sf::RenderWindow& window, float timeDelta)
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


const sf::Texture& Level::getTextureByTileTipe_WA(const eTILE tileType)
{
	return m_scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>(m_textureMatch_WA.at(tileType));// throw std::out_of_range
}


