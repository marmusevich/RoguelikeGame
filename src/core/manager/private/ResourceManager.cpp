#include "core/manager/ResourceManager.hpp"

namespace NResurceManagement
{
template class TResourceHolder<EResourceType::Texture>;
template class TResourceHolder<EResourceType::Font>;
template class TResourceHolder<EResourceType::Image>;
template class TResourceHolder<EResourceType::Shader>;
template class TResourceHolder<EResourceType::Sound>;

ResourceManager::ResourceManager()
: mTexture(std::make_unique<TResourceHolder<EResourceType::Texture>>())
, mFonts(std::make_unique<TResourceHolder<EResourceType::Font>>())
, mImage(std::make_unique<TResourceHolder<EResourceType::Image>>())
, mShader(std::make_unique<TResourceHolder<EResourceType::Shader>>())
, mSound(std::make_unique<TResourceHolder<EResourceType::Sound>>())
{

}

ResourceManager::~ResourceManager() = default;

} // namespace NResurceManagement
