//#include "PCH.hpp"
#include "core/Entity.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"

Entity::Entity(const Scene& scene)
: tBase(scene)
, m_textureIDs(static_cast<int>(eANIMATION_STATE::COUNT) )
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
void Entity::update(const float timeDelta)
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
		getSpriteWA().setTexture(getTexture(m_textureIDs[m_currentTextureIndex]));
	}
}

int Entity::getHealth() const
{
	return m_health;
}

int Entity::getMaxHealth() const
{
	return m_maxHealth;
}

int Entity::getAttack() const
{
	return m_attack;
}

int Entity::getDefense() const
{
	return m_defense;
}

int Entity::getStrength() const
{
	return m_strength;
}

int Entity::getDexterity() const
{
	return m_dexterity;
}

int Entity::getStamina() const
{
	return m_stamina;
}

void Entity::setAttack(const int attackValue)
{
	m_attack = attackValue;
}

void Entity::setDefense(const int defenseValue)
{
	m_defense = defenseValue;
}

void Entity::setStrength(const int strengthValue)
{
	m_strength = strengthValue;
}

void Entity::setDexterity(const int dexterityValue)
{
	m_dexterity = dexterityValue;
}

void Entity::setStamina(const int staminaValue)
{
	m_stamina = staminaValue;
}
