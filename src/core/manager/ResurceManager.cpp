#include "core/manager/ResurceManager.hpp"

namespace NResursesManagement
{
template class TResourceHolder<EResurceType::Texture>;
template class TResourceHolder<EResurceType::Font>;
template class TResourceHolder<EResurceType::Image>;
template class TResourceHolder<EResurceType::Shader>;
template class TResourceHolder<EResurceType::Sound>;

ResurceManager::ResurceManager()
: mTexture(std::make_unique<TResourceHolder<EResurceType::Texture>>())
, mFonts(std::make_unique<TResourceHolder<EResurceType::Font>>())
, mImage(std::make_unique<TResourceHolder<EResurceType::Image>>())
, mShader(std::make_unique<TResourceHolder<EResurceType::Shader>>())
, mSound(std::make_unique<TResourceHolder<EResurceType::Sound>>())
{

}

ResurceManager::~ResurceManager() = default;

} // namespace NResursesManagement
