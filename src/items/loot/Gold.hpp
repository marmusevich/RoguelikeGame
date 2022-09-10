#ifndef GOLD_H
#define GOLD_H

#include "core/Item.hpp"

#include <unordered_map>

class Gold : public Item
{
	using tBase = Item;

public:
	explicit Gold(const Scene& scene);

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