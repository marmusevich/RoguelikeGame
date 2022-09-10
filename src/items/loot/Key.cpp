//#include "PCH.hpp"
#include "items/loot/Key.hpp"

// Default constructor.
Key::Key(const Scene& scene)
: tBase(scene)
{
	// Set item name.
	setItemName("Key");

	// Set item type.
	m_type = eITEM::KEY;
}