#include "core/Item.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"

#include <sstream>

Item::Item(const Scene& scene)
: tBase(scene)
, m_name("")
, m_textOffset({0.f, 0.f})
{
	m_text.setFont(getResourceManager().get<NResurceManagement::EResourceType::Font>("font"));

	// Setup the text.
	m_text.setCharacterSize(12);
}

// Gets the name of the item.
std::string Item::getItemName() const
{
	return m_name;
}

// Sets the item name.
void Item::setItemName(const std::string name)
{
	// Store new name.
	m_name = name;

	// Set the item name.
	std::ostringstream ss;
	ss << m_name;
	std::string str(ss.str());
	m_text.setString(str);

	// Store the text offset needed when drawing.
	m_textOffset = sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

// Gets the item type.
eITEM Item::getType() const
{
	return m_type;
}

// Draws the item and its name if it has one.
void Item::draw(sf::RenderWindow& window, const float timeDelta)
{
	// Draw the object.
	Object::draw(window, timeDelta);

	// Draw the item name.
	const auto sprPos = getPosition();
	m_text.setPosition(sprPos.x - m_textOffset.x, (sprPos.y - 30.f) - m_textOffset.y);
	window.draw(m_text);
}