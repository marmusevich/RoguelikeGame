#ifndef ENTITY_H
#define ENTITY_H

#include "core/Object.hpp"

#include <array>


// Animation states.
enum class eANIMATION_STATE
{
	WALK_UP,
	WALK_DOWN,
	WALK_RIGHT,
	WALK_LEFT,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	COUNT
};



class Entity : public Object
{
	using tBase = Object;

public:

	explicit Entity(const Scene& scene);

	/**
	 * Override the default Object::update function.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	virtual void update(float timeDelta) override;

	/**
	 * Gets the entities health.
	 * @return The entities health.
	 */
	int getHealth() const;

	/**
	 * Gets the entities max health.
	 * @return The entities max health.
	 */
	int getMaxHealth() const;

	/**
	 * Gets the entities attack.
	 * @return The entities attack.
	 */
	int getAttack() const;

	/**
	 * Gets the entities defense.
	 * @return The entities defense.
	 */
	int getDefense() const;

	/**
	 * Gets the entities strength.
	 * @return The entities strength.
	 */
	int getStrength() const;

	/**
	 * Gets the entities dexterity.
	 * @return The entities dexterity.
	 */
	int getDexterity() const;

	/**
	 * Gets the entities stamina.
	 * @return The entities stamina.
	 */
	int getStamina() const;

	/**
	 * Sets the entities attack stat.
	 * @param attackValue The player's new attack stat value.
	 */
	void setAttack(int attackValue);

	/**
	 * Sets the entities defense stat.
	 * @param defenseValue The player's new defense stat value.
	*/
	 void setDefense(int defenseValue);

	/**
	 * Sets the entities strength stat.
	 * @param strengthValue The player's new strength stat value.
	 */
	void setStrength(int strengthValue);

	/**
	 * Sets the entities dexterity stat.
	 * @param dexterityValue The player's new dexterity stat value.
	 */
	void setDexterity(int dexterityValue);

	/**
	 * Sets the entities stamina stat.
	 * @param staminaValue The player's new stamina stat value.
	 */
	void setStamina(int staminaValue);

	int getCurrentTextureIndex();

protected:
	/**
	 * A vector of all texture IDs.
	 */
	std::array<int, static_cast<int>(eANIMATION_STATE::COUNT)> m_textureIDs;

	/**
	 * The index of the current texture.
	 */
	int m_currentTextureIndex;

	/**
	 * The entities current health.
	 */
	int m_health;

	/**
	 * The entities maximum health.
	 */
	int m_maxHealth;

	/**
	 * The entities current mana.
	 */
	int m_mana;

	/**
	 * The entities maximum mana.
	 */
	int m_maxMana;

	/**
	 * The entities attack stat. Effects damage dealt.
	 */
	int m_attack;

	/**
	 * The entities defense stat. Effects damage taken.
	 */
	int m_defense;

	/**
	 * The entities strength. Effects damage dealt.
	 */
	int m_strength;

	/**
	 * The entities dexterity. Effects movement speed.
	 */
	int m_dexterity;

	/**
	 * The entities stamina. Effects health.
	 */
	int m_stamina;

	/**
	 * The entities movement speed.
	 */
	int m_speed;

	/**
	 * The entities current velocity.
	 */
	sf::Vector2f m_velocity;
};
#endif