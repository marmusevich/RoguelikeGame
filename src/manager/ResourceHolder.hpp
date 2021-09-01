#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>


//TODO hide detals



//TODO hide
//for TResurceTraits
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>







//provide
//namespace ResursesManager

using tResurceID = size_t;

enum class EResurceType : unsigned char
{
	Texture, // sf::Texture
	Font,    // sf::Font
	Image,   // sf::Image
	Shader,  // sf::Shader
	Sound,   // sf::SoundBuffer
	// Music, no need?
};

//TODO hide
//add traits enum ResurceType --> sf resurce
template <EResurceType TYPE>
struct TResurceTraits;

template<>
struct TResurceTraits<EResurceType::Texture>
{
	typedef sf::Texture TResource;
};
template<>
struct TResurceTraits<EResurceType::Font>
{
typedef sf::Font TResource;
};
template<>
struct TResurceTraits<EResurceType::Image>
{
	typedef sf::Image TResource;
};
template<>
struct TResurceTraits<EResurceType::Shader>
{
	typedef sf::Shader TResource;
};
template<>
struct TResurceTraits<EResurceType::Sound>
{
	typedef sf::Sound TResource;
};


/*
usage like
class a
{
ResourceHolder<EResurceType::Texture> mTextures;
ResourceHolder<EResurceType::Sound> mSounds;
}
*/
// TODO how about texture atlass? one texture file many textures present? or it is sprite
//			>> one file = one texture, for manupulate alias of texture in level my.sprites classes, name too

// has problem key value losts after remove op

//make no copy and move

template <EResurceType TYPE>
class ResourceHolder
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

//#include "ResourceHolder.ipp"
//----------------------------------------------------------------------------
// move to ResourceHolder.ipp
// only for edit, code here
//----------------------------------------------------------------------------

template <EResurceType TYPE>
ResourceHolder<TYPE>::ResourceHolder()
	: mResourceMap()
	, mCurIndex(static_cast<tResurceID>(0))
{

}

template <EResurceType TYPE>
tResurceID ResourceHolder<TYPE>::Load(const std::string& filename)
{
	for (auto it = mResourceMap.cbegin(); it != mResourceMap.cend(); ++it)
	{
		if (it->second.first == filename)
		{
			return it->first;
		}
	}

	// At this point the texture doesn't exists, so we'll create and add it.
	std::unique_ptr<tResource> resource = std::make_unique<tResource>();
	if (resource->loadFromFile(filename))
	{
		auto isInserted = mResourceMap.emplace(mCurIndex + 1, std::make_pair(filename, std::move(resource)));
		if (isInserted.second)
		{
			//ok!
			mCurIndex++;
			return mCurIndex;
		}
		else
		{
			//LOG
			throw std::runtime_error("ResourceHolder::Load - Can't add resurse from file " + filename);
		}
	}
	else
	{
		//LOG
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	//error occured, must NOT reach any way
	return -1;
}

template <EResurceType TYPE>
const typename ResourceHolder<TYPE>::tResource& ResourceHolder<TYPE>::Get(tResurceID id) const
{
	auto it = mResourceMap.find(id);

	if (it == mResourceMap.end())
	{
		//LOG
		throw std::runtime_error("ResourceHolder::Get - Can't get with id  " + std::to_string(id));
	}

	return *(it->second.second);
}

template <EResurceType TYPE>
void ResourceHolder<TYPE>::Remove(tResurceID id)
{
	auto it = mResourceMap.find(id);
	if (it != mResourceMap.end())
	{
		mResourceMap.erase(it);
	}
	// LOG or ?
	//throw std::runtime_error("ResourceHolder::Remove - Can't delete with id  " + std::to_string(id));
}

template <EResurceType TYPE>
void ResourceHolder<TYPE>::Clear()
{
	mResourceMap.clear();
	mCurIndex = static_cast<tResurceID>(0);
}

#endif // RESOURCEHOLDER_HPP
