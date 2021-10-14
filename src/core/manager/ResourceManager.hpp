#ifndef SCR_CORE_MANAGER_ResourceMANAGER_HPP
#define SCR_CORE_MANAGER_ResourceMANAGER_HPP

#include "core/manager/ResourceType.hpp"
#include "core/manager/private/TResourceHolder.hpp"
#include "utils/NonCopyable.hpp"
#include "utils/NonMoveable.hpp"

#include <memory>

namespace NResurceManagement
{


/*
здесь
- возможно сделать семейство функций типа add*, load*, get*, isPresent* - длф каждого типа ресурса = getFont(...)
		или лучше get<Font>(...) --> нужны трейты
наверное вместо енума тип ресурсов лучше класы теги, не надо будет имя енума указывать (дедукция типов поможет наверное),
  или простой енум использовать(херня)
*/

/**
 * Pimp idiom for resurses.
 *  see note by ~ResourceManager()  
 */
class ResourceManager : NonCopyable, NonMoveable
{
public:
	ResourceManager();

	template <EResourceType TYPE>
	const typename TResourceTraits<TYPE>::TResource& get(const std::string& key, typename TResourceTraits<TYPE>::TResource* = 0) const;

	template <>
	const sf::Texture& get<EResourceType::Texture>(const std::string& key, sf::Texture*) const
	{
		return mTexture->get(key);
	}

	template <>
	const sf::Font& get<EResourceType::Font>(const std::string& key, sf::Font*) const
	{
		return mFonts->get(key);
	}

	template <>
	const sf::Image& get<EResourceType::Image>(const std::string& key, sf::Image*) const
	{
		return mImage->get(key);
	}

	template <>
	const sf::Shader& get<EResourceType::Shader>(const std::string& key, sf::Shader*) const
	{
		return mShader->get(key);
	}

	template <>
	const sf::SoundBuffer& get<EResourceType::Sound>(const std::string& key, sf::SoundBuffer*) const
	{
		return mSound->get(key);
	}


	std::unique_ptr<TResourceHolder<EResourceType::Texture>> mTexture;
	std::unique_ptr<TResourceHolder<EResourceType::Font>> mFonts;
	std::unique_ptr<TResourceHolder<EResourceType::Image>> mImage;
	std::unique_ptr<TResourceHolder<EResourceType::Shader>> mShader;
	std::unique_ptr<TResourceHolder<EResourceType::Sound>> mSound;

	/**
	 * prevent 'uncomplete type error' in unique_ptr
	 * see:
	 * https://stackoverflow.com/questions/28786387/c-pimpl-idiom-incomplete-type-using-stdunique-ptr
	 * https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
	 */
	~ResourceManager();
};

} // namespace NResurceManagement
#endif // SCR_CORE_MANAGER_ResourceMANAGER_HPP
