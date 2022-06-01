#ifndef ENEMY_H
#define ENEMY_H

#include "core/Entity.hpp"
#include "scenes/Level.hpp"

// Enemy types.
enum class eENEMY 
{
	SLIME,
	HUMANOID,
	COUNT
};


class Enemy : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Enemy();

	/**
	 * Overrides the default update function of Entity.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	virtual void update(float timeDelta) override;

	/**
	 * Recalculates the enemies path finding.
	 * @param level A reference to the level object.
	 * @param playerPosition The position of the player within the level.
	 */
	void UpdatePathfinding(Level& level, sf::Vector2f playerPosition);

	/**
	 * Applies the given amount of damage to the enemy.
	 * @param damage The amount of damage to deal to the enemy.
	 */
	void Damage(int damage);

	/**
	 * Checks if the enemy has taken enough damage that they are now dead.
	 * @return True if the enemy is dead.
	 */
	bool IsDead();

protected:
	/**
	 * The target position of the enemy.
	 */
	std::vector<sf::Vector2f> m_targetPositions;

	/**
	 * The current target of the enemy.
	 */
	sf::Vector2f m_currentTarget;
};
#endif