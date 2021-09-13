#ifndef HUMANOID_H
#define HUMANOID_H

#include "characters/enemies/Enemy.hpp"

class Humanoid : public Enemy
{
public:

	/**
	 * Default constructor
	 */
	Humanoid();

	/**
	 * Overrides the update event of Enemy.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	void update(float timeDelta) override;

private:

	/**
	 * Generates random armor for the humanoid.
	 */
	void GenerateArmor();

private:

	/**
	 * An array of modified textures.
	 */
	sf::Texture m_textures_old[static_cast<int>(ANIMATION_STATE::COUNT)];
};
#endif