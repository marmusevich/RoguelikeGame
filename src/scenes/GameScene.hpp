#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "core/Scene.hpp"

#include "characters/Player.hpp"
#include "characters/enemies/Slime.hpp"
#include "characters/enemies/Humanoid.hpp"
#include "scenes/Level.hpp"
#include "items/loot/Gold.hpp"
#include "items/loot/Key.hpp"
#include "items/loot/Gem.hpp"
#include "items/loot/Potion.hpp"
#include "items/loot/Heart.hpp"

#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>

#include <unordered_map>

class GameScene : public Scene
{
	using tBase = Scene;
public:
	GameScene(const Game& game);

	virtual bool BeforeLoad() override;

	virtual void AfterLoad(bool isLoaded) override;

	virtual void Update(float timeDelta) override;

	virtual void Draw(sf::RenderWindow& window, float timeDelta) override;

private:

	/**
	 * Plays the given sound effect, with randomized parameters.
	 * @param sound A reference to the sound to play.
	 * @param position The position to play the sound at.
	 */
	void PlaySound(sf::Sound& sound, sf::Vector2f position = { 0.f, 0.f });

	/**
	 * Populates the current game room with items and enemies.
	 */
	void PopulateLevel();

	/**
	 * Spawns a given number of a certain tile at random locations in the level.
	 * This is used to give variance to the level grid.
	 * @param newTileIndex The index of the tiles you want to create.
	 * @param count The number of tiles to create.
	 */
	void SpawnRandomTiles(TILE tileType, int count);

	/**
	 * Loads all sprites needed for the UI.
	 */
	void LoadUI();

	/**
	 * Generates a new level.
	 */
	void GenerateLevel();

	/**
	 * Draws text at a given location on the screen.
	 * @param text The string you wish to draw.
	 * @param position The top-left position of the string.
	 * @param size (Optional) The font-size to use. Default value is 10.
	 */
	void DrawString(sf::RenderWindow& window, std::string text, sf::Vector2f position, unsigned int size = 10);

	/**
	 * Spawns a given item within the level.
	 * Be default, the object will be spawned at a random location. There are optional parameters to override and spawn at a given location.
	 * @param itemType The type of the item to spawn.
	 * @param position The position to spawn the item at.
	 */
	void SpawnItem(ITEM itemType, sf::Vector2f position = { -1.f, -1.f });

	/**
	* Spawns a given enemy within the level.
	* Be default, the object will be spawned at a random location. There are optional parameters to override and spawn at a given location.
	* @param enemyType The type of the enemy to spawn.
	* @param position The position to spawn the enemy at.
	*/
	void SpawnEnemy(ENEMY enemyType, sf::Vector2f position = { -1.f, -1.f });

	/**
	 * Constructs the grid of sprites that are used to draw the game light system.
	 */
	void ConstructLightGrid();

	/**
	 * Generates a level goal.
	 */
	void GenerateLevelGoal();

	/**
	 * Updates the level light.
	 * @param playerPosition The position of the players within the level.
	 */
	void UpdateLight(sf::Vector2f playerPosition, int direction);

	/**
	 * Updates all items in the level.
	 * @param playerPosition The position of the players within the level.
	 */
	void UpdateItems(sf::Vector2f playerPosition);

	/**
	 * Updates all enemies in the level.
	 * @param playerPosition The position of the players within the level.
	 * @param timeDelta The amount of time that has passed since the last update.
	 */
	void UpdateEnemies(sf::Vector2f playerPosition, float timeDelta);

	/**
	 * Updates all projectiles in the level.
	 * @param timeDetla The amount of time that has passed since the last update.
	 */
	void UpdateProjectiles(float timeDelta);

	void ReSpawnLevel();

	std::string MakeGoalString();

private:

	/**
	 * An array of the different views the game needs.
	 */
	sf::View m_views[static_cast<int>(VIEW::COUNT)];

	/**
	 * The default font to be used when drawing text.
	 */
	sf::Font m_font;

	/**
	 * A vector that holds all items within the level.
	 */
	std::vector<std::unique_ptr<Item>> m_items;

	/**
	 * A vector that holds all the enemies within the level.
	 */
	std::vector<std::unique_ptr<Enemy>> m_enemies;

	/**
	 * The main level object. All data and functionally regarding the level lives in this class/object.
	 */
	Level m_level;

	/**
	 * The main player object. Only one instance of this object should be created at any one time.
	 */
	Player m_player;

	/**
	 * Text used by the DrawText() function.
	 */
	sf::Text m_text;

	/**
	 * A vector containing all sprites that make up the lighting grid.
	 */
	std::vector<sf::Sprite> m_lightGrid;

	/**
	 * The size of the screen and window.
	 */
	sf::Vector2u m_screenSize;

	/**
	* The center of the screen.
	*/
	sf::Vector2f m_screenCenter;

	/**
	 * The current game score.
	 */
	int m_scoreTotal;

	/**
	* The amount of gold that the player currently has.
	*/
	int m_goldTotal;

	/**
	 * The sprite that shows the player class in the UI.
	 */
	std::shared_ptr<sf::Sprite> m_playerUiSprite;

	/**
	 * The sprite used to show how many coins the player has.
	 */
	std::shared_ptr<sf::Sprite> m_coinUiSprite;

	/**
	* The sprite used to show how much score the player has.
	*/
	std::shared_ptr<sf::Sprite> m_gemUiSprite;

	/**
	 * Key ui sprite.
	 */
	std::shared_ptr<sf::Sprite> m_keyUiSprite;

	/**
	 * The sprite for the players attack stat.
	 */
	std::shared_ptr<sf::Sprite> m_attackStatSprite;

	/**
	 * The texture IDs for the attack stat textures.
	 */
	int m_attackStatTextureIDs[2];

	/**
	* The sprite for the players defense stat.
	*/
	std::shared_ptr<sf::Sprite> m_defenseStatSprite;

	/**
	* The texture IDs for the defense stat textures.
	*/
	int m_defenseStatTextureIDs[2];

	/**
	* The sprite for the players strength stat.
	*/
	std::shared_ptr<sf::Sprite> m_strengthStatSprite;

	/**
	* The texture IDs for the strength stat textures.
	*/
	int m_strengthStatTextureIDs[2];

	/**
	* The sprite for the players dexterity stat.
	*/
	std::shared_ptr<sf::Sprite> m_dexterityStatSprite;

	/**
	* The texture IDs for the dexterity stat textures.
	*/
	int m_dexterityStatTextureIDs[2];

	/**
	* The sprite for the players stamina stat.
	*/
	std::shared_ptr<sf::Sprite> m_staminaStatSprite;

	/**
	* The texture IDs for the stamina stat textures.
	*/
	int m_staminaStatTextureIDs[2];

	/**
	 * The last tile that the player was on.
	 */
	Tile* m_playerPreviousTile;

	/**
	 * A vector of all the player's projectiles.
	 */
	std::vector<std::unique_ptr<Projectile>> m_playerProjectiles;

	/**
	 * The ID of the player's projectile texture.
	 */
	int m_projectileTextureID;

	/**
	 * The value of gold remaining for the current goal.
	 */
	int m_goldGoal;

	/**
	 * The value of gems remaining for the current goal.
	 */
	int m_gemGoal;

	/**
	 * The number of kills remaining for the current goal.
	 */
	int m_killGoal;

	/**
	* The text that will hold the level goal.
	*/
	sf::String m_goalString;

	/**
	 * A boolean denoting if a goal is currently active.
	 */
	bool m_activeGoal;

	/**
	 * Sprite for the health bar.
	 */
	std::shared_ptr<sf::Sprite> m_healthBarSprite;

	/**
	* Sprite for the health bar outline.
	*/
	std::shared_ptr<sf::Sprite> m_healthBarOutlineSprite;

	/**
	 * Sprite for the mana bar.
	 */
	std::shared_ptr<sf::Sprite> m_manaBarSprite;

	/**
	* Sprite for the mana bar outline.
	*/
	std::shared_ptr<sf::Sprite> m_manaBarOutlineSprite;

	/**
	 * A vector of all ui sprites.
	 */
	std::vector<std::shared_ptr<sf::Sprite>> m_uiSprites;

	/**
	 * Torch sound.
	 */
	sf::Sound m_fireSound;

	/**
	 * Gem pickup sound.
	 */
	sf::Sound m_gemPickupSound;

	/**
	 * Coin pickup sound.
	 */
	sf::Sound m_coinPickupSound;

	/**
	* Key collect sound.
	*/
	sf::Sound m_keyPickupSound;

	/**
	 * Enemy die sound.
	 */
	sf::Sound m_enemyDieSound;

	/**
	 * Player hit sound.
	 */
	sf::Sound m_playerHitSound;

	/**
	 * The main music.
	 */
	sf::Music m_music;

	/**
	 * An array of texture for the player in the UI.
	 */
	int m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::COUNT)];




	std::unordered_map<POTION, int> m_potionTextureIDs;
	std::unordered_map<GOLD_TEXTURE_TYPE, int> m_goldTextureIDs;
	int m_gemTextureID;
	int m_keyTextureID;
	int m_heartTextureID;
	int m_lightTextureID;
};

#endif //SCENE_H