//-------------------------------------------------------------------------------------
#ifndef POTION_H
#define POTION_H

#include "core/Item.hpp"

#include <unordered_map>


// Potions.
enum class ePOTION 
{
	ATTACK,
	DEFENSE,
	STRENGTH,
	DEXTERITY,
	STAMINA,
	COUNT
};


class Potion : public Item
{
public:
	/**
	* constructor.
	*/
	explicit Potion(const std::unordered_map<ePOTION, int>& textureIDs);

	/**
	 * Gets the potion type.
	 * @return The potion type.
	 */
	ePOTION GetPotionType() const;

	/**
	 * Gets the attack value of the potion.
	 * @return The attack value the potion gives.
	 */
	int getAttack() const;

	/**
	 * Gets the defense value of the potion.
	 * @return The defense value the potion gives.
	 */
	int getDefense() const;

	/**
	 * Gets the strength value of the potion.
	 * @return The strength value the potion gives.
	 */
	int getStrength() const;

	/**
	 * Gets the dexterity value of the potion.
	 * @return The dexterity value the potion gives.
	 */
	int getDexterity() const;

	/**
	 * Gets the stamina value of the potion.
	 * @return The stamina value the potion gives.
	 */
	int getStamina() const;

private:
	/**
	 * The potion type.
	 */
	ePOTION m_potionType;

	/**
	 * The attack value of the potion.
	 */
	int m_attack;

	/**
	 * The defense value of the potion.
	 */
	int m_defense;

	/**
	* The strength value of the potion.
	*/
	int m_strength;

	/**
	 * The dexterity value of the potion.
	 */
	int m_dexterity;

	/**
	 * The stamina value of the potion.
	 */
	int m_stamina;
};
#endif