//#include "PCH.hpp"
#include "characters/Player.hpp"
#include "core/Scene.hpp"
#include "utils/MathUtils.hpp"

//old
#include "core/manager/TextureManager.hpp"


// Constructor.
Player::Player(const Scene& scene)
: m_attackDelta(0.f)
, m_damageDelta(0.f)
, m_manaDelta(0.f)
, m_isAttacking(false)
, m_canTakeDamage(true)
, m_statPoints(0)
, m_uiTextureID("")
, m_projectileTextureID("")
{
	// Generate a random class.
	m_class = Random(ePLAYER_CLASS::COUNT);
	std::string className;

	// Set class-specific variables.
	switch (m_class)
	{
	case ePLAYER_CLASS::WARRIOR:
		m_strength += Random(5, 10);
		className = "warrior";
		m_projectileTextureID = "resources/projectiles/spr_sword.png";
		break;

	case ePLAYER_CLASS::MAGE:
		m_defense = Random(5, 10);
		className = "mage";
		m_projectileTextureID = "resources/projectiles/spr_magic_ball.png";
		break;

	case ePLAYER_CLASS::ARCHER:
		m_dexterity = Random(5, 10);
		className = "archer";
		m_projectileTextureID = "resources/projectiles/spr_arrow.png";
		break;

	case ePLAYER_CLASS::THIEF:
		m_stamina = Random(5, 10);
		className = "thief";
		m_projectileTextureID = "resources/projectiles/spr_dagger.png";
		break;
	}

	// Load textures.
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("resources/players/" + className + "/spr_walk_up.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("resources/players/" + className + "/spr_walk_down.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("resources/players/" + className + "/spr_walk_right.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("resources/players/" + className + "/spr_walk_left.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("resources/players/" + className + "/spr_idle_up.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("resources/players/" + className + "/spr_idle_down.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("resources/players/" + className + "/spr_idle_right.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("resources/players/" + className + "/spr_idle_left.png");

	// Load the correct projectile texture.
	scene.getResourceManager().mTexture->loadFromFile(m_projectileTextureID, m_projectileTextureID);

	// Initialize the player ui texture and sprite.
    m_uiTextureID = "resources/ui/spr_" + className + "_ui.png";
	scene.getResourceManager().mTexture->loadFromFile(m_uiTextureID, m_uiTextureID);

	// Set initial sprite.
	setSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)]), false, 8, 12);
	m_currentTextureIndex = static_cast<int>(eANIMATION_STATE::WALK_UP);
	m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));

	// Create the player's aim sprite.
	int textureID = TextureManager::AddTexture("resources/ui/spr_aim.png");
	m_aimSprite.setTexture(scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_aim"));
	m_aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
	m_aimSprite.setScale(2.f, 2.f);

	// Set random traits.
	SetRandomTraits();

	// Set fixed stats.
	m_health = m_maxHealth = 100;
	m_mana = m_maxMana = 50;
	m_speed = 200;

	// Randomly distribute other stats.
	m_statPoints = 50;

	int attackBias = Random(100);
	int defenseBias = Random(100);
	int strengthBias = Random(100);
	int dexterityBias = Random(100);
	int staminaBias = Random(100);

	int total = attackBias + defenseBias + strengthBias + dexterityBias + staminaBias;

	m_attack += m_statPoints * (attackBias / total);
	m_defense += m_statPoints * (defenseBias / total);
	m_strength += m_statPoints * (strengthBias / total);
	m_dexterity += m_statPoints * (dexterityBias / total);
	m_stamina += m_statPoints * (staminaBias / total);
}

// Updates the player object.
void Player::update(float timeDelta, Level& level)
{
	// Calculate movement speed based on the timeDelta since the last update.
	sf::Vector2f movementSpeed(0.f, 0.f);
	sf::Vector2f previousPosition = m_position;

	// Calculate where the current movement will put us.
	eANIMATION_STATE animState = static_cast<eANIMATION_STATE>(m_currentTextureIndex);

	if (Input::IsKeyPressed(Input::eKEY::KEY_LEFT))
	{
		// Set movement speed.
		movementSpeed.x = -m_speed * timeDelta;

		// Chose animation state.
		animState = eANIMATION_STATE::WALK_LEFT;
	}
	else if (Input::IsKeyPressed(Input::eKEY::KEY_RIGHT))
	{
		// Set movement speed.
		movementSpeed.x = m_speed * timeDelta;

		// Chose animation state.
		animState = eANIMATION_STATE::WALK_RIGHT;
	}

	if (Input::IsKeyPressed(Input::eKEY::KEY_UP))
	{
		// Set movement speed.
		movementSpeed.y = -m_speed * timeDelta;

		// Chose animation state.
		animState = eANIMATION_STATE::WALK_UP;
	}
	else if (Input::IsKeyPressed(Input::eKEY::KEY_DOWN))
	{
		// Set movement speed.
		movementSpeed.y = m_speed * timeDelta;

		// Chose animation state.
		animState = eANIMATION_STATE::WALK_DOWN;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
	{
		m_position.x = previousPosition.x;
	}
	else
	{
		m_position.x += movementSpeed.x;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
	{
		m_position.y = previousPosition.y;
	}
	else
	{
		m_position.y += movementSpeed.y;
	}

	// update the sprite position
	m_sprite.setPosition(m_position);

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}

	// set animation speed
	if ((movementSpeed.x == 0) && (movementSpeed.y == 0))
	{
		// the character is still
		if (isAnimated())
		{
			// update sprite to idle version.
			// In our enum we have 4 walking sprites followed by 4 idle sprites.
			// Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
			m_currentTextureIndex += 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Stop movement animations.
			setAnimated(false);
		}
	}
	else
	{
		// the character is moving
		if (!isAnimated())
		{
			// update sprite to walking version.
			//m_currentTextureIndex -= 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Start movement animations.
			setAnimated(true);
		}
	}

	// Calculate aim based on mouse.
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	m_aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

	// Check if shooting.
	if ((m_attackDelta += timeDelta) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::eKEY::KEY_ATTACK))
		{
			// Mark player as attacking.
			m_isAttacking = true;
		}
	}

	// Determine if the player can take damage.
	if (!m_canTakeDamage)
	{
		if ((m_damageDelta += timeDelta) > 1.f)
		{
			m_canTakeDamage = true;
			m_damageDelta = 0.f;
		}
	}

	// Increase player mana.
	if ((m_manaDelta += timeDelta) > 0.20)
	{
		if (m_mana < m_maxMana)
		{
			m_mana += 1;
		}

		m_manaDelta = 0.f;
	}
}

// Chooses random traits for the character.
void Player::SetRandomTraits()
{
	// Generate the traits.
	for (int i = 0; i < PLAYER_TRAIT_COUNT; ++i)
		m_traits[i] = Random(PLAYER_TRAIT::COUNT);

	// Action the traits.
	for (PLAYER_TRAIT trait : m_traits)
	{
		switch (trait)
		{
		case PLAYER_TRAIT::ATTACK: default:
			m_attack += Random(5, 10);
			break;

		case PLAYER_TRAIT::DEFENSE:
			m_defense += Random(5, 10);
			break;

		case PLAYER_TRAIT::STRENGTH:
			m_strength += Random(5, 10);
			break;

		case PLAYER_TRAIT::DEXTERITY:
			m_dexterity += Random(5, 10);
			break;

		case PLAYER_TRAIT::STAMINA:
			m_stamina += Random(5, 10);
			break;
		}
	}
}

// Return the players traits.
PLAYER_TRAIT* Player::GetTraits()
{
	return &m_traits[0];
}

// Returns the number of traits the player has.
int Player::GetTraitCount() const
{
	return PLAYER_TRAIT_COUNT;
}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
	return m_aimSprite;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
	if (m_isAttacking)
	{
		m_isAttacking = false;
		m_attackDelta = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Checks if the player can take damage.
bool Player::CanTakeDamage()
{
	return m_canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
	m_health -= damage;

	if (m_health < 0)
	{
		m_health = 0;
	}

	m_canTakeDamage = false;
}

// Checks is the given movement will result in a collision.
bool Player::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
	Tile* overlappingTiles[4];
	sf::Vector2f newPosition = m_position + movement;

	// Top left.
	overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

	// Top right.
	overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

	// Bottom left.
	overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

	// Bottom right.
	overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

	// If any of the overlapping tiles are solid there was a collision.
	for (int i = 0; i < 4; i++)
	{
		if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
			return true;
	}

	// If we've not returned yet no collisions were found.
	return false;
}

// Gets the player's mana.
int Player::GetMana() const
{
	return m_mana;
}

// Gets the player's max mana.
int Player::GetMaxMana() const
{
	return m_maxMana;
}

// Set the player's mana level.
void Player::SetMana(int manaValue)
{
	if (manaValue >= 0)
	{
		m_mana = manaValue;
	}
}

// Set the player's health.
void Player::SetHealth(int healthValue)
{
	m_health = healthValue;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

const std::string Player::getUiTextureID() const
{
	return m_uiTextureID;
}

const std::string Player::getProjectileTextureID() const
{
	return m_projectileTextureID;
}