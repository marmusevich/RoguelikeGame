#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "core/Object.hpp"

#include <string>

class Projectile : public Object
{
	using tBase = Object;

public:
	/**
	 * Default constructor.
	 * @param texture The texture of the projectile.
	 * @param origin The location that the projectile should be created at.
	 * @param screenCenter The center of the screen. Used to calculate direction.
	 * @param target The target location of the projectile.
	 */
	explicit Projectile(const Scene& scene, const std::string& textureId, const sf::Vector2f origin, const sf::Vector2f screenCenter, const sf::Vector2f target);

	/**
	 * Override of the update function.
	 * @param timeDelta The time in seconds since the last update.
	 */
	void update(const float timeDelta) override;

private:
	/**
	 * The velocity of the projectile.
	 */
	sf::Vector2f m_velocity;
};
#endif