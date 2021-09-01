#ifndef SCR_CORE_MANAGER_RESOURCETIPE_HPP
#define SCR_CORE_MANAGER_RESOURCETIPE_HPP

namespace NResursesManagement
{

/**
 * .
 */
using tResurceID = size_t;

/**
 * .
 */
enum class EResurceType : unsigned char
{
	Texture, /** sf::Texture */
	Font,    /** sf::Font */
	Image,   /** sf::Image */
	Shader,  /** sf::Shader */
	Sound,   /** sf::SoundBuffer */
	// Music, no need?
};


//class ResourceHolderBase
//{
//public:
//	virtual tResurceID Load(const std::string& filename) = 0;
//
//};

} // namespace NResursesManagement
#endif // SCR_CORE_MANAGER_RESOURCETIPE_HPP
