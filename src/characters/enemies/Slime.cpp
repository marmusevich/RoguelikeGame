//#include "PCH.hpp"
#include "characters/enemies/Slime.hpp"
#include "core/manager/TextureManager.hpp"
#include "utils/MathUtils.hpp"

Slime::Slime()
{
	// Load textures.
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_walk_up.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_walk_down.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_walk_right.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_walk_left.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_idle_up.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_idle_down.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_idle_right.png");
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("resources/enemies/slime/spr_slime_idle_left.png");

	// Set initial sprite.
	setSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)]), false, 8, 12);

	// Choose the random sprite color and set it.
	m_sprite.setColor(RandomColor(100u, 255u));

	// Generate a random scale between 0.5 and 1.5 and set it.
	const float scale = Random(5, 15) / 10.0f;
	m_sprite.setScale(sf::Vector2f(scale, scale));
}