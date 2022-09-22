#include "items/bullet/Projectile.hpp"

// Default constructor.
Projectile::Projectile(const Scene& scene, const std::string& textureId, const sf::Vector2f origin, const sf::Vector2f screenCenter, const sf::Vector2f target)
	: tBase(scene)
{
	// Create the sprite.
	setSprite(textureId, false);

	// Set the sprite position.
	m_sprite.setPosition(origin);

	// Set the position.
	m_position = origin;

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
	m_sprite.setRotation(m_sprite.getRotation() + (400.f * timeDelta));

	// update position.
	m_sprite.setPosition(m_sprite.getPosition().x + (m_velocity.x * (500 * timeDelta)), m_sprite.getPosition().y + (m_velocity.y * (500 * timeDelta)));
	m_position = m_sprite.getPosition();
}