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
	const eHUMANOID humanoidType = Random(eHUMANOID::COUNT);
	std::string enemyName;

	// Set enemy specific variables.
	switch (humanoidType)
	{
	case eHUMANOID::GOBLIN:
		enemyName = "goblin";
		break;

	case eHUMANOID::SKELETON:
		enemyName = "skeleton";
		break;
	}

	// Load textures.
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = enemyName + "_spr_walk_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = enemyName + "_spr_walk_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = enemyName + "_spr_walk_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = enemyName + "_spr_walk_left";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = enemyName + "_spr_idle_up";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = enemyName + "_spr_idle_down";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = enemyName + "_spr_idle_right";
	m_textureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = enemyName + "_spr_idle_left";

	// Set initial sprite.
	setSprite(getTexture(m_textureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)]), false, 8, 12);

	// Copy textures.
	for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
	{
		m_textures_old[i] = getTexture(m_textureIDs[i]);
	}

	// Generate armor.
	GenerateArmor();
}

// Generates random armor for the humanoid.
void Humanoid::GenerateArmor()
{
	// Create arrays of textures for our armor, and the final versions.
	const int textureCount = static_cast<int>(eANIMATION_STATE::COUNT);
	sf::RenderTexture armorTextures[textureCount];
	sf::RenderTexture finalTextures[textureCount];
	sf::Image renderImage;

	// Setup all render textures.
	for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
	{
		sf::Vector2u textureSize = m_textures_old[i].getSize();

		armorTextures[i].create(textureSize.x, textureSize.y);
		finalTextures[i].create(textureSize.x, textureSize.y);
	}

	// Create variables to determine what armor be created.
	int hasHelmet(0), hasTorso(0), hasLegs(0);

	hasHelmet = Random(5);
	hasTorso = Random(5);
	hasLegs = Random(5);

	// Spawn helmet.
	if (hasHelmet == 0)
	{
		// Load the default helmet textures.
		std::unordered_map<int, std::string> defaultHelmetTextureIDs(static_cast<int>(eANIMATION_STATE::COUNT));

		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "helmet_spr_walk_front";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "helmet_spr_walk_front";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "helmet_spr_walk_side";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "helmet_spr_walk_side";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "helmet_spr_idle_front";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "helmet_spr_idle_front";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "helmet_spr_idle_side";
		defaultHelmetTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "helmet_spr_idle_side";

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
		for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
		{
			// Load the default helmet texture and set its color.
			sf::Sprite tempSprite;
			tempSprite.setTexture(getTexture(defaultHelmetTextureIDs[i]));
			tempSprite.setColor(tierColor);

			// Flip the texture vertically.
			sf::Vector2u size = armorTextures[i].getTexture().getSize();
			tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

			// Draw the texture.
			armorTextures[i].draw(tempSprite);
		}
	}

	// Spawn torso.
	if (hasTorso == 0)
	{
		// Load the default torso textures.
		std::unordered_map<int, std::string> defaultTorsoTextureIDs(static_cast<int>(eANIMATION_STATE::COUNT));

		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "torso_spr_walk_front";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "torso_spr_walk_front";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "torso_spr_walk_side";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "torso_spr_walk_side";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "torso_spr_idle_front";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "torso_spr_idle_front";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "torso_spr_idle_side";
		defaultTorsoTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "torso_spr_idle_side";

		// Generate random number to determine tier.
		sf::Color tierColor;
		const int tierValue = Random(1, 100);

		// Select which tier armor should we created.
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

		// Render torso to armor texture.
		for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
		{
			sf::Sprite tempSprite;
			tempSprite.setTexture(getTexture(defaultTorsoTextureIDs[i]));
			tempSprite.setColor(tierColor);

			// Flip the texture vertically.
			sf::Vector2u size = armorTextures[i].getTexture().getSize();
			tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

			// Draw the texture.
			armorTextures[i].draw(tempSprite);
		}
	}

	// Spawn legs.
	if (hasLegs == 0)
	{
		// Load the default legs textures.
		std::unordered_map<int, std::string> defaultLegsTextureIDs(static_cast<int>(eANIMATION_STATE::COUNT));

		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_UP)] = "legs_spr_walk_front";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_DOWN)] = "legs_spr_walk_front";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_RIGHT)] = "legs_spr_walk_side";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::WALK_LEFT)] = "legs_spr_walk_side";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_UP)] = "legs_spr_idle_front";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_DOWN)] = "legs_spr_idle_front";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_RIGHT)] = "legs_spr_idle_side";
		defaultLegsTextureIDs[static_cast<int>(eANIMATION_STATE::IDLE_LEFT)] = "legs_spr_idle_side";

		// Generate random number to determine tier.
		sf::Color tierColor;
		const int tierValue = Random(1, 100);

		// Select which tier armor should we created.
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

		// Render legs to armor texture.
		for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
		{
			sf::Sprite tempSprite;
			tempSprite.setTexture(getTexture(defaultLegsTextureIDs[i]));
			tempSprite.setColor(tierColor);

			// Flip the texture vertically.
			sf::Vector2u size = armorTextures[i].getTexture().getSize();
			tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

			// Draw the texture.
			armorTextures[i].draw(tempSprite);
		}
	}

	// Create the final textures.
	for (int i = 0; i < static_cast<int>(eANIMATION_STATE::COUNT); i++)
	{
		sf::Sprite baseSprite, armorSprite;

		// Draw the default texture.
		baseSprite.setTexture(m_textures_old[i]);
		finalTextures[i].draw(baseSprite);

		// Draw armor on top.
		armorSprite.setTexture(armorTextures[i].getTexture());
		finalTextures[i].draw(armorSprite);

		// Flip the texture vertically.
		sf::Image img = finalTextures[i].getTexture().copyToImage();
		img.flipVertically();

		// Store the resulting texture.
		m_textures_old[i].loadFromImage(img);
	}
}

// Overrides the update event of Enemy.
void Humanoid::update(float timeDelta)
{
	// Call parent functionality.
	Enemy::update(timeDelta);

	// update the texture with our custom textures.
	m_sprite.setTexture(m_textures_old[m_currentTextureIndex]);
}