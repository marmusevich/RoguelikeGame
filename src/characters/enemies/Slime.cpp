//#include "PCH.hpp"
#include "characters/enemies/Slime.hpp"
#include "utils/MathUtils.hpp"

Slime::Slime(const Scene& scene)
: tBase(scene)
{
	// Load textures.
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "slime_spr_walk_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "slime_spr_walk_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "slime_spr_walk_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "slime_spr_walk_left";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "slime_spr_idle_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "slime_spr_idle_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "slime_spr_idle_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "slime_spr_idle_left";

	// Set initial sprite.
	setSprite(getTexture(m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)]), false, 8, 12);
	// Choose the random sprite color and set it.
	m_sprite.setColor(RandomColor(100u, 255u));

	// Generate a random scale between 0.5 and 1.5 and set it.
	const float scale = Random(5, 15) / 10.0f;
	m_sprite.setScale(sf::Vector2f(scale, scale));
}