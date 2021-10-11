#ifndef SCR_CORE_MANAGER_RESOURCETRAITS_HPP
#define SCR_CORE_MANAGER_RESOURCETRAITS_HPP

#include "core/manager/ResourceType.hpp"

//TODO hide
//for TResourceTraits
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace NResurceManagement
{

//traits enum ResourceType --> sf Resource
template <EResourceType TYPE>
struct TResourceTraits;

template<>
struct TResourceTraits<EResourceType::Texture>
{
	typedef sf::Texture TResource;
};
template<>
struct TResourceTraits<EResourceType::Font>
{
	typedef sf::Font TResource;
};
template<>
struct TResourceTraits<EResourceType::Image>
{
	typedef sf::Image TResource;
};
template<>
struct TResourceTraits<EResourceType::Shader>
{
	typedef sf::Shader TResource;
};
template<>
struct TResourceTraits<EResourceType::Sound>
{
	typedef sf::SoundBuffer TResource;
};

} // namespace NResurceManagement
#endif // RESOURCETRAITS_HPP
