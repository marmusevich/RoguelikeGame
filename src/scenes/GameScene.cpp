
#include "scenes/GameScene.hpp"

#include "core/Game.hpp"
#include "core/manager/TextureManager.hpp"
#include "core/manager/SoundBufferManager.hpp"
#include "utils/Util.hpp"
#include "utils/MathUtils.hpp"

#include <algorithm>
#include <sstream>


static int const MAX_ITEM_SPAWN_COUNT = 50;			// The maximum number of items that can be spawned each room.
static int const MAX_ENEMY_SPAWN_COUNT = 20;		// The maximum number of enemies that can be spawned each room.


GameScene::GameScene(const Game& game)
	:tBase(game),
	m_screenSize(getGame().getScreenSize()),
	m_screenCenter(getGame().getScreenCenter()),
	m_scoreTotal(0),
	m_goldTotal(0),
	m_playerPreviousTile(nullptr),
	m_projectileTextureID(0),
	m_goldGoal(0),
	m_gemGoal(0),
	m_killGoal(0),
	m_goalString(""),
	m_activeGoal(false),
	m_level(getGame().getScreenSize()),

	m_potionTextureIDs(),
	m_goldTextureIDs(),
	m_gemTextureID(-1),
	m_keyTextureID(-1),
	m_heartTextureID(-1),
	m_lightTextureID(-1)

{
	// Define the game views.
	m_views[static_cast<int>(VIEW::MAIN)] = getGame().getDefaultView();
	m_views[static_cast<int>(VIEW::MAIN)].zoom(0.5f);
	m_views[static_cast<int>(VIEW::UI)] = getGame().getDefaultView();
}


bool GameScene::beforeLoad()
{
	// Create the game font.
	//mResurceManager.mFonts->Load("font", "resources/fonts/ADDSBP__.TTF");
	//m_text.setFont(mResurceManager.mFonts->Get("font") );
	//or 
	m_text.setFont(mResurceManager.mFonts->loadFromFile("font", "resources/fonts/ADDSBP__.TTF"));



	// Load the correct projectile texture.
	switch (m_player.GetClass())
	{
	case PLAYER_CLASS::ARCHER:
		m_projectileTextureID = TextureManager::AddTexture("resources/projectiles/spr_arrow.png");
		break;
	case PLAYER_CLASS::MAGE:
		m_projectileTextureID = TextureManager::AddTexture("resources/projectiles/spr_magic_ball.png");
		break;
	case PLAYER_CLASS::THIEF:
		m_projectileTextureID = TextureManager::AddTexture("resources/projectiles/spr_dagger.png");
		break;
	case PLAYER_CLASS::WARRIOR:
		m_projectileTextureID = TextureManager::AddTexture("resources/projectiles/spr_sword.png");
		break;
	}

	m_potionTextureIDs[POTION::ATTACK] = TextureManager::AddTexture("resources/loot/potions/spr_potion_attack.png");
	m_potionTextureIDs[POTION::DEFENSE] = TextureManager::AddTexture("resources/loot/potions/spr_potion_defense.png");
	m_potionTextureIDs[POTION::STRENGTH] = TextureManager::AddTexture("resources/loot/potions/spr_potion_strength.png");
	m_potionTextureIDs[POTION::DEXTERITY] = TextureManager::AddTexture("resources/loot/potions/spr_potion_dexterity.png");
	m_potionTextureIDs[POTION::STAMINA] = TextureManager::AddTexture("resources/loot/potions/spr_potion_stamina.png");

	m_goldTextureIDs[GOLD_TEXTURE_TYPE::SMALL] = TextureManager::AddTexture("resources/loot/gold/spr_pickup_gold_small.png");
	m_goldTextureIDs[GOLD_TEXTURE_TYPE::LARGE] = TextureManager::AddTexture("resources/loot/gold/spr_pickup_gold_large.png");
	m_goldTextureIDs[GOLD_TEXTURE_TYPE::MEDIUM] = TextureManager::AddTexture("resources/loot/gold/spr_pickup_gold_medium.png");


	m_gemTextureID = TextureManager::AddTexture("resources/loot/gem/spr_pickup_gem.png");
	m_keyTextureID = TextureManager::AddTexture("resources/loot/key/spr_pickup_key.png");
	m_heartTextureID = TextureManager::AddTexture("resources/loot/heart/spr_pickup_heart.png");

	m_lightTextureID = TextureManager::AddTexture("resources/spr_light_grid.png");


	// Add the new tile type to level.
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_floor_alt.png"), TILE::FLOOR_ALT);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_floor.png"), TILE::FLOOR);

	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_top.png"), TILE::WALL_TOP);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_top_left.png"), TILE::WALL_TOP_LEFT);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_top_right.png"), TILE::WALL_TOP_RIGHT);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_top_t.png"), TILE::WALL_TOP_T);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_top_end.png"), TILE::WALL_TOP_END);

	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_bottom_left.png"), TILE::WALL_BOTTOM_LEFT);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_bottom_right.png"), TILE::WALL_BOTTOM_RIGHT);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_bottom_t.png"), TILE::WALL_BOTTOM_T);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_bottom_end.png"), TILE::WALL_BOTTOM_END);

	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_side.png"), TILE::WALL_SIDE);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_side_left_t.png"), TILE::WALL_SIDE_LEFT_T);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_side_left_end.png"), TILE::WALL_SIDE_LEFT_END);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_side_right_t.png"), TILE::WALL_SIDE_RIGHT_T);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_side_right_end.png"), TILE::WALL_SIDE_RIGHT_END);

	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_intersection.png"), TILE::WALL_INTERSECTION);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_single.png"), TILE::WALL_SINGLE);

	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_wall_entrance.png"), TILE::WALL_ENTRANCE);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_door_locked.png"), TILE::WALL_DOOR_LOCKED);
	m_level.AddTile(TextureManager::AddTexture("resources/tiles/spr_tile_door_unlocked.png"), TILE::WALL_DOOR_UNLOCKED);

	m_level.AddTile(TextureManager::AddTexture("resources/spr_torch.png"), TILE::TORCH);


	//--------------------------------------------------------

	// Load all game sounds.
	int soundBufferId = -1;

	// Load torch sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("resources/sounds/snd_fire.wav");
	m_fireSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_fireSound.setLoop(true);
	m_fireSound.setAttenuation(5.f);
	m_fireSound.setMinDistance(80.f);
	m_fireSound.play();

	// Load enemy die sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("resources/sounds/snd_enemy_dead.wav");
	m_enemyDieSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_enemyDieSound.setAttenuation(5.f);
	m_enemyDieSound.setMinDistance(80.f);

	// Load gem pickup sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("resources/sounds/snd_gem_pickup.wav");
	m_gemPickupSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_gemPickupSound.setRelativeToListener(true);

	// Load coin pickup sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("resources/sounds/snd_coin_pickup.wav");
	m_coinPickupSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_coinPickupSound.setRelativeToListener(true);

	// Load key pickup sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("resources/sounds/snd_key_pickup.wav");
	m_keyPickupSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_keyPickupSound.setRelativeToListener(true);

	// Load player hit sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("resources/sounds/snd_player_hit.wav");
	m_playerHitSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_playerHitSound.setRelativeToListener(true);


	// Setup the main game music.
	const int trackIndex = Random(static_cast<int>(MUSIC_TRACK::COUNT));
	// Load the music track.
	m_music.openFromFile("resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav");


//-------------------------------------------------------------------------


	// Initialize the UI.
	LoadUI();



	return true;
}

// Loads and prepares all UI assets.
void GameScene::LoadUI()
{
	// Initialize the player ui texture and sprite.
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::WARRIOR)] = TextureManager::AddTexture("resources/ui/spr_warrior_ui.png");
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::MAGE)] = TextureManager::AddTexture("resources/ui/spr_mage_ui.png");
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::ARCHER)] = TextureManager::AddTexture("resources/ui/spr_archer_ui.png");
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::THIEF)] = TextureManager::AddTexture("resources/ui/spr_thief_ui.png");

	// Bar outlines.
	sf::Texture& barOutlineTexture = TextureManager::GetTexture(TextureManager::AddTexture("resources/ui/spr_bar_outline.png"));
	sf::Vector2f barOutlineTextureOrigin = { barOutlineTexture.getSize().x / 2.f, barOutlineTexture.getSize().y / 2.f };

	m_healthBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_healthBarOutlineSprite->setTexture(barOutlineTexture);
	m_healthBarOutlineSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_healthBarOutlineSprite);

	m_manaBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_manaBarOutlineSprite->setTexture(barOutlineTexture);
	m_manaBarOutlineSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_manaBarOutlineSprite);

	//Bars.
	sf::Texture& healthBarTexture = TextureManager::GetTexture(TextureManager::AddTexture("resources/ui/spr_health_bar.png"));
	sf::Vector2f barTextureOrigin = { healthBarTexture.getSize().x / 2.f, healthBarTexture.getSize().y / 2.f };

	m_healthBarSprite = std::make_shared<sf::Sprite>();
	m_healthBarSprite->setTexture(healthBarTexture);
	m_healthBarSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	m_manaBarSprite = std::make_shared<sf::Sprite>();
	m_manaBarSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("resources/ui/spr_mana_bar.png")));
	m_manaBarSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	m_playerUiSprite = std::make_shared<sf::Sprite>();
	m_playerUiSprite->setTexture(TextureManager::GetTexture(m_playerUiTextureIDs[static_cast<int>(m_player.GetClass())]));
	m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
	m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
	m_uiSprites.push_back(m_playerUiSprite);

	// Initialize the coin and gem ui sprites.
	m_gemUiSprite = std::make_shared<sf::Sprite>();
	m_gemUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("resources/ui/spr_gem_ui.png")));
	m_gemUiSprite->setPosition(sf::Vector2f(m_screenCenter.x - 260.f, 50.f));
	m_gemUiSprite->setOrigin(sf::Vector2f(42.f, 36.f));
	m_uiSprites.push_back(m_gemUiSprite);

	m_coinUiSprite = std::make_shared<sf::Sprite>();
	m_coinUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("resources/ui/spr_coin_ui.png")));
	m_coinUiSprite->setPosition(sf::Vector2f(m_screenCenter.x + 60.f, 50.f));
	m_coinUiSprite->setOrigin(sf::Vector2f(48.f, 24.f));
	m_uiSprites.push_back(m_coinUiSprite);

	// Key pickup sprite.
	m_keyUiSprite = std::make_shared<sf::Sprite>();
	m_keyUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("resources/ui/spr_key_ui.png")));
	m_keyUiSprite->setPosition(sf::Vector2f(m_screenSize.x - 120.f, m_screenSize.y - 70.f));
	m_keyUiSprite->setOrigin(sf::Vector2f(90.f, 45.f));
	m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
	m_uiSprites.push_back(m_keyUiSprite);

	// Load stats.
	m_attackStatTextureIDs[0] = TextureManager::AddTexture("resources/ui/spr_attack_ui.png");
	m_attackStatTextureIDs[1] = TextureManager::AddTexture("resources/ui/spr_attack_ui_alt.png");

	m_attackStatSprite = std::make_shared<sf::Sprite>();
	m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[0]));
	m_attackStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_attackStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 270.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_attackStatSprite);

	m_defenseStatTextureIDs[0] = TextureManager::AddTexture("resources/ui/spr_defense_ui.png");
	m_defenseStatTextureIDs[1] = TextureManager::AddTexture("resources/ui/spr_defense_ui_alt.png");

	m_defenseStatSprite = std::make_shared<sf::Sprite>();
	m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[0]));
	m_defenseStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_defenseStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 150.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_defenseStatSprite);

	m_strengthStatTextureIDs[0] = TextureManager::AddTexture("resources/ui/spr_strength_ui.png");
	m_strengthStatTextureIDs[1] = TextureManager::AddTexture("resources/ui/spr_strength_ui_alt.png");

	m_strengthStatSprite = std::make_shared<sf::Sprite>();
	m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[0]));
	m_strengthStatSprite->setOrigin(sf::Vector2f(22.f, 12.f));
	m_strengthStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 30.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_strengthStatSprite);

	m_dexterityStatTextureIDs[0] = TextureManager::AddTexture("resources/ui/spr_dexterity_ui.png");
	m_dexterityStatTextureIDs[1] = TextureManager::AddTexture("resources/ui/spr_dexterity_ui_alt.png");

	m_dexterityStatSprite = std::make_shared<sf::Sprite>();
	m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[0]));
	m_dexterityStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_dexterityStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 90.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_dexterityStatSprite);

	m_staminaStatTextureIDs[0] = TextureManager::AddTexture("resources/ui/spr_stamina_ui.png");
	m_staminaStatTextureIDs[1] = TextureManager::AddTexture("resources/ui/spr_stamina_ui_alt.png");

	m_staminaStatSprite = std::make_shared<sf::Sprite>();
	m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[0]));
	m_staminaStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_staminaStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 210.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_staminaStatSprite);

	// Set player traits
	int traitCount = m_player.GetTraitCount();

	for (int i = 0; i < traitCount; ++i)
	{
		switch (m_player.GetTraits()[i])
		{
		case PLAYER_TRAIT::ATTACK:
			m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[1]));
			m_attackStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::DEFENSE:
			m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[1]));
			m_defenseStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::STRENGTH:
			m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[1]));
			m_strengthStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::DEXTERITY:
			m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[1]));
			m_dexterityStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::STAMINA:
			m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[1]));
			m_staminaStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;
		}
	}
}



void GameScene::afterLoad(bool isLoaded)
{
	if (isLoaded)
	{
		m_music.play();

		// Generate a level.
		GenerateLevel();

		// Builds the light grid.
		ConstructLightGrid();

		// Change a selection of random tiles to the cracked tile sprite.
		SpawnRandomTiles(TILE::FLOOR_ALT, 15);

	}
}


void GameScene::ReSpawnLevel()
{
	// Clear all current items.
	m_items.clear();

	// Clear all current enemies.
	m_enemies.clear();

	// Generate a new room.
	GenerateLevel();

	// Set the key as not collected.
	m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
}

// Updates the game.
void GameScene::update(float timeDelta)
{
	// First check if the player is at the exit. If so there's no need to update anything.
	Tile& playerTile = *m_level.GetTile(m_player.getPosition());

	if (playerTile.type == TILE::WALL_DOOR_UNLOCKED)
	{
		ReSpawnLevel();
	}
	else
	{
		// update the player.
		m_player.update(timeDelta, m_level);

		// Store the player position as it's used many times.
		sf::Vector2f playerPosition = m_player.getPosition();

		int playerDirection = m_player.getCurrentTextureIndex() % 4;

		// Move the audio listener to the players location.
		sf::Listener::setPosition(playerPosition.x, playerPosition.y, 0.f);

		// If the player is attacking create a projectile.
		if (m_player.IsAttacking())
		{
			if (m_player.GetMana() >= 2)
			{
				sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
				std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::GetTexture(m_projectileTextureID), playerPosition, m_screenCenter, target);
				m_playerProjectiles.push_back(std::move(proj));

				// Reduce player mana.
				m_player.SetMana(m_player.GetMana() - 2);
			}
		}

		// update all items.
		UpdateItems(playerPosition);

		// update level light.
		UpdateLight(playerPosition, playerDirection);

		// update all enemies.
		UpdateEnemies(playerPosition, timeDelta);

		// update all projectiles.
		UpdateProjectiles(timeDelta);

		// Find which torch is nearest the player.
		auto torches = m_level.GetTorches();

		// If there are torches.
		if (!torches->empty())
		{
			// Store the first torch as the current closest.
			std::shared_ptr<Torch> nearestTorch = torches->front();
			float lowestDistanceToPlayer = DistanceBetweenPoints(playerPosition, nearestTorch->getPosition());

			for (std::shared_ptr<Torch> torch : *torches)
			{
				// Get the distance to the player.
				float distanceToPlayer = DistanceBetweenPoints(playerPosition, torch->getPosition());
				if (distanceToPlayer < lowestDistanceToPlayer)
				{
					lowestDistanceToPlayer = distanceToPlayer;
					nearestTorch = torch;
				}
			}
			m_fireSound.setPosition(nearestTorch->getPosition().x, nearestTorch->getPosition().y, 0.0f);
		}

		// Check if the player has moved grid square.
		Tile* playerCurrentTile = m_level.GetTile(playerPosition);

		if (m_playerPreviousTile != playerCurrentTile)
		{
			// Store the new tile.
			m_playerPreviousTile = playerCurrentTile;

			// update path finding for all enemies if within range of the player.
			for (const auto& enemy : m_enemies)
			{
				if (DistanceBetweenPoints(enemy->getPosition(), playerPosition) < 300.f)
				{
					enemy->UpdatePathfinding(m_level, playerPosition);
				}
			}
		}

		// Check if we have completed an active goal.
		if (m_activeGoal)
		{
			if ((m_gemGoal <= 0) &&
				(m_goldGoal <= 0) &&
				(m_killGoal <= 0))
			{
				m_scoreTotal += Random(1000, 2000);
				m_activeGoal = false;
			}
			else
			{
				m_goalString = MakeGoalString();
			}
		}

		// Center the view.
		m_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
	}
}


// Draw the current game scene.
void GameScene::draw(sf::RenderWindow& window, float timeDelta)
{
	// Clear the screen.
	window.clear(sf::Color(3, 3, 3, 225));		// Gray

    // Set the main game view.
	window.setView(m_views[static_cast<int>(VIEW::MAIN)]);

	// Draw the level.
	m_level.draw(window, timeDelta);

	// Draw all objects.
	for (const auto& item : m_items)
	{
		item->draw(window, timeDelta);
	}

	// Draw all enemies.
	for (const auto& enemy : m_enemies)
	{
		enemy->draw(window, timeDelta);
	}

	// Draw all projectiles
	for (const auto& proj : m_playerProjectiles)
	{
		window.draw(proj->getSprite());
	}

	// Draw the player.
	m_player.draw(window, timeDelta);

	// Draw level light.
	for (const sf::Sprite& sprite : m_lightGrid)
	{
		window.draw(sprite);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	// Switch to UI view.
	window.setView(m_views[static_cast<int>(VIEW::UI)]);

	// Draw player aim.
	window.draw(m_player.GetAimSprite());

	// Draw the level goal if active.
	if (m_activeGoal)
	{
		DrawString(window, m_goalString, sf::Vector2f(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y - 75)), 30);
	}

	// Draw player stats.
	DrawString(window, std::to_string(m_player.getAttack()), sf::Vector2f(m_screenCenter.x - 210.f, m_screenSize.y - 30.f), 25);
	DrawString(window, std::to_string(m_player.getDefense()), sf::Vector2f(m_screenCenter.x - 90.f, m_screenSize.y - 30.f), 25);
	DrawString(window, std::to_string(m_player.getStrength()), sf::Vector2f(m_screenCenter.x + 30.f, m_screenSize.y - 30.f), 25);
	DrawString(window, std::to_string(m_player.getDexterity()), sf::Vector2f(m_screenCenter.x + 150.f, m_screenSize.y - 30.f), 25);
	DrawString(window, std::to_string(m_player.getStamina()), sf::Vector2f(m_screenCenter.x + 270.f, m_screenSize.y - 30.f), 25);
	DrawString(window, ToStringFormated("%.6i", m_scoreTotal), sf::Vector2f(m_screenCenter.x - 120.f, 40.f), 40);
	DrawString(window, ToStringFormated("%.5i", m_goldTotal), sf::Vector2f(m_screenCenter.x + 220.f, 40.f), 40);

	// Draw rest of the UI.
	for (const auto& sprite : m_uiSprites)
	{
		window.draw(*sprite);
	}

	// Draw the current room and floor.
	DrawString(window, ToStringFormated("Floor %d", m_level.GetFloorNumber()), sf::Vector2f(70.f, m_screenSize.y - 65.f), 25);
	DrawString(window, ToStringFormated("Room %d", m_level.GetRoomNumber()), sf::Vector2f(70.f, m_screenSize.y - 30.f), 25);

	// Draw health and mana bars.
	m_healthBarSprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>((213.f / m_player.getMaxHealth()) * m_player.getHealth()), 8));
	window.draw(*m_healthBarSprite);

	m_manaBarSprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>((213.f / m_player.GetMaxMana()) * m_player.GetMana()), 8));
	window.draw(*m_manaBarSprite);


	DrawString(window, ToStringFormated("is paused %s", (getGame().isPaused() == true ? "true" : "false")), m_screenCenter, 25);


}






// Constructs the grid of sprites that are used to draw the game light system.
void GameScene::ConstructLightGrid()
{
	// Load the light tile texture and store a reference.
	sf::Texture& lightTexture = TextureManager::GetTexture(m_lightTextureID);

	// Calculate the number of tiles in the grid. Each light tile is 25px square.
	sf::IntRect levelArea;

	// Define the bounds of the level.
	levelArea.left = static_cast<int>(m_level.getPosition().x);
	levelArea.top = static_cast<int>(m_level.getPosition().y);
	levelArea.width = m_level.GetSize().x * m_level.GetTileSize();
	levelArea.height = m_level.GetSize().y * m_level.GetTileSize();

	int width, height, lightTotal;

	width = levelArea.width / 25;
	height = levelArea.height / 25;

	lightTotal = width * height;

	// Create all tiles.
	for (int i = 0; i < lightTotal; i++)
	{
		// Create the tile.
		sf::Sprite lightSprite;

		// Set sprite texture.
		lightSprite.setTexture(lightTexture);

		// Set the position of the tile.
		int xPos = levelArea.left + ((i % width) * 25);
		int yPos = levelArea.top + ((i / width) * 25);

		lightSprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));

		// Add the sprite to our light vector.
		m_lightGrid.push_back(lightSprite);
	}
}

// Generates a new level.
void GameScene::GenerateLevel()
{
	// Generate a new level.
	m_level.GenerateLevel();

	// Add a key to the level.
	SpawnItem(ITEM::KEY);

	// Populate the level with items.
	PopulateLevel();

	// 1 in 3 change of creating a level goal.
	if ((Random(2) == 0) && !m_activeGoal)
	{
		GenerateLevelGoal();
	}

	// Moves the player to the start.
	m_player.setPosition(m_level.SpawnLocation());
}

// Populate the level with items.
void GameScene::PopulateLevel()
{
	// Spawn items.
	for (int i = 0; i < MAX_ITEM_SPAWN_COUNT; i++)
	{
		if (Random())
		{
			//only gem or gold
			SpawnItem(Random(ITEM::GOLD));
		}
	}

	// Spawn enemies.
	for (int i = 0; i < MAX_ENEMY_SPAWN_COUNT; i++)
	{
		if (Random())
		{
			SpawnEnemy(Random(ENEMY::COUNT));
		}
	}
}



// Updates the level light.
void GameScene::UpdateLight(sf::Vector2f playerPosition, int direction)
{
	for (sf::Sprite& sprite : m_lightGrid)
	{
		float tileAlpha = 255.f;			// Tile alpha.
		float distance = 0.f;				// The distance between player and tile.

		// Calculate distance between tile and player.
		distance = DistanceBetweenPoints(sprite.getPosition(), playerPosition);

		// Calculate tile transparency.
		if (distance < 200.f)
		{
			tileAlpha = 0.f;
		}
		else if (distance < 250.f)
		{
			tileAlpha = (51.f * (distance - 200.f)) / 10.f;
		}



		//bool isOn = false;
		//sf::Vector2f d = playerPosition - sprite.getPosition();
		//if (direction == 1 && d.y <= 0)
		//{
		//	isOn = true;
		//}
		//else if (direction == 0 && d.y >= 0)
		//{
		//	isOn = true;
		//}
		//else if (direction == 3 && d.x >= 0)
		//{
		//	isOn = true;
		//}
		//else if (direction == 2 && d.x <= 0)
		//{
		//	isOn = true;
		//}

		//if (distance < 100.f)
		//{
		//	tileAlpha = 0.f;
		//}
		//else if (distance < 200.f)
		//{
		//	if (isOn )
		//	{
		//		//tileAlpha = std::abs(distance - 50) * (255 - 0) / (200 - 50);
		//		tileAlpha = 100;
		//	}
		//	else
		//	{
		//		//tileAlpha = (distance - 50) * (255 - 0) / (100 - 50);
		//		tileAlpha = 230;
		//	}
		//}


		//WALK_UP,
		//	WALK_DOWN,
		//	WALK_RIGHT,
		//	WALK_LEFT,



		//tileAlpha = std::min(0.0f, std::max(255.0f - distance,  255.0f));

		// Get all torches from the level.
		auto torches = m_level.GetTorches();

		// If there are torches.
		if (!torches->empty())
		{
			// update the light surrounding each torch.
			for (std::shared_ptr<Torch> torch : *torches)
			{
				// If the light tile is within range of the torch.
				distance = DistanceBetweenPoints(sprite.getPosition(), torch->getPosition());
				if (distance < 50.f)
					//if (distance < 100.f)
				{
					// Edit its alpha.
					tileAlpha -= (tileAlpha - ((tileAlpha / 100.f) * distance)) * torch->GetBrightness();
				}
			}

			// Ensure alpha does not go negative.
			if (tileAlpha < 0)
			{
				tileAlpha = 0;
			}
		}

		// Set the sprite transparency.
		sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
	}
}

// Updates all items in the level.
void GameScene::UpdateItems(sf::Vector2f playerPosition)
{
	// update all items.
	auto itemIterator = m_items.begin();
	while (itemIterator != m_items.end())
	{
		// Get the item from the iterator.
		Item& item = **itemIterator;

		// Check if the player is within pickup range of the item.
		if (DistanceBetweenPoints(item.getPosition(), playerPosition) < 40.f)
		{
			// Check what type of object it was.
			switch (item.getType())
			{
			case ITEM::GOLD:
			{
				// Get the amount of gold.
				int goldValue = dynamic_cast<Gold&>(item).GetGoldValue();

				// Add to the gold total.
				m_goldTotal += goldValue;

				// Check if we have an active level goal regarding gold.
				if (m_activeGoal)
					m_goldGoal -= goldValue;

				// Play gold collect sound effect.
				PlaySound(m_coinPickupSound);
			}
			break;

			case ITEM::GEM:
			{
				// Get the score of the gem.
				int scoreValue = dynamic_cast<Gem&>(item).GetScoreValue();

				// Add to the score total
				m_scoreTotal += scoreValue;

				// Check if we have an active level goal.
				if (m_activeGoal)
					--m_gemGoal;

				// Play the gem pickup sound
				PlaySound(m_gemPickupSound);
			}
			break;

			case ITEM::KEY:
			{
				// Unlock the door.
				m_level.UnlockDoor();

				// Play key collect sound.
				PlaySound(m_keyPickupSound);

				// Set the key as collected.
				m_keyUiSprite->setColor(sf::Color::White);
			}
			break;

			case ITEM::POTION:
			{
				// Cast to position and get type.
				Potion& potion = dynamic_cast<Potion&>(item);
				POTION potionType = potion.GetPotionType();

				switch (potionType)
				{
				case POTION::ATTACK:
					m_player.setAttack(m_player.getAttack() + potion.getAttack());
					break;

				case POTION::DEFENSE:
					m_player.setDefense(m_player.getDefense() + potion.getDefense());
					break;

				case POTION::STRENGTH:
					m_player.setStrength(m_player.getStrength() + potion.getStrength());
					break;

				case POTION::DEXTERITY:
					m_player.setDexterity(m_player.getDexterity() + potion.getDexterity());
					break;

				case POTION::STAMINA:
					m_player.setStamina(m_player.getStamina() + potion.getStamina());
					break;
				}
			}
			break;

			case ITEM::HEART:
				// Cast to heart and get health.
				Heart& heart = dynamic_cast<Heart&>(item);

				m_player.SetHealth(m_player.getHealth() + heart.getHealth());
			}

			// Finally, delete the object.
			itemIterator = m_items.erase(itemIterator);
		}
		else
		{
			// Increment iterator.
			++itemIterator;
		}
	}
}

// Updates all enemies in the level.
void GameScene::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta)
{
	// Store player tile.
	Tile* playerTile = m_level.GetTile(m_player.getPosition());

	auto enemyIterator = m_enemies.begin();
	while (enemyIterator != m_enemies.end())
	{
		// Create a bool so we can check if an enemy was deleted.
		bool enemyWasDeleted = false;

		// Get the enemy object from the iterator.
		Enemy& enemy = **enemyIterator;

		// Get the tile that the enemy is on.
		Tile* enemyTile = m_level.GetTile(enemy.getPosition());

		// Check for collisions with projectiles.
		auto projectilesIterator = m_playerProjectiles.begin();
		while (projectilesIterator != m_playerProjectiles.end())
		{
			// Get the projectile object from the iterator.
			Projectile& projectile = **projectilesIterator;

			// If the enemy and projectile occupy the same tile they have collided.
			if (enemyTile == m_level.GetTile(projectile.getPosition()))
			{
				// Delete the projectile.
				projectilesIterator = m_playerProjectiles.erase(projectilesIterator);

				// Damage the enemy.
				enemy.Damage(25);

				// If the enemy is dead remove it.
				if (enemy.IsDead())
				{
					// Get the enemy position.
					sf::Vector2f position = enemy.getPosition();

					// Spawn loot. gold or gem
					for (int i = 0; i < 5; i++)
					{
						position.x += Random(-15, 15);
						position.y += Random(-15, 15);
						SpawnItem(Random(ITEM::GOLD), position);	// Generates a number 0 - 2
					}

					if (Random(4) == 0)			// 1 in 5 change of spawning health.
					{
						position.x += Random(-15, 15);
						position.y += Random(-15, 15);
						SpawnItem(ITEM::HEART, position);
					}
					// 1 in 5 change of spawning potion.
					else if (Random(4) == 1)
					{
						position.x += Random(-15, 15);
						position.y += Random(-15, 15);
						SpawnItem(ITEM::POTION, position);
					}

					// Play enemy kill sound.
					PlaySound(m_enemyDieSound, enemy.getPosition());

					// Delete enemy.
					enemyIterator = m_enemies.erase(enemyIterator);
					enemyWasDeleted = true;

					// If we have an active goal decrement killGoal.
					if (m_activeGoal)
					{
						--m_killGoal;
					}

					// Since the enemy is dead we no longer need to check projectiles.
					projectilesIterator = m_playerProjectiles.end();
				}
			}
			else
			{
				// Move to the next projectile.
				++projectilesIterator;
			}
		}

		// If the enemy was not deleted, update it and increment the iterator.
		if (!enemyWasDeleted)
		{
			enemy.update(timeDelta);
			++enemyIterator;
		}

		// Check for collision with player.
		if (enemyTile == playerTile)
		{
			if (m_player.CanTakeDamage())
			{
				m_player.Damage(10);
				PlaySound(m_playerHitSound);
			}
		}
	}
}

// Updates all projectiles in the level.
void GameScene::UpdateProjectiles(float timeDelta)
{
	auto projectileIterator = m_playerProjectiles.begin();
	while (projectileIterator != m_playerProjectiles.end())
	{
		// Get the projectile object from the iterator.
		Projectile& projectile = **projectileIterator;

		// Get the tile that the projectile is on.
		TILE projectileTileType = m_level.GetTile(projectile.getPosition())->type;

		// If the tile the projectile is on is not floor, delete it.
		if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
		{
			projectileIterator = m_playerProjectiles.erase(projectileIterator);
		}
		else
		{
			// update the projectile and move to the next one.
			projectile.update(timeDelta);
			++projectileIterator;
		}
	}
}

// Draw the given string at the given position.
void GameScene::DrawString(sf::RenderWindow& window, std::string text, sf::Vector2f position, unsigned int size)
{
	//TODO way m_text is class member, maybe prefer local variable
	//sf::Text text;
	//text.setFont(m_font);

	m_text.setString(text);
	m_text.setCharacterSize(size);
	m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

	window.draw(m_text);
}

// Spawns a given object type at a random location within the map. Has the option to explicitly set a spawn location.
void GameScene::SpawnItem(ITEM itemType, sf::Vector2f position)
{
	std::unique_ptr<Item> item;

	int objectIndex = 0;

	// Choose a random, unused spawn location.
	sf::Vector2f spawnLocation;

	if ((position.x >= 0.f) || (position.y >= 0.f))
		spawnLocation = position;
	else
		spawnLocation = m_level.GetRandomSpawnLocation();

	// Check which type of object is being spawned.
	switch (itemType)
	{
	case ITEM::POTION:
		item = std::make_unique<Potion>(m_potionTextureIDs);
		break;

	case ITEM::GOLD:
		item = std::make_unique<Gold>(m_goldTextureIDs);
		break;

	case ITEM::GEM:
		item = std::make_unique<Gem>();
		item->setSprite(TextureManager::GetTexture(m_gemTextureID), false, 8, 12);
		break;

	case ITEM::KEY:
		item = std::make_unique<Key>();
		item->setSprite(TextureManager::GetTexture(m_keyTextureID), false, 8, 12);
		break;

	case ITEM::HEART:
		item = std::make_unique<Heart>();
		item->setSprite(TextureManager::GetTexture(m_heartTextureID), false, 8, 12);
		break;
	}

	// Set the item position.
	item->setPosition(spawnLocation);

	// Add the item to the list of all items.
	m_items.push_back(std::move(item));
}

// Spawns a given number of enemies in the level.
void GameScene::SpawnEnemy(ENEMY enemyType, sf::Vector2f position)
{
	// Spawn location of enemy(s).
	sf::Vector2f spawnLocation;

	// Choose a random, unused spawn location.
	if ((position.x >= 0.f) || (position.y >= 0.f))
		spawnLocation = position;
	else
		spawnLocation = m_level.GetRandomSpawnLocation();

	// Create the enemy.
	std::unique_ptr<Enemy> enemy;

	switch (enemyType)
	{
	case ENEMY::SLIME:
		enemy = std::make_unique<Slime>();
		break;

	case ENEMY::HUMANOID:
		enemy = std::make_unique<Humanoid>();
		break;
	}

	// Set spawn location.
	enemy->setPosition(spawnLocation);

	// Add to list of all enemies.
	m_enemies.push_back(std::move(enemy));
}

// Spawns a given number of a given tile randomly in the level.
void GameScene::SpawnRandomTiles(TILE tileType, int count)
{
	// Declare the variables we need.
	int rowIndex(0), columnIndex(0), tileIndex(0);

	// Loop the number of tiles we need.
	for (int i = 0; i < count; i++)
	{
		// Declare the variables we need.
		int columnIndex(0), rowIndex(0);

		// Loop until we select a floor tile.
		while (!m_level.IsFloor(columnIndex, rowIndex))
		{
			// Generate a random index for the row and column
			columnIndex = Random(GRID_WIDTH - 1);
			rowIndex = Random(GRID_HEIGHT - 1);
		}

		// Now we change the selected tile.
		m_level.SetTile(columnIndex, rowIndex, tileType);
	}
}

// Generates a random level goal.
void GameScene::GenerateLevelGoal()
{
	// Reset our goal variables.
	m_killGoal = 0;
	m_goldGoal = 0;
	m_gemGoal = 0;

	// Choose which type of goal is to be generated.
	int goalType = Random(2);

	switch (goalType)
	{
	case 0:		// Kill X Enemies
		m_killGoal = Random(5, 10);
		break;

	case 1:		// Collect X Gold
		m_goldGoal = Random(50, 100);
		break;

	case 2:		// Collect X Gems
		m_gemGoal = Random(5, 10);
		break;
	}

	// Store our string.
	m_goalString = MakeGoalString();

	// Set the goal as active.
	m_activeGoal = true;
}

// Plays the given sound effect, with randomized parameters.
void GameScene::PlaySound(sf::Sound& sound, sf::Vector2f position)
{
	// Generate and set a random pitch.
	float pitch = Random(95, 105) / 100.f;
	sound.setPitch(pitch);

	// Set the position of the sound.
	sound.setPosition(position.x, position.y, 0.f);

	// Play the sound.
	sound.play();
}

std::string GameScene::MakeGoalString()
{
	std::ostringstream ss;

	if (m_goldGoal > 0)
	{
		ss << "Current Goal: Collect " << m_goldGoal << " gold" << "!" << std::endl;
	}
	else if (m_gemGoal > 0)
	{
		ss << "Current Goal: Collect " << m_gemGoal << " gem" << "!" << std::endl;
	}
	else if (m_killGoal > 0)
	{
		ss << "Current Goal: Kill " << m_killGoal << " enemies" << "!" << std::endl;
	}
	return ss.str();
}
