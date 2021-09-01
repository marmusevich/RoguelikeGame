#include "core/manager/ResurceManager.hpp"
#include "core/manager/ResourceHolder.hpp"

#include <memory>

namespace NResursesManagement
{

template class ResourceHolder<EResurceType::Texture>;
template class ResourceHolder<EResurceType::Font>;
template class ResourceHolder<EResurceType::Image>;
//template class ResourceHolder<EResurceType::Shader>;
template class ResourceHolder<EResurceType::Sound>;


ResurceManager::ResurceManager()
: mTexture( std::make_unique<ResourceHolder<EResurceType::Texture>>() )
, mFonts(   std::make_unique<ResourceHolder<EResurceType::Font>>() )
, mImage(   std::make_unique<ResourceHolder<EResurceType::Image>>() )
//, mShader(  std::make_unique<ResourceHolder<EResurceType::Shader>>() )
, mSound(   std::make_unique<ResourceHolder<EResurceType::Sound>>() )
{

}

ResurceManager::~ResurceManager() = default;

} // namespace NResursesManagement
