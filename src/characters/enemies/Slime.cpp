//#include "PCH.hpp"
#include "characters/enemies/Slime.hpp"
#include "utils/MathUtils.hpp"

Slime::Slime(const Scene& scene)
: tBase(scene)
{
	// Set textures.
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "spr_slime_walk_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "spr_slime_walk_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "spr_slime_walk_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "spr_slime_walk_left";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "spr_slime_idle_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "spr_slime_idle_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "spr_slime_idle_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "spr_slime_idle_left";

	// Set initial sprite.
	setSprite(getTexture(m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)]), 8, 12);
	// Choose the random sprite color and set it.
	getSpriteWA().setColor(RandomColor(100u, 255u));

	// Generate a random scale between 0.5 and 1.5 and set it.
	const float scale { Random(5, 15) / 10.0f };
	getSpriteWA().setScale(sf::Vector2f(scale, scale));
}