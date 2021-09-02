#ifndef SCR_CORE_MANAGER_RESOURCETIPE_HPP
#define SCR_CORE_MANAGER_RESOURCETIPE_HPP

namespace NResursesManagement
{



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

} // namespace NResursesManagement
#endif // SCR_CORE_MANAGER_RESOURCETIPE_HPP
