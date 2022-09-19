#ifndef SCR_CORE_DRAWABLE_CPATHFINDINGBUILDER_HPP
#define SCR_CORE_DRAWABLE_CPATHFINDINGBUILDER_HPP

#include "core/mapUtils/IPathfinding.hpp"
#include "core/mapUtils/types.hpp"

#include <functional>

namespace NMapUtils
{

	//use lambda to convert tile type from level to pathFindinf type
	//return constitence object with init sizes and set correct tile types in map


struct CPathfindingBuilder
{
	//using fnTileConvert = NMapUtils::eTILE_TYPE(uint32_t columnIndex, uint32_t rowIndex);
	using fnTileConvert = std::function<NMapUtils::eTILE_TYPE(uint32_t columnIndex, uint32_t rowIndex)>;

	//template <typename FN>
	static NMapUtils::IPathfinding* makeFromBook(const sf::Vector2u& mapSize, fnTileConvert converter);
};


} // namespace NMapUtils
#endif // SCR_CORE_DRAWABLE_CPATHFINDINGBUILDER_HPP
