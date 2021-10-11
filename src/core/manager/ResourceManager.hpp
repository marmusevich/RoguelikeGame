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

	//loadResuse(xml or jml file)

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
