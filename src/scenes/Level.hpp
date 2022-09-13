
#ifndef LEVEL_H
#define LEVEL_H

#include "items/environment/Torch.hpp"

#include <array>
#include <unordered_map>
#include <optional>
#include <list>

//fwd
class Scene;

// Tiles.
enum class eTILE 
{
	WALL_SINGLE,
	WALL_TOP_END,
	WALL_SIDE_RIGHT_END,
	WALL_BOTTOM_LEFT,
	WALL_BOTTOM_END,
	WALL_SIDE,
	WALL_TOP_LEFT,
	WALL_SIDE_LEFT_T,
	WALL_SIDE_LEFT_END,
	WALL_BOTTOM_RIGHT,
	WALL_TOP,
	WALL_BOTTOM_T,
	WALL_TOP_RIGHT,
	WALL_SIDE_RIGHT_T,
	WALL_TOP_T,
	WALL_INTERSECTION,
	WALL_DOOR_LOCKED,
	WALL_DOOR_UNLOCKED,
	WALL_ENTRANCE,
	FLOOR,
	FLOOR_ALT,
	EMPTY,
	TORCH,
	COUNT
};

// The level tile type.
struct Tile 
{
	eTILE type;							// The type of tile this is.
	int columnIndex;					// The column index of the tile.
	int rowIndex;						// The row index of the tile.
	sf::Sprite sprite;					// The tile sprite.


	////for path finding
	//int H;								// Heuristic / movement cost to goal.
	//int G;								// Movement cost. (Total of entire path)
	//int F;								// Estimated cost for full path. (G + H)
	//Tile* parentNode;					// Node to reach this node.

	//friend inline bool operator==(const Tile& lhs, const Tile& rhs)
	//{
	//	return lhs.columnIndex == rhs.columnIndex && lhs.rowIndex == rhs.rowIndex;
	//}
	//friend inline bool operator!=(const Tile& lhs, const Tile& rhs)
	//{
	//	return !(lhs == rhs);
	//}

	inline bool operator==(const Tile& other) const
	{
		return columnIndex == other.columnIndex && rowIndex == other.rowIndex;
	}
	inline bool operator!=(const Tile& other) const
	{
		return !(*this == other);
	}

};

class Level
{
// Constants for the game grid size.
static int const GRID_WIDTH = 19;
static int const GRID_HEIGHT = 19;

// The width and height of each tile in pixels.
static int const TILE_SIZE = 50;

public:
	/** 
	 * Constructor.
	 * A renderWindow is needed in order for the level to calculate its position.
	 * @param window The game window.
	 */
	explicit Level(const sf::Vector2u screenSize, const Scene& scene);

	/**
	 * Draws the level grid to the provided render window.
	 * @param window The render window to draw the level to.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	void draw(sf::RenderWindow &window, float timeDelta) const;


	/**
	 * Gets the position of the level grid relative to the window.
	 * @return The position of the top-left of the level grid.
	 */
	sf::Vector2f getPosition() const;

	/**
	 * Gets a vector of all torches in the level.
	 * @return A vector of shared_ptrs containing all torches in the level.
	 */
	std::vector<std::shared_ptr<Torch>>& GetTorches();

	/**
	 * Gets the index of the given tile.
	 * @param columnIndex The column index of the tile to check.
	 * @param rowIndex The row index of the tile to check.
	 * @return The index of the given tile.
	 */
	eTILE GetTileType(const int columnIndex, const int rowIndex) const;
	eTILE GetTileType(const sf::Vector2f position) const;

	/**
	 * Gets the current floor number.
	 * @return The current floor.
	 */
	int GetFloorNumber() const;

	/**
	 * Gets the current room number.
	 * @return The current room.
	 */
	int GetRoomNumber() const;

	/**
	 * Gets the size of the level in terms of tiles.
	 * @return The size of the level grid.
	 */
	sf::Vector2i getSize() const;

	/**
	 * Returns the size of the tiles in the level.
	 * @return The size of the tiles in the level.
	 */
	int getTileSize() const;


	/**
	 * Gets the actual position of a tile in the game.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return The position of the tile if valid.
	 */
	sf::Vector2f mapCordToLocation(const int columnIndex, const int rowIndex) const;
	/**
	* from screen coord to map
	*/
	sf::Vector2i locationToMapCord(const sf::Vector2f position) const;


	/**
	* Returns a valid spawn location from the current room.
	* The position returned is relative to the game window.
	* @return A suitable spawn location within the room.
	*/
	sf::Vector2f GetRandomSpawnLocation() const;

	/**
	* Returns a valid spawn map position from the current room.
	* The position returned is idexes of map.
	*/
	sf::Vector2i getRandomSpawnMapPos() const;

	/**
	 * Returns the spawn location for the current level.
	 * @return The spawn location of the level.
	 */
	sf::Vector2f getPlayerSpawnLocation() const;

	/**
	 * Return true if the given tile is a floor tile.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the given tile is a floor tile.
	 */
	bool IsFloor(int columnIndex, int rowIndex) const;

	/**
	* Return true if the given tile is a floor tile.
	* @param tile The tile to check
	* @return True if the given tile is a floor tile.
	*/
	bool IsFloor(const Tile& tile) const;

	/**
	 * Returns true if the given tile index is solid.
	 * @param columnIndex The tile's column index.
	 * @param rowIndex The tile's row index.
	 * @return True if the given tile is solid.
	 */
	bool IsSolid(const int columnIndex, const int rowIndex) const;
	bool IsSolid(const sf::Vector2f position) const;




	/**
	 * Gets the tile at the given position.
	 * @param position The coordinates of the position to check.
	 * @return A pointer to the tile at the given location.
	 */
	Tile* GetTile(const sf::Vector2f position);

	/**
	* Gets the tile at the given position in the level array.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The row that the tile is in.
	* @return A pointer to the tile if valid.
	*/
	//const std::optional<Tile> GetTile(int columnIndex, int rowIndex) const;
	Tile* GetTile(const int columnIndex, const int rowIndex);


	std::list<sf::Vector2f> pathfinding(const sf::Vector2f from, const sf::Vector2f to) const;



	/**
	 * Resets the A* data of all level tiles.
	 */
	//void ResetNodes___willBeRemoved();

	/**
	 * Sets the overlay color of the level tiles.
	 * @param tileColor The new tile overlay color.
	 */
	void SetColor(sf::Color tileColor);

	/**
	 * Generates a random level.
	 */
	void GenerateLevel();

	/**
	 * Spawns a given number of torches in the level.
	 * @param torchCount The number of torches to create.
	 */
	void SpawnTorches(int torchCount);

	/**
	 * Unlocks the door in the level.
	 */
	void UnlockDoor();

private:
	/**
	 * Sets the index of a given tile in the 2D game grid.
	 * This also changes the tile sprite, and is how tiles should be changed and set manually.
	 * @param columnIndex The tile's column index.
	 * @param rowIndex The tile's row index.
	 * @param index The new index of the tile.
	 */
	void SetTile(const int columnIndex, const int rowIndex, const eTILE tileType);

	/** 
	 * Creates a path between two nodes in the recursive backtracker algorithm.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 */
	void CreatePath(int columnIndex, int rowIndex);

	/**
	 * Adds a given number of randomly sized rooms to the level to create some open space.
	 */
	void CreateRooms(int roomCount);

	/**
	 * Calculates the correct texture for each tile in the level.
	 */
	void CalculateTextures();

	/**
	 * Generates an entry and exit point for the given level.
	 */
	void GenerateEntryExit();

	/**
	 * Spawns a given number of a certain tile at random locations in the level.
	 * This is used to give variance to the level grid.
	 * @param newTileIndex The index of the tiles you want to create.
	 * @param count The number of tiles to create.
	 */
	void SpawnRandomTiles(eTILE tileType, int count);

	/**
	 * Checks if a given tile is a wall block.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the given tile is a wall tile.
	 */
	bool IsWall(const int columnIndex, const int rowIndex) const;

	/**
	 * Checks if a given tile is valid.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the tile is valid.
	 */
	bool TileIsValid(int columnIndex, int rowIndex) const;

private:

	/**
	 * A 2D array that describes the level data.
	 * The type is Tile, which holds a sprite and an index.
	 */
	//std::array<std::array<Tile, GRID_HEIGHT>, GRID_WIDTH> m_grid;   VS  ????
	std::array<std::array<Tile, GRID_WIDTH>, GRID_HEIGHT> m_grid;
	//Tile m_grid[GRID_WIDTH][GRID_HEIGHT];

	/**
	 * A vector off all the sprites in the level.
	 */
	std::vector<sf::Sprite> m_tileSprites;

	/**
	 * The position of the level relative to the window.
	 * This is to the top-left of the level grid.
	 */
	sf::Vector2i m_origin;

	/**
	* The floor number that the player is currently on.
	*/
	int m_floorNumber;

	/**
	* The room number that the player is currently in.
	*/
	int m_roomNumber;

	/**
	* A 2D array that contains the room layout for the current floor.
	*/
	//std::array<std::array<int, 3>, 10> m_roomLayout; VS  ????
	std::array<std::array<int, 10>, 3> m_roomLayout;
	//int m_roomLayout[3][10];

	/**
	 * An array containing all texture IDs of the level tiles.
	 */
	std::unordered_map<eTILE, std::string> m_textureMatch_WA;
	const sf::Texture& getTextureByTileTipe_WA(const eTILE tileType) const;

	/**
	 * The spawn location for the current level.
	 */
	sf::Vector2f m_spawnLocation;

	/**
	 * The indices of the tile containing the levels door.
	 */
	sf::Vector2i m_doorTileIndices;

	/**
	 * A vector of all tiles in the level.
	 */
	std::vector<std::shared_ptr<Torch>> m_torches;

	const Scene& m_scene;
};
#endif