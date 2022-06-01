//#include "PCH.hpp"
#include "items/loot/Potion.hpp"
#include "core/manager/TextureManager.hpp"
#include "utils/MathUtils.hpp"

// Default constructor.
Potion::Potion(const std::unordered_map<ePOTION, int>& textureIDs) :
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0)
{
	// Set the potion type.
	m_potionType = Random(ePOTION::COUNT);

	// Set stat modifiers, sprite file path, and item name.
	switch (m_potionType)
	{
	case ePOTION::ATTACK:
		m_dexterity = Random(5, 15);
		break;

	case ePOTION::DEFENSE:
		m_dexterity = Random(5, 15);
		break;

	case ePOTION::STRENGTH:
		m_strength = Random(5, 15);
		break;

	case ePOTION::DEXTERITY:
		m_dexterity = Random(5, 15);
		break;

	case ePOTION::STAMINA:
		m_stamina = Random(5, 15);
		break;
	}

	// Load and set sprite.
	setSprite(TextureManager::GetTexture(textureIDs.at(m_potionType)), false, 8, 12);

	// Set the item type.
	m_type = eITEM::POTION;
}

// Gets the potion type.
ePOTION Potion::GetPotionType() const
{
	return m_potionType;
}

// Gets the attack value of the potion.
int Potion::getAttack() const
{
	return m_attack;
}

// Gets the defense value of the potion.
int Potion::getDefense() const
{
	return m_defense;
}

// Gets the strength value of the potion.
int Potion::getStrength() const
{
	return m_strength;
}

// Gets the dexterity value of the potion.
int Potion::getDexterity() const
{
	return m_dexterity;
}

// Gets the stamina value of the potion.
int Potion::getStamina() const
{
	return m_stamina;
}