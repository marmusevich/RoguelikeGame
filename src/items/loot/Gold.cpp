//#include "PCH.hpp"
#include "items/loot/Gold.hpp"
#include "core/manager/TextureManager.hpp"
#include "utils/MathUtils.hpp"


Gold::Gold()
{
	// Randomly generate the value of the pickup.
	this->goldValue = Random(5, 25);

	// Choose a sprite based on the gold value.
	if (this->goldValue < 9)
	{
		this->setSprite(TextureManager::GetTexture(TextureManager::AddTexture("resources/loot/gold/spr_pickup_gold_small.png")), false, 8, 12);
	}
	else if (this->goldValue >= 16)
	{
		this->setSprite(TextureManager::GetTexture(TextureManager::AddTexture("resources/loot/gold/spr_pickup_gold_large.png")), false, 8, 12);
	}
	else
	{
		this->setSprite(TextureManager::GetTexture(TextureManager::AddTexture("resources/loot/gold/spr_pickup_gold_medium.png")), false, 8, 12);
	}

	// Set the item type.
	m_type = eITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
	return this->goldValue;
}