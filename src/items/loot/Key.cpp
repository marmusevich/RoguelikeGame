#include "items/loot/Key.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"

// Default constructor.
Key::Key(const Scene& scene)
: tBase(scene)
{
	// Set item name.
	setItemName("Key");

	// Set item type.
	m_type = eITEM::KEY;
}