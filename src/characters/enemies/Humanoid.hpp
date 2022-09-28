#ifndef HUMANOID_H
#define HUMANOID_H

#include "characters/enemies/Enemy.hpp"

#include <string>
#include <array>


class Humanoid : public Enemy
{
	using tBase = Enemy;

public:
	explicit Humanoid(const Scene& scene);

private:
	static const std::size_t TEXTURE_COUNT = static_cast<int>(eANIMATION_STATE::COUNT);

	//TODO armor other sprite, влияет на характеристики в зависимости от типа и цвета

	// Generates random armor for the humanoid.
	void generateArmor();
	// set armor textures by type
	void setArmorTexture(const std::string& armorName, std::array<sf::RenderTexture, TEXTURE_COUNT>& armorTextures);

	// An array of modified textures.
	std::array<sf::Texture, TEXTURE_COUNT> m_textures;
};
#endif
