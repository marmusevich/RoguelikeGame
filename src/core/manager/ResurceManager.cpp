#include "core/manager/ResurceManager.hpp"
#include "core/manager/ResourceHolder.hpp"

#include <memory>

namespace NResursesManagement
{

template class ResourceHolder_NumberAutoIncKey<EResurceType::Texture>;
template class ResourceHolder_NumberAutoIncKey<EResurceType::Font>;
template class ResourceHolder_NumberAutoIncKey<EResurceType::Image>;
//template class ResourceHolder_NumberAutoIncKey<EResurceType::Shader>;
template class ResourceHolder_NumberAutoIncKey<EResurceType::Sound>;


ResurceManager::ResurceManager()
: mTexture( std::make_unique<ResourceHolder_NumberAutoIncKey<EResurceType::Texture>>() )
, mFonts(   std::make_unique<ResourceHolder_NumberAutoIncKey<EResurceType::Font>>() )
, mImage(   std::make_unique<ResourceHolder_NumberAutoIncKey<EResurceType::Image>>() )
//, mShader(  std::make_unique<ResourceHolder_NumberAutoIncKey<EResurceType::Shader>>() )
, mSound(   std::make_unique<ResourceHolder_NumberAutoIncKey<EResurceType::Sound>>() )
{

}

ResurceManager::~ResurceManager() = default;

} // namespace NResursesManagement
