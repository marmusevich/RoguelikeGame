//#include "PCH.hpp"
#include "items/loot/Gold.hpp"
#include "core/manager/TextureManager.hpp"
#include "utils/MathUtils.hpp"


Gold::Gold(const std::unordered_map<eGOLD_TEXTURE_TYPE, int>& textureIDs)
{
	// Randomly generate the value of the pickup.
	this->goldValue = Random(5, 25);

	// Choose a sprite based on the gold value.
	eGOLD_TEXTURE_TYPE type = eGOLD_TEXTURE_TYPE::MEDIUM;
	if (this->goldValue < 9)
	{
		type = eGOLD_TEXTURE_TYPE::SMALL;
	}
	else if (this->goldValue >= 16)
	{
		type = eGOLD_TEXTURE_TYPE::LARGE;
	}

	// Set the sprite.
	this->setSprite(TextureManager::GetTexture(textureIDs.at(type)), false, 8, 12);

	// Set the item type.
	m_type = eITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
	return this->goldValue;
}