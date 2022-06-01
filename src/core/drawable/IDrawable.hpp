#ifndef SCR_CORE_DRAWABLE_IDRAWABLE_HPP
#define SCR_CORE_DRAWABLE_IDRAWABLE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

namespace NDrawable
{

/**
*
*/
class IDrawable
{
public:
	/**
	 * Draws the object to the screen at its current position.
	 * @param target The render target to draw the object to.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void draw(sf::RenderTarget& target, float timeDelta) = 0;
	
	virtual ~IDrawable() = default;
};

} // namespace NDrawable
#endif // SCR_CORE_DRAWABLE_IDRAWABLE_HPP
