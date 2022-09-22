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
#include <memory>
#include <array>
#include <string>
#include <optional>

 

// Music tracks.
enum class eMUSIC_TRACK
{
	ALT_1,
	ALT_2,
	ALT_3,
	ALT_4,
	COUNT
};


class GameScene : public Scene
{
	using tBase = Scene;
public:
	explicit GameScene(const Game& game);

	virtual bool beforeLoad() override;

	virtual void afterLoad(const bool isLoaded) override;

	virtual void update(const float timeDelta) override;

	virtual void draw(sf::RenderWindow& window, const float timeDelta) override;

private:

	// Views - 2D camera that defines what region is shown on screen.
	enum class eVIEW
	{
		MAIN,
		UI,
		COUNT
	};


	void drawGame(sf::RenderWindow& window, const float timeDelta, const eVIEW viev);
	void drawUI(sf::RenderWindow& window, const float timeDelta, const eVIEW viev);


	/**
	 * Plays the given sound effect, with randomized parameters.
	 * @param sound A reference to the sound to play.
	 * @param position The position to play the sound at.
	 */
	void PlaySound(sf::Sound& sound, const sf::Vector2f position = { 0.f, 0.f });

	/**
	 * Populates the current game room with items and enemies.
	 */
	void PopulateLevel();

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
	void DrawString(sf::RenderWindow& window, const std::string text, const sf::Vector2f position, const unsigned int size = 10);

	/**
	 * Spawns a given item within the level.
	 * Be default, the object will be spawned at a random location. There are optional parameters to override and spawn at a given location.
	 * @param itemType The type of the item to spawn.
	 * @param position The position to spawn the item at.
	 */
	void SpawnItem(const eITEM itemType, const sf::Vector2f position = { -1.f, -1.f });

	/**
	* Spawns a given enemy within the level.
	* Be default, the object will be spawned at a random location. There are optional parameters to override and spawn at a given location.
	* @param enemyType The type of the enemy to spawn.
	* @param position The position to spawn the enemy at.
	*/
	void SpawnEnemy(const eENEMY enemyType, const sf::Vector2f position = { -1.f, -1.f });

	/**
	 * Constructs the grid of sprites that are used to draw the game shadow system.
	 */
	void ConstructShadowGrid();

	/**
	 * Generates a level goal.
	 */
	void GenerateLevelGoal();


	/**
	 * Updates the level shadow.
	 * @param playerPosition The position of the players within the level.
	 */
	std::optional<sf::Vector2f> UpdateShadow(const sf::Vector2f playerPosition);
	/**
	 * Updates all items in the level.
	 * @param playerPosition The position of the players within the level.
	 */
	void UpdateItems(const sf::Vector2f playerPosition);
	/**
	 * Updates all enemies in the level.
	 * @param playerPosition The position of the players within the level.
	 * @param timeDelta The amount of time that has passed since the last update.
	 */
	void UpdateEnemies(const sf::Vector2f playerPosition, const float timeDelta);
	/**
	 * Updates all projectiles in the level.
	 * @param timeDetla The amount of time that has passed since the last update.
	 */
	void UpdateProjectiles(const float timeDelta);
	sf::Vector2f updatePlayer(const float timeDelta);

	void ReSpawnLevel();

	std::string MakeGoalString() const;

private:
	// An array of the different views the game needs.
	std::array<sf::View, static_cast<int>(eVIEW::COUNT)> m_views;

	// A vector that holds all items within the level.
	std::vector<std::unique_ptr<Item>> m_items;

	// A vector that holds all the enemies within the level.
	std::vector<std::unique_ptr<Enemy>> m_enemies;

	// A vector containing all sprites that make up the shadowing grid.
	std::vector<sf::Sprite> m_shadowGrid;

	// The main level object. All data and functionally regarding the level lives in this class/object.
	std::unique_ptr<Level> m_level;

	// The main player object. Only one instance of this object should be created at any one time.
	std::unique_ptr<Player> m_player;

	// The size of the screen and window.
	sf::Vector2u m_screenSize;

	// The center of the screen.
	sf::Vector2f m_screenCenter;


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
	* The sprite for the players defense stat.
	*/
	std::shared_ptr<sf::Sprite> m_defenseStatSprite;

	/**
	* The sprite for the players strength stat.
	*/
	std::shared_ptr<sf::Sprite> m_strengthStatSprite;

	/**
	* The sprite for the players dexterity stat.
	*/
	std::shared_ptr<sf::Sprite> m_dexterityStatSprite;

	/**
	* The sprite for the players stamina stat.
	*/
	std::shared_ptr<sf::Sprite> m_staminaStatSprite;

	/**
	 * A vector of all the player's projectiles.
	 */
	std::vector<std::unique_ptr<Projectile>> m_playerProjectiles;


	// The current game score.
	int m_scoreTotal;

	// The amount of gold that the player currently has.
	int m_goldTotal;

	// The value of gold remaining for the current goal.
	int m_goldGoal;

	// The value of gems remaining for the current goal.
	int m_gemGoal;

	// The number of kills remaining for the current goal.
	int m_killGoal;

	// The text that will hold the level goal.
	sf::String m_goalString;

	// A boolean denoting if a goal is currently active.
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

	// Sounds.
	sf::Sound m_fireSound;
	sf::Sound m_gemPickupSound;
	sf::Sound m_coinPickupSound;
	sf::Sound m_keyPickupSound;
	sf::Sound m_enemyDieSound;
	sf::Sound m_playerHitSound;

	 // The main music.
	sf::Music m_music;

	//TODO way m_text is class member, maybe prefer local variable
	//sf::Text text;
	///Text used by the DrawText() function.
	sf::Text m_text;
};

#endif //SCENE_H