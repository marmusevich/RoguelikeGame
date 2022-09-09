#ifndef SCR_CORE_DRAWABLE_IDRAWABLE_HPP
#define SCR_CORE_DRAWABLE_IDRAWABLE_HPP

#include <SFML/Graphics/RenderTarget.hpp>


#include <memory>

namespace NDrawable
{

/**
* common object that can paint
* interface to
*  - animated sprite
*  - static (single texture) sprite
*  - particle
*/
class IDrawable // public sf::Drawable //, public sf::Transformable - is need ?
{
public:
	/**
	 * Draws the object to the screen at its current position.
	 * @param target The render target to draw the object to.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void draw(sf::RenderTarget& target, float timeDelta) = 0;

	virtual ~IDrawable() = default;

private:

	// in case if derived from sf::Drawable
	/**
	 * Update state
	 */
	 // void update(const sf::Time dt) = 0;

	 /**
	  * Draws the object to the screen at its current position.
	  */
	  //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

/**
* shared_ptr OR unic_ptr ???
*/
using Ptr = std::shared_ptr<IDrawable>;

} // namespace NDrawable
#endif // SCR_CORE_DRAWABLE_IDRAWABLE_HPP
