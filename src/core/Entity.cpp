//#include "PCH.hpp"
#include "core/Entity.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"

//old
#include "core/manager/TextureManager.hpp"


Entity::Entity(const Scene& scene)
: tBase(scene)
, m_currentTextureIndex(static_cast<int>(eANIMATION_STATE::WALK_DOWN))
, m_health(0)
, m_maxHealth(0)
, m_mana(0)
, m_maxMana(0)
, m_attack(0)
, m_defense(0)
, m_strength(0)
, m_dexterity(0)
, m_stamina(0)
, m_speed(0)
, m_velocity({0.f, 0.f})
{
}

// Override the default Object::update function.
void Entity::update(float timeDelta)
{
	// Choose animation state.
	eANIMATION_STATE animState = static_cast<eANIMATION_STATE>(m_currentTextureIndex);

	if ((m_velocity.x != 0) || (m_velocity.y != 0))
	{
		if (abs(m_velocity.x) > abs(m_velocity.y))
		{
			if (m_velocity.x <= 0)
			{
				animState = eANIMATION_STATE::WALK_LEFT;
			}
			else
			{
				animState = eANIMATION_STATE::WALK_RIGHT;
			}
		}
		else
		{
			if (m_velocity.y <= 0)
			{
				animState = eANIMATION_STATE::WALK_UP;
			}
			else
			{
				animState = eANIMATION_STATE::WALK_DOWN;
			}
		}
	}

	// Set animation speed.
	if ((m_velocity.x == 0) && (m_velocity.y == 0))
	{
		// The character is still.
		if (isAnimated())
		{
			// update sprite to idle version.
			m_currentTextureIndex += 4;

			// Stop movement animations.
			setAnimated(false);
		}
	}
	else
	{
		// The character is moving.
		if (!isAnimated())
		{
			// update sprite to walking version.
			m_currentTextureIndex -= 4;

			// Start movement animations.
			setAnimated(true);
		}
	}

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}
}

// Gets the entities health.
int Entity::getHealth() const
{
	return m_health;
}

// Gets the entities max health.
int Entity::getMaxHealth() const
{
	return m_maxHealth;
}

// Gets the entities attack.
int Entity::getAttack() const
{
	return m_attack;
}

// Gets the entities defense.
int Entity::getDefense() const
{
	return m_defense;
}

// Gets the entities strength.
int Entity::getStrength() const
{
	return m_strength;
}

// Gets the entities dexterity.
int Entity::getDexterity() const
{
	return m_dexterity;
}

// Gets the entities stamina.
int Entity::getStamina() const
{
	return m_stamina;
}

// Sets the entities attack stat.
void Entity::setAttack(int attackValue)
{
	m_attack = attackValue;
}

// Sets the entities defense stat.
void Entity::setDefense(int defenseValue)
{
	m_defense = defenseValue;
}

// Sets the entities strength stat.
void Entity::setStrength(int strengthValue)
{
	m_strength = strengthValue;
}

// Sets the entities dexterity stat.
void Entity::setDexterity(int dexterityValue)
{
	m_dexterity = dexterityValue;
}

// Sets the entities stamina stat.
void Entity::setStamina(int staminaValue)
{
	m_stamina = staminaValue;
}

int Entity::getCurrentTextureIndex()
{
	return m_currentTextureIndex;
}