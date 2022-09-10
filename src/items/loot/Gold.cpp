//#include "PCH.hpp"
#include "items/loot/Gold.hpp"
#include "core/Scene.hpp"

#include "utils/MathUtils.hpp"


Gold::Gold(const Scene& scene)
: tBase(scene)
{
	// Randomly generate the value of the pickup.
	this->goldValue = Random(5, 25);

	// Choose a sprite based on the gold value.
	if (this->goldValue < 9)
	{
		setSprite(scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_pickup_gold_small"), false, 8, 12);
	}
	else if (this->goldValue >= 16)
	{
		setSprite(scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_pickup_gold_large"), false, 8, 12);
	}
	else
	{
		setSprite(scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>("spr_pickup_gold_medium"), false, 8, 12);
	}

	// Set the item type.
	m_type = eITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
	return this->goldValue;
}