#ifndef SCR_CORE_DRAWABLE_PRIVATE_CANIMATESPRITE_HPP
#define SCR_CORE_DRAWABLE_PRIVATE_CANIMATESPRITE_HPP

#include "core/drawable/IDrawable.hpp"

namespace NDrawable
{

/**
* animated sprite
*/
class CAnimateSprite : public IDrawable 
{
public:
	/**
	 * Draws the object to the screen at its current position.
	 * @param target The render target to draw the object to.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void draw(sf::RenderTarget& target, float timeDelta) override;

private:

	// in case if derived from sf::Drawable
	/**
	 * Update state
	 */
	// void update(sf::Time dt);

	/**
	 * Draws the object to the screen at its current position.
	 */
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

} // namespace NDrawable
#endif // SCR_CORE_DRAWABLE_PRIVATE_CANIMATESPRITE_HPP
