#ifndef SCR_CORE_DRAWABLE_PRIVATE_CSINGLESPRITE_HPP
#define SCR_CORE_DRAWABLE_PRIVATE_CSINGLESPRITE_HPP

#include "core/drawable/iDrawable.hpp"

namespace NDrawable
{

/**
*
*/
class CSingleSprite : public IDrawable
{
public:
	/**
	 * Draws the object to the screen at its current position.
	 * @param target The render target to draw the object to.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void draw(sf::RenderTarget& target, float timeDelta) override;
};

} // namespace NDrawable
#endif // SCR_CORE_DRAWABLE_PRIVATE_CSINGLESPRITE_HPP
