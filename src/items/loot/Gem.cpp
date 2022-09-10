#include "items/loot/Gem.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"
#include "utils/MathUtils.hpp"

Gem::Gem(const Scene& scene)
: tBase(scene)
{
	// Set the value of the gem.
	m_scoreValue = Random(100);

	// Set the item type.
	m_type = eITEM::GEM;
}

// Gets the amount of score this pickup gives.
int Gem::GetScoreValue() const
{
	return m_scoreValue;
}