#ifndef SCR_CORE_MANAGER_RESOURCETIPE_HPP
#define SCR_CORE_MANAGER_RESOURCETIPE_HPP

namespace NResurceManagement
{



/**
 * .
 */
enum class EResourceType : unsigned char
{
	Texture, /** sf::Texture */
	Font,    /** sf::Font */
	Image,   /** sf::Image */
	Shader,  /** sf::Shader */
	Sound,   /** sf::SoundBuffer */
	// Music, no need?
};

} // namespace NResurceManagement
#endif // SCR_CORE_MANAGER_RESOURCETIPE_HPP
