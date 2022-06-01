#ifndef GOLD_H
#define GOLD_H

#include "core/Item.hpp"

#include <unordered_map>

enum class eGOLD_TEXTURE_TYPE 
{
	SMALL,
	LARGE,
	MEDIUM,
	COUNT
};


class Gold : public Item
{
public:
	/**
	 * constructor.
	 */
	explicit Gold(const std::unordered_map<eGOLD_TEXTURE_TYPE, int>& textureIDs);

	/**
	 * Gets the amount of gold this pickup has.
	 * @return The amount of gold the pickup has.
	 */
	int GetGoldValue() const;

private:
	/**
	 * The value of this gold pickup.
	 */
	int goldValue;
};
#endif