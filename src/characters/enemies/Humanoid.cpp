#include "characters/enemies/Humanoid.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"
#include "utils/MathUtils.hpp"

#include <unordered_map>

Humanoid::Humanoid(const Scene& scene)
: tBase(scene)
{
	// Enemy humanoid types.
	enum class eHUMANOID
	{
		GOBLIN,
		SKELETON,
		COUNT
	};

	// Generate a humanoid type. (Skeleton or Goblin)
	std::string enemyName;
	switch (static_cast<eHUMANOID>(Random(eHUMANOID::COUNT)))
	{
	case eHUMANOID::GOBLIN:
		enemyName = "goblin";
		break;

	case eHUMANOID::SKELETON:
		enemyName = "skeleton";
		break;
	}

	// Load textures.
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "spr_" + enemyName + "_walk_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "spr_" + enemyName + "_walk_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "spr_" + enemyName + "_walk_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "spr_" + enemyName + "_walk_left";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "spr_" + enemyName + "_idle_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "spr_" + enemyName + "_idle_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "spr_" + enemyName + "_idle_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "spr_" + enemyName + "_idle_left";

	// Set initial sprite.
	setSprite(getTexture(m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)]), false, 8, 12);

	// Copy textures.
	for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
	{
		m_textures[i] = getTexture(m_textureIDs[i]);
	}

	// Generate armor.
	generateArmor();
}

void Humanoid::setArmorTexture(const std::string& armorName, std::array<sf::RenderTexture, TEXTURE_COUNT>& armorTextures)
{
	// Load the default helmet textures.
	std::unordered_map<int, std::string> textureIDs(TEXTURE_COUNT);
	textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "spr_" + armorName + "_walk_front";
	textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "spr_"+ armorName +"_walk_front";
	textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "spr_" + armorName + "_walk_side";
	textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "spr_" + armorName + "_walk_side";
	textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "spr_" + armorName + "_idle_front";
	textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "spr_" + armorName + "_idle_front";
	textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "spr_" + armorName + "_idle_side";
	textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "spr_" + armorName + "_idle_side";

	// Generate random number to determine tier.
	sf::Color tierColor;
	const int tierValue = Random(1, 100);
	// Select which tier armor should be created.
	if (tierValue < 51)
	{
		tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
	}
	else if (tierValue < 86)
	{
		tierColor = sf::Color(209, 208, 201, 255);	// Silver.
	}
	else
	{
		tierColor = sf::Color(229, 192, 21, 255);	// Gold.
	}

	// Render helmet to armor texture.
	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		// Load the default helmet texture and set its color.
		sf::Sprite tempSprite;
		tempSprite.setTexture(getTexture(textureIDs[i]));
		tempSprite.setColor(tierColor);

		// Flip the texture vertically.
		const sf::Vector2u size{ armorTextures[i].getTexture().getSize() };
		tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

		// Draw the texture.
		armorTextures[i].draw(tempSprite);
	}
}

// Generates random armor for the humanoid.
void Humanoid::generateArmor()
{
	// Create arrays of textures for our armor, and the final versions.
	std::array<sf::RenderTexture, TEXTURE_COUNT> armorTextures;
	std::array<sf::RenderTexture, TEXTURE_COUNT> finalTextures;

	// Setup all render textures.
	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		const sf::Vector2u textureSize{ m_textures[i].getSize() };

		armorTextures[i].create(textureSize.x, textureSize.y);
		finalTextures[i].create(textureSize.x, textureSize.y);
	}

	// Spawn helmet if has ( one of 5).
	if (Random(5) == 0)
	{
		setArmorTexture("helmet", armorTextures);
	}
	// Spawn torso if has ( one of 5).
	if (Random(5) == 0)
	{
		setArmorTexture("torso", armorTextures);
	}
	// Spawn legs if has ( one of 5).
	if (Random(5) == 0)
	{
		setArmorTexture("legs", armorTextures);
	}

	// Create the final textures.
	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		sf::Sprite baseSprite;
		sf::Sprite armorSprite;

		// Draw the default texture.
		baseSprite.setTexture(m_textures[i]);
		finalTextures[i].draw(baseSprite);

		// Draw armor on top.
		armorSprite.setTexture(armorTextures[i].getTexture());
		finalTextures[i].draw(armorSprite);

		// Flip the texture vertically.
		sf::Image img{ finalTextures[i].getTexture().copyToImage() };
		img.flipVertically();

		// Store the resulting texture.
		m_textures[i].loadFromImage(img);
	}
}

// Overrides the update event of Enemy.
void Humanoid::update(float timeDelta)
{
	// Call parent functionality.
	Enemy::update(timeDelta);

	// update the texture with our custom textures.
	m_sprite.setTexture(m_textures[m_currentTextureIndex]);
}