//#include "PCH.hpp"
#include "items/loot/Key.hpp"
#include "manager\TextureManager.hpp"

// Default constructor.
Key::Key()
{
	// Set item name.
	SetItemName("Key");

	// Set item type.
	m_type = ITEM::KEY;
}