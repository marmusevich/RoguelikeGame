
#include "scenes/GameScene.hpp"

#include "core/resourceLoader/cResourceLoaderBuilder.hpp"
#include "core/Game.hpp"
#include "utils/Util.hpp"
#include "utils/MathUtils.hpp"

#include <algorithm>
#include <sstream>

#include <plog/Log.h>


static int const MAX_ITEM_SPAWN_COUNT = 50;			// The maximum number of items that can be spawned each room.
static int const MAX_ENEMY_SPAWN_COUNT = 20;		// The maximum number of enemies that can be spawned each room.


GameScene::GameScene(const Game& game)
: tBase(game)
, m_screenSize(getGame().getScreenSize())
, m_screenCenter(getGame().getScreenCenter())
, m_scoreTotal(0)
, m_goldTotal(0)
, m_goldGoal(0)
, m_gemGoal(0)
, m_killGoal(0)
, m_goalString("")
, m_activeGoal(false)
, m_level(nullptr)
, m_player(nullptr)
{
    // Define the game views.
    m_views[static_cast<int>(eVIEW::MAIN)] = getGame().getDefaultView();
    m_views[static_cast<int>(eVIEW::MAIN)].zoom(0.5f);
    m_views[static_cast<int>(eVIEW::UI)] = getGame().getDefaultView();
}


bool GameScene::beforeLoad()
{
    //must be in Scene::loadResurce()
    NResourceLoader::Ptr resourceLoader{ NResourceLoader::getXmlLoaderFromFile("resources/resources.xml") };
    bool ret = resourceLoader != nullptr && resourceLoader->addResources(getResourceManager());
    if (!ret)
    {
        LOG_ERROR << "Doesn't load ressurce!!";
        throw std::runtime_error("Doesn't load ressurce!!");
    }

    return true;
}

// Loads and prepares all UI assets.
void GameScene::LoadUI()
{
    // Bar outlines.
    const sf::Texture& barOutlineTexture = getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_bar_outline");
    const sf::Vector2f barOutlineTextureOrigin = { barOutlineTexture.getSize().x / 2.f, barOutlineTexture.getSize().y / 2.f };
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
    const sf::Texture& healthBarTexture = getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_health_bar");
    const sf::Vector2f barTextureOrigin = { healthBarTexture.getSize().x / 2.f, healthBarTexture.getSize().y / 2.f };
    m_healthBarSprite = std::make_shared<sf::Sprite>();
    m_healthBarSprite->setTexture(healthBarTexture);
    m_healthBarSprite->setPosition(sf::Vector2f(205.f, 35.f));
    m_healthBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

    m_manaBarSprite = std::make_shared<sf::Sprite>();
    m_manaBarSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_mana_bar"));
    m_manaBarSprite->setPosition(sf::Vector2f(205.f, 55.f));
    m_manaBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

    m_playerUiSprite = std::make_shared<sf::Sprite>();
    m_playerUiSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>(m_player->getUiTextureID()));
    m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
    m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
    m_uiSprites.push_back(m_playerUiSprite);

    // Initialize the coin and gem ui sprites.
    m_gemUiSprite = std::make_shared<sf::Sprite>();
    m_gemUiSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_gem_ui"));
    m_gemUiSprite->setPosition(sf::Vector2f(m_screenCenter.x - 260.f, 50.f));
    m_gemUiSprite->setOrigin(sf::Vector2f(42.f, 36.f));
    m_uiSprites.push_back(m_gemUiSprite);

    m_coinUiSprite = std::make_shared<sf::Sprite>();
    m_coinUiSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_coin_ui"));
    m_coinUiSprite->setPosition(sf::Vector2f(m_screenCenter.x + 60.f, 50.f));
    m_coinUiSprite->setOrigin(sf::Vector2f(48.f, 24.f));
    m_uiSprites.push_back(m_coinUiSprite);

    // Key pickup sprite.
    m_keyUiSprite = std::make_shared<sf::Sprite>();
    m_keyUiSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_key_ui"));
    m_keyUiSprite->setPosition(sf::Vector2f(m_screenSize.x - 120.f, m_screenSize.y - 70.f));
    m_keyUiSprite->setOrigin(sf::Vector2f(90.f, 45.f));
    m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
    m_uiSprites.push_back(m_keyUiSprite);

    // Load stats.
    {
        m_attackStatSprite = std::make_shared<sf::Sprite>();
        m_attackStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_attack_ui"));
        m_attackStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
        m_attackStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 270.f, m_screenSize.y - 30.f));
        m_uiSprites.push_back(m_attackStatSprite);

        m_defenseStatSprite = std::make_shared<sf::Sprite>();
        m_defenseStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_defense_ui"));
        m_defenseStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
        m_defenseStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 150.f, m_screenSize.y - 30.f));
        m_uiSprites.push_back(m_defenseStatSprite);

        m_strengthStatSprite = std::make_shared<sf::Sprite>();
        m_strengthStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_strength_ui"));
        m_strengthStatSprite->setOrigin(sf::Vector2f(22.f, 12.f));
        m_strengthStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 30.f, m_screenSize.y - 30.f));
        m_uiSprites.push_back(m_strengthStatSprite);

        m_dexterityStatSprite = std::make_shared<sf::Sprite>();
        m_dexterityStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_dexterity_ui"));
        m_dexterityStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
        m_dexterityStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 90.f, m_screenSize.y - 30.f));
        m_uiSprites.push_back(m_dexterityStatSprite);

        m_staminaStatSprite = std::make_shared<sf::Sprite>();
        m_staminaStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_stamina_ui"));
        m_staminaStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
        m_staminaStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 210.f, m_screenSize.y - 30.f));
        m_uiSprites.push_back(m_staminaStatSprite);

        // Highlight player traits
        int traitCount = m_player->GetTraitCount();

        for (int i = 0; i < traitCount; ++i)
        {
            switch (m_player->GetTraits()[i])
            {
            case PLAYER_TRAIT::ATTACK:
                m_attackStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_attack_ui_alt"));
                m_attackStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;

            case PLAYER_TRAIT::DEFENSE:
                m_defenseStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_defense_ui_alt"));
                m_defenseStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;

            case PLAYER_TRAIT::STRENGTH:
                m_strengthStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_strength_ui_alt"));
                m_strengthStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;

            case PLAYER_TRAIT::DEXTERITY:
                m_dexterityStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_dexterity_ui_alt"));
                m_dexterityStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;

            case PLAYER_TRAIT::STAMINA:
                m_staminaStatSprite->setTexture(getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_stamina_ui_alt"));
                m_staminaStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
                break;
            }
        }
    }// Load stats.
}


void GameScene::afterLoad(const bool isLoaded)
{
    m_text.setFont(getResourceManager().get<NResurceManagement::EResourceType::Font>("font"));

    m_level = std::make_unique<Level>(getGame().getScreenSize(), *this);
    m_player = std::make_unique<Player>(*this);


    // Set torch sound.
    m_fireSound.setBuffer(getResourceManager().get<NResurceManagement::EResourceType::Sound>("snd_fire"));
    m_fireSound.setLoop(true);
    m_fireSound.setAttenuation(5.f);
    m_fireSound.setMinDistance(80.f);
    m_fireSound.play();
    // Set enemy die sound.
    m_enemyDieSound.setBuffer(getResourceManager().get<NResurceManagement::EResourceType::Sound>("snd_enemy_dead"));
    m_enemyDieSound.setAttenuation(5.f);
    m_enemyDieSound.setMinDistance(80.f);
    // Set gem pickup sound.
    m_gemPickupSound.setBuffer(getResourceManager().get<NResurceManagement::EResourceType::Sound>("snd_gem_pickup"));
    m_gemPickupSound.setRelativeToListener(true);
    // Set coin pickup sound.
    m_coinPickupSound.setBuffer(getResourceManager().get<NResurceManagement::EResourceType::Sound>("snd_coin_pickup"));
    m_coinPickupSound.setRelativeToListener(true);
    // Set key pickup sound.
    m_keyPickupSound.setBuffer(getResourceManager().get<NResurceManagement::EResourceType::Sound>("snd_key_pickup"));
    m_keyPickupSound.setRelativeToListener(true);
    // Set player hit sound.
    m_playerHitSound.setBuffer(getResourceManager().get<NResurceManagement::EResourceType::Sound>("snd_player_hit"));
    m_playerHitSound.setRelativeToListener(true);

    // Setup the main game music.
    const int trackIndex = Random(static_cast<int>(eMUSIC_TRACK::COUNT));
    // Load the music track.
    m_music.openFromFile("resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav");

    //-------------------------------------------------------------------------
    // Initialize the UI.
    LoadUI();


    m_music.play();
    // Generate a level.
    GenerateLevel();

    // Builds the shadow grid.
    ConstructShadowGrid();
}

//--------------------------------------------------------------------------------------------------------------------------------

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

// Generates a new level.
void GameScene::GenerateLevel()
{
    // Generate a new level.
    m_level->GenerateLevel();

    // Add a key to the level.
    SpawnItem(eITEM::KEY);

    // Populate the level with items.
    PopulateLevel();

    // 1 in 3 change of creating a level goal.
    if ((Random(2) == 0) && !m_activeGoal)
    {
        GenerateLevelGoal();
    }

    // Moves the player to the start.
    m_player->setPosition(m_level->getPlayerSpawnLocation());

}

// Constructs the grid of sprites that are used to draw the game shadow system.
void GameScene::ConstructShadowGrid()
{
    //Each shadow tile is 25px square.
    const int size_texture_shadow_grid = 25.f;

    // Calculate the number of tiles in the grid. 
    sf::IntRect levelArea;

    // Define the bounds of the level.
    levelArea.left = static_cast<int>(m_level->getPosition().x);
    levelArea.top = static_cast<int>(m_level->getPosition().y);
    levelArea.width = m_level->getSize().x * m_level->getTileSize();
    levelArea.height = m_level->getSize().y * m_level->getTileSize();


    const int width = levelArea.width / size_texture_shadow_grid;
    const int height = levelArea.height / size_texture_shadow_grid;
    const int shadowTotal = width * height;

    const auto& shadow_texture = getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_shadow_grid");

    // Create all tiles.
    for (int i = 0; i < shadowTotal; i++)
    {
        // Set the position of the tile.
        const float xPos = levelArea.left + ((i % width) * size_texture_shadow_grid);
        const float yPos = levelArea.top + ((i / width) * size_texture_shadow_grid);

        sf::Sprite shadowSprite(shadow_texture);
        shadowSprite.setPosition(xPos, yPos);
        m_shadowGrid.push_back(shadowSprite);
    }
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
            SpawnItem(Random(eITEM::GOLD));
        }
    }



    //debug path finding
#ifdef NDEBUG
    // Spawn enemies.
    for (int i = 0; i < MAX_ENEMY_SPAWN_COUNT; i++)
    {
        if (Random())
        {
            SpawnEnemy(Random(eENEMY::COUNT));
        }
    }
#else
    SpawnEnemy(eENEMY::HUMANOID);
#endif

}

// Spawns a given object type at a random location within the map. Has the option to explicitly set a spawn location.
void GameScene::SpawnItem(const eITEM itemType, const sf::Vector2f position)
{
    std::unique_ptr<Item> item;

    int objectIndex = 0;

    // Choose a random, unused spawn location.
    sf::Vector2f spawnLocation;

    if ((position.x >= 0.f) || (position.y >= 0.f))
        spawnLocation = position;
    else
        spawnLocation = m_level->GetRandomSpawnLocation();

    // Check which type of object is being spawned.
    switch (itemType)
    {
    case eITEM::POTION:
        item = std::make_unique<Potion>(*this);
        break;

    case eITEM::GOLD:
        item = std::make_unique<Gold>(*this);
        break;

    case eITEM::GEM:
        item = std::make_unique<Gem>(*this);
        item->setSprite("spr_pickup_gem", false, 8, 12);
        break;

    case eITEM::KEY:
        item = std::make_unique<Key>(*this);
        item->setSprite("spr_pickup_key", false, 8, 12);
        break;

    case eITEM::HEART:
        item = std::make_unique<Heart>(*this);
        item->setSprite("spr_pickup_heart", false, 8, 12);
        break;
    }

    // Set the item position.
    item->setPosition(spawnLocation);

    // Add the item to the list of all items.
    m_items.push_back(std::move(item));
}

// Spawns a given number of enemies in the level.
void GameScene::SpawnEnemy(const eENEMY enemyType, const sf::Vector2f position)
{
    // Spawn location of enemy(s).
    sf::Vector2f spawnLocation;

    // Choose a random, unused spawn location.
    if ((position.x >= 0.f) || (position.y >= 0.f))
        spawnLocation = position;
    else
        spawnLocation = m_level->GetRandomSpawnLocation();

    // Create the enemy.
    std::unique_ptr<Enemy> enemy;

    switch (enemyType)
    {
    case eENEMY::SLIME:
        enemy = std::make_unique<Slime>(*this);
        break;

    case eENEMY::HUMANOID:
        enemy = std::make_unique<Humanoid>(*this);
        break;
    }

    // Set spawn location.
    enemy->setPosition(spawnLocation);

    // Add to list of all enemies.
    m_enemies.push_back(std::move(enemy));
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

std::string GameScene::MakeGoalString() const
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

//--------------------------------------------------------------------------------------------------------------------------------

// Updates the game.
void GameScene::update(const float timeDelta)
{
    // First check if the player is at the exit. If so there's no need to update anything.
    if (m_level->isItGoal(m_player->getPosition()))
    {
        ReSpawnLevel();
    }
    else
    {
        // update the player.
        const sf::Vector2f playerPosition = updatePlayer(timeDelta);

        // update all items.
        UpdateItems(playerPosition);
        // update level shadow.
        std::optional<sf::Vector2f> distanceToNearestTorch = UpdateShadow(playerPosition);
        if (distanceToNearestTorch)
        {
            m_fireSound.setPosition(distanceToNearestTorch.value().x, distanceToNearestTorch.value().y, 0.0f);
        }
        
        // update all enemies.
        UpdateEnemies(playerPosition, timeDelta);

        // update all projectiles.
        UpdateProjectiles(timeDelta);

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
        m_views[static_cast<int>(eVIEW::MAIN)].setCenter(playerPosition);
    }
}

sf::Vector2f GameScene::updatePlayer(const float timeDelta)
{
    
    m_player->update(timeDelta, *m_level);
    // Store the player position as it's used many times.
    sf::Vector2f playerPosition = m_player->getPosition();
    //int playerDirection = m_player->getCurrentTextureIndex() % 4;
    // Move the audio listener to the players location.
    sf::Listener::setPosition(playerPosition.x, playerPosition.y, 0.f);
    // If the player is attacking create a projectile.
    if (m_player->IsAttacking())
    {
        if (m_player->GetMana() >= 2)
        {
            sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
            std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(*this, m_player->getProjectileTextureID(), playerPosition, m_screenCenter, target);
            m_playerProjectiles.push_back(std::move(proj));
            // Reduce player mana.
            m_player->SetMana(m_player->GetMana() - 2);
        }
    }

    return playerPosition;
}

// Updates the level shadow.
std::optional<sf::Vector2f> GameScene::UpdateShadow(const sf::Vector2f playerPosition)
{
    std::optional<sf::Vector2f> distanceToPlayer;

    // Get all torches from the level.
    auto torches = m_level->GetTorches();


    for (sf::Sprite& shadow : m_shadowGrid)
    {
        float tileAlpha = 255.f;			// Tile alpha.
        // Calculate distance between tile and player.
        float distance = DistanceBetweenPoints(shadow.getPosition(), playerPosition); // The distance between player and tile.

        // Calculate tile transparency by PLAYER.
        if (distance < 200.f)
        {
            tileAlpha = 0.f;
        }
        else if (distance < 250.f)
        {
            tileAlpha = (51.f * (distance - 200.f)) / 10.f;
        }

        // Correcte tile transparency by torches.
        for (std::shared_ptr<Torch> torch : torches)
        {
            // If the shadow tile is within range of the torch.
            distance = DistanceBetweenPoints(shadow.getPosition(), torch->getPosition());
            if (distance < 100.f)
            {
                // Edit its alpha.
                tileAlpha -= (tileAlpha - ((tileAlpha / 100.f) * distance)) * torch->GetBrightness();
            }
        }

        // Ensure alpha does not go negative.
        if (tileAlpha < 0)
        {
            tileAlpha = 0.0;
        }

        // Set the sprite transparency.
        shadow.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
    }


    //algoritm get min distace
    if (!torches.empty())
    {
        // Store the first torch as the current closest.
        std::shared_ptr<Torch> nearestTorch = torches.front();
        float lowestDistanceToPlayer = DistanceBetweenPoints(playerPosition, nearestTorch->getPosition());

        for (std::shared_ptr<Torch> torch : torches)
        {
            // Find which torch is nearest the player.
            {
                // Get the distance to the player.
                float distToPlayer = DistanceBetweenPoints(playerPosition, torch->getPosition());
                if (distToPlayer < lowestDistanceToPlayer)
                {
                    lowestDistanceToPlayer = distToPlayer;
                    nearestTorch = torch;
                }
            }
        }
        distanceToPlayer = nearestTorch->getPosition();
    }

    return distanceToPlayer;
}

// Updates all items in the level.
void GameScene::UpdateItems(const sf::Vector2f playerPosition)
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
            case eITEM::GOLD:
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

            case eITEM::GEM:
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

            case eITEM::KEY:
            {
                // Unlock the door.
                m_level->UnlockDoor();

                // Play key collect sound.
                PlaySound(m_keyPickupSound);

                // Set the key as collected.
                m_keyUiSprite->setColor(sf::Color::White);
            }
            break;

            case eITEM::POTION:
            {
                // apply potion - move to other place
                // Cast to position and get type.
                Potion& potion = dynamic_cast<Potion&>(item);
                m_player->setAttack(m_player->getAttack() + potion.getAttack());
                m_player->setDefense(m_player->getDefense() + potion.getDefense());
                m_player->setStrength(m_player->getStrength() + potion.getStrength());
                m_player->setDexterity(m_player->getDexterity() + potion.getDexterity());
                m_player->setStamina(m_player->getStamina() + potion.getStamina());
            }
            break;

            case eITEM::HEART:
                // Cast to heart and get health.
                Heart& heart = dynamic_cast<Heart&>(item);

                m_player->SetHealth(m_player->getHealth() + heart.getHealth());
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
void GameScene::UpdateEnemies(const sf::Vector2f playerPosition, const float timeDelta)
{
    // Store player tile.
    const auto playerPos = m_level->locationToMapCord(playerPosition);

    auto enemyIterator = m_enemies.begin();
    while (enemyIterator != m_enemies.end())
    {
        // Create a bool so we can check if an enemy was deleted.
        bool enemyWasDeleted = false;

        // Get the enemy object from the iterator.
        Enemy& enemy = **enemyIterator;

        // Get the tile that the enemy is on.
        const auto enemyPos = m_level->locationToMapCord(enemy.getPosition());

        // Check for collisions with projectiles.
        auto projectilesIterator = m_playerProjectiles.begin();
        while (projectilesIterator != m_playerProjectiles.end())
        {
            // Get the projectile object from the iterator.
            Projectile& projectile = **projectilesIterator;

            // If the enemy and projectile occupy the same tile they have collided.
            if (enemyPos == m_level->locationToMapCord(projectile.getPosition()))
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
                        SpawnItem(Random(eITEM::GOLD), position);	// Generates a number 0 - 2
                    }

                    if (Random(4) == 0)			// 1 in 5 change of spawning health.
                    {
                        position.x += Random(-15, 15);
                        position.y += Random(-15, 15);
                        SpawnItem(eITEM::HEART, position);
                    }
                    // 1 in 5 change of spawning potion.
                    else if (Random(4) == 1)
                    {
                        position.x += Random(-15, 15);
                        position.y += Random(-15, 15);
                        SpawnItem(eITEM::POTION, position);
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

            // Check for collision with player.
            if (enemyPos == playerPos)
            {
                if (m_player->CanTakeDamage())
                {
                    m_player->Damage(10);
                    PlaySound(m_playerHitSound);
                }
            }

            enemy.invokeAI(*m_level, playerPosition);


            ++enemyIterator;
        }
    }
}

// Updates all projectiles in the level.
void GameScene::UpdateProjectiles(const float timeDelta)
{
    auto projectileIterator = m_playerProjectiles.begin();
    while (projectileIterator != m_playerProjectiles.end())
    {
        // Get the projectile object from the iterator.
        Projectile& projectile = **projectileIterator;

        // If the tile the projectile is on is not floor, delete it.
        if (!m_level->IsFloor(projectile.getPosition()))
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

//--------------------------------------------------------------------------------------------------------------------------------

// Draw the current game scene.
void GameScene::draw(sf::RenderWindow& window, const float timeDelta)
{
    // Clear the screen.
    window.clear(sf::Color(3, 3, 3, 225));		// Gray

    drawGame(window, timeDelta, eVIEW::MAIN);
    drawUI(window, timeDelta, eVIEW::UI);
}

void GameScene::drawGame(sf::RenderWindow& window, const float timeDelta, const GameScene::eVIEW viev)
{
    // Set the main game view.
    window.setView(m_views[static_cast<int>(viev)]);

    // Draw the level.
    m_level->draw(window, timeDelta);

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
    m_player->draw(window, timeDelta);

    // Draw level shadow.
    for (const sf::Sprite& shadow : m_shadowGrid)
    {
        window.draw(shadow);
    }
}

void GameScene::drawUI(sf::RenderWindow& window, const float timeDelta, const GameScene::eVIEW viev)
{
    // Switch to UI view.
    window.setView(m_views[static_cast<int>(viev)]);

    // Draw player aim.
    window.draw(m_player->GetAimSprite());

    // Draw the level goal if active.
    if (m_activeGoal)
    {
        DrawString(window, m_goalString, sf::Vector2f(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y - 75)), 30);
    }

    // Draw player stats.
    DrawString(window, std::to_string(m_player->getAttack()), sf::Vector2f(m_screenCenter.x - 210.f, m_screenSize.y - 30.f), 25);
    DrawString(window, std::to_string(m_player->getDefense()), sf::Vector2f(m_screenCenter.x - 90.f, m_screenSize.y - 30.f), 25);
    DrawString(window, std::to_string(m_player->getStrength()), sf::Vector2f(m_screenCenter.x + 30.f, m_screenSize.y - 30.f), 25);
    DrawString(window, std::to_string(m_player->getDexterity()), sf::Vector2f(m_screenCenter.x + 150.f, m_screenSize.y - 30.f), 25);
    DrawString(window, std::to_string(m_player->getStamina()), sf::Vector2f(m_screenCenter.x + 270.f, m_screenSize.y - 30.f), 25);
    DrawString(window, ToStringFormated("%.6i", m_scoreTotal), sf::Vector2f(m_screenCenter.x - 120.f, 40.f), 40);
    DrawString(window, ToStringFormated("%.5i", m_goldTotal), sf::Vector2f(m_screenCenter.x + 220.f, 40.f), 40);

    // Draw rest of the UI.
    for (const auto& sprite : m_uiSprites)
    {
        window.draw(*sprite);
    }

    // Draw the current room and floor.
    DrawString(window, ToStringFormated("Floor %d", m_level->GetFloorNumber()), sf::Vector2f(70.f, m_screenSize.y - 65.f), 25);
    DrawString(window, ToStringFormated("Room %d", m_level->GetRoomNumber()), sf::Vector2f(70.f, m_screenSize.y - 30.f), 25);

    // Draw health and mana bars.
    m_healthBarSprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>((213.f / m_player->getMaxHealth()) * m_player->getHealth()), 8));
    window.draw(*m_healthBarSprite);

    m_manaBarSprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>((213.f / m_player->GetMaxMana()) * m_player->GetMana()), 8));
    window.draw(*m_manaBarSprite);


    //DrawString(window, ToStringFormated("is paused %s", (getGame().isPaused() == true ? "true" : "false")), m_screenCenter, 25);
}


// Draw the given string at the given position.
void GameScene::DrawString(sf::RenderWindow& window, const std::string text, const sf::Vector2f position, const unsigned int size)
{
    //TODO way m_text is class member, maybe prefer local variable
    //sf::Text text;
    //text.setFont(m_font);

    m_text.setString(text);
    m_text.setCharacterSize(size);
    m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

    window.draw(m_text);
}

//--------------------------------------------------------------------------------------------------------------------------------

// Plays the given sound effect, with randomized parameters.
void GameScene::PlaySound(sf::Sound& sound, const sf::Vector2f position)
{
    // Generate and set a random pitch.
    float pitch = Random(95, 105) / 100.f;
    sound.setPitch(pitch);

    // Set the position of the sound.
    sound.setPosition(position.x, position.y, 0.f);

    // Play the sound.
    sound.play();
}