//#include "PCH.hpp"
#include "items/loot/Heart.hpp"
#include "core/manager/TextureManager.hpp"
#include "utils/MathUtils.hpp"
// Default constructor.
Heart::Heart()
{
	// Set health value.
	m_health = Random(10, 20);

	// Set item type.
	m_type = ITEM::HEART;
}

// Returns the amount of health that the heart gives.
int Heart::GetHealth() const
{
	return m_health;
}