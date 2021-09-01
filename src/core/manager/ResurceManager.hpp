#ifndef SCR_CORE_MANAGER_RESURCEMANAGER_HPP
#define SCR_CORE_MANAGER_RESURCEMANAGER_HPP

#include "core/manager/ResurceType.hpp"

#include <memory>


namespace NResursesManagement
{

//fwd
template <EResurceType TYPE>
class ResourceHolder;
//class ResourceHolderBase;

/**
 * Pimp idiom for resurses.
 * TODO disable copy and moveá see note by ~ResurceManager()  
 */
class ResurceManager
{
public:
	ResurceManager();

	//std::unique_ptr<ResourceHolderBase> mTexture;
	//std::unique_ptr<ResourceHolderBase> mFonts;
	//std::unique_ptr<ResourceHolderBase> mImage;
	//std::unique_ptr<ResourceHolderBase> mSound;

	
	std::unique_ptr<ResourceHolder<EResurceType::Texture>> mTexture;
	std::unique_ptr<ResourceHolder<EResurceType::Font>> mFonts;
	std::unique_ptr<ResourceHolder<EResurceType::Image>> mImage;
//	std::unique_ptr<ResourceHolder<EResurceType::Shader>> mShader;
	std::unique_ptr<ResourceHolder<EResurceType::Sound>> mSound;

	/**
	 * prevent 'uncomplete type error' in unique_ptr
	 * see:
	 * https://stackoverflow.com/questions/28786387/c-pimpl-idiom-incomplete-type-using-stdunique-ptr
	 * https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
	 */
	~ResurceManager();

};

} // namespace NResursesManagement
#endif // SCR_CORE_MANAGER_RESURCEMANAGER_HPP
