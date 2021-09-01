#ifndef SCR_CORE_MANAGER_RESOURCEHOLDER_HPP
#define SCR_CORE_MANAGER_RESOURCEHOLDER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

#include "core/manager/ResurceType.hpp"
#include "core/manager/ResurceTraits.hpp"

namespace NResursesManagement
{

// TODO how about texture atlass? one texture file many textures present? or it is sprite
//			>> one file = one texture, for manupulate alias of texture in level my.sprites classes, name too

// has problem key value losts after remove op

//make no copy and move

template <EResurceType TYPE>
class ResourceHolder //: public ResourceHolderBase
{
public:
	using tResource = typename TResurceTraits<TYPE>::TResource;
private:
	using tMap = std::unordered_map<tResurceID, std::pair<std::string /*file name*/, std::unique_ptr<tResource> > >;
public:
	ResourceHolder();

	tResurceID Load(const std::string& filename);

	//TODO only sf::Texture has second param
	// specilization for texteure rect
	// or not need, rect in other class will provide, but only one file with texture can loaded ?
	//template <typename Parameter>
	//tResurceID Load(tResurceID id, const std::string& filename, const Parameter& secondParam);

	//tResource& Get(tResurceID id);
	const tResource& Get(tResurceID id) const;

	void Remove(tResurceID id);

	void Clear();

private:
	mutable tMap mResourceMap;
	mutable tResurceID mCurIndex;
};

#include "ResourceHolder.ipp"

} // namespace NResursesManagement
#endif // SCR_CORE_MANAGER_RESOURCEHOLDER_HPP
