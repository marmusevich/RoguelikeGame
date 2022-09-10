#include "items/loot/Heart.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"
#include "utils/MathUtils.hpp"

Heart::Heart(const Scene& scene)
: tBase(scene)
{
	// Set health value.
	m_health = Random(10, 20);

	// Set item type.
	m_type = eITEM::HEART;
}

// Returns the amount of health that the heart gives.
int Heart::getHealth() const
{
	return m_health;
}