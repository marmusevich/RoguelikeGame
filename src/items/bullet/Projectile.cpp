#include "items/bullet/Projectile.hpp"

// Default constructor.
Projectile::Projectile(const Scene& scene, const std::string& textureId, const sf::Vector2f origin, const sf::Vector2f screenCenter, const sf::Vector2f target)
	: tBase(scene)
{
	// Create the sprite.
	setSprite(textureId);

	// Set the sprite position.
	setPosition(origin);
	
	// Calculate the velocity of the object.
	m_velocity = target - screenCenter;

	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity.x /= length;
	m_velocity.y /= length;
}

// update the projectile.
void Projectile::update(const float timeDelta)
{
	// update rotation.
	getSpriteWA().setRotation(getSpriteWA().getRotation() + (400.f * timeDelta));

	// update position.
	const auto newPos = getPosition() + m_velocity * (500 * timeDelta);
	setPosition(newPos);
}