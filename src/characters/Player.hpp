#ifndef PLAYER_H
#define PLAYER_H

#include "core/Entity.hpp"
#include "core/Input.hpp"
#include "scenes/Level.hpp"
#include "items/bullet/Projectile.hpp"

#include <string>
#include <array>

// Player traits.
enum class PLAYER_TRAIT 
{
	ATTACK,
	DEFENSE,
	STRENGTH,
	DEXTERITY,
	STAMINA,
	COUNT
};


class Player : public Entity
{
	using tBase = Entity;

	// The number of traits that the player can have.
	static const int PLAYER_TRAIT_COUNT = 2;

public:
	using tTraits = std::array<PLAYER_TRAIT, PLAYER_TRAIT_COUNT>;

	explicit Player(const Scene& scene);

	/**
	 * Updates the player object.
	 * The main purpose of this function is to update the players position.
	 * @param timeDelta The time, in MS, since the last game tick.
	 * @param level A reference to the level object.
	 */
	void update(float timeDelta, Level& level);

	/**
	 * Gets the player's current traits.
	 * @return The player's current traits.
	 */
	const tTraits& GetTraits() const;

	/**
	 * Gets the number of traits the player has.
	 */
	int GetTraitCount() const;

	/**
	* Gets the player's mana.
	* @return The player's mana.
	*/
	int GetMana() const;

	/**
	* Gets the player's max mana.
	* @return The player's max mana.
	*/
	int GetMaxMana() const;

	/**
	 * Set the player's health.
	 * @param healthValue The player's new health.
	 */
	void SetHealth(int healthValue);

	/**
	 * Set the player's mana level.
	 * @param mana The new mana value.
	 */
	void SetMana(int manaValue);

	/**
	 * Chooses random traits for the character.
	 */
	void SetRandomTraits();

	/**
	 * Gets the player's aim sprite.
	 * return The player's aim sprite.
	 */
	const sf::Sprite& GetAimSprite() const;

	/**
	 * Checks if the player is currently attacking.
	 * @return True if the player is attacking.
	 */
	bool IsAttacking();

	/**
	 * Checks if the player can take damage.
	 * @return True if the player can take damage.
	 */
	bool CanTakeDamage();

	/**
	 * Apply the given amount of damage to the player.
	 * @param damage The amount of damage to deal to the player.
	 */
	void Damage(int damage);

	const std::string getUiTextureID() const;
	const std::string getProjectileTextureID() const;

private:

	/**
	 * Checks if the given movement will result in a collision.
	 * @param movement The movement to check.
	 * @param level A reference to the level object.
	 * @return True if the given movement will result in a collision.
	 */
	bool CausesCollision(sf::Vector2f movement, Level& level);

private:
	// Player classes.
	enum class ePLAYER_CLASS
	{
		WARRIOR,
		MAGE,
		ARCHER,
		THIEF,
		COUNT
	};

	// An array containing the character's traits.
	tTraits m_traits;

	// The player's class.
	ePLAYER_CLASS m_class;

	// The sprite for the player's aim cross hair.
	sf::Sprite m_aimSprite;

	// The time since the player's last attack.
	float m_attackDelta;

	// The time since the player last took damage.
	float m_damageDelta;

	// The time since the last mana regeneration.
	float m_manaDelta;

	// Is the player attacking.
	bool m_isAttacking;

	// Can the player take damage.
	bool m_canTakeDamage;

	// The number of stat points the entities has to distribute.
	int m_statPoints;

	// The ui texture and sprite
	std::string m_uiTextureID;
	// The ID of the player's projectile texture.
	std::string m_projectileTextureID;
};
#endif