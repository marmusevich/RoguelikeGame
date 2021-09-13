#ifndef ITEM_H
#define ITEM_H


#include "core/Object.hpp"
#include "Enums.hpp"


class Item : public Object
{
public:
	/**
	 * Default constructor.
	 */
	Item();

	/**
	 * Draws the item name to screen if it has one. The drawing of the object is done in the parent function which is called.
	 * @param window The render window to draw to.
	 * @param font The font to use when drawing the item name.
	 */
	void draw(sf::RenderWindow& window, float timeDelta);

	/**
	 * Gets the name of the item.
	 * @return The name of the item.
	 */
	std::string getItemName() const;

	/**
	 * Gets the item type.
	 * @return The item type.
	 */
	ITEM getType() const;

protected:
	/**
	 * Sets the item name.
	 * @param name The new item name.
	 */
	void setItemName(std::string name);

public:
	/**
	 * The name of the item.
	 */
	std::string m_name;

	/**
	 * The type of item.
	 */
	ITEM m_type;

	/**
	 * A text object storing the name of the item.
	 */
	sf::Text m_text;

	/**
	 * A font object storing the name of the item.
	 */
	sf::Font m_font;

	/*
	 * The dimensions of the items name in text.
	 */
	sf::Vector2f m_textOffset;
};
#endif