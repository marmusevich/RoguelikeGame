#ifndef GEM_H
#define GEM_H

#include "core/Item.hpp"

class Gem : public Item
{
public:
	/**
	 * Default constructor.
	 */
	Gem();

	/**
	 * Gets the amount of score this pickup gives.
	 * @return The amount of score the pickup gives.
	 */
	int GetScoreValue() const;

private:
	/**
	 * The value of this gem pickup.
	 */
	int m_scoreValue;
};
#endif