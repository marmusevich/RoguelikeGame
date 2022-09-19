#include "core/mapUtils/CPathfindingBuilder.hpp"

#include "core/mapUtils/private/CPathfinding_refactBook.hpp"
#include "core/mapUtils/private/CPathfinding_fromBook.hpp"

#include <memory>


namespace NMapUtils
{

NMapUtils::IPathfinding* CPathfindingBuilder::makeFromBook(const sf::Vector2u& mapSize, fnTileConvert converter)
{
	//auto ret{ std::make_unique<CPathfinding_fromBook>(mapSize) };
	auto ret = new CPathfinding_fromBook(mapSize);

	ret->mMap.resize(mapSize.x);

	for (uint32_t columnIndex = 0; columnIndex < mapSize.x; ++columnIndex)
	{
		ret->mMap[columnIndex].resize(mapSize.y);

		for (uint32_t rowIndex = 0; rowIndex < mapSize.x; ++rowIndex)
		{
			auto& tile = ret->mMap[columnIndex][rowIndex];
			tile.type = converter(columnIndex, rowIndex);
			tile.columnIndex = columnIndex;
			tile.rowIndex = rowIndex;
		}
	}

	//return ret.release();
	return ret;
}

} // namespace NMapUtils
