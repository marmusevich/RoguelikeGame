#ifndef SCR_CORE_MANAGER_RESOURCETRAITS_HPP
#define SCR_CORE_MANAGER_RESOURCETRAITS_HPP

#include "core/manager/ResurceType.hpp"

//TODO hide
//for TResurceTraits
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace NResursesManagement
{

//traits enum ResurceType --> sf resurce
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
	typedef sf::SoundBuffer TResource;
};

} // namespace NResursesManagement
#endif // RESOURCETRAITS_HPP
