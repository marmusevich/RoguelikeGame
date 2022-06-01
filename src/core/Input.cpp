//#include "src\PCH.hpp"
#include "core/Input.hpp"

#include <SFML/Window.hpp>

// Returns true if the given key is pressed.
bool Input::IsKeyPressed(eKEY keycode)
{
	switch (keycode)
	{
	case Input::eKEY::KEY_LEFT:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -40))
		{
			return true;
		}
		break;

	case Input::eKEY::KEY_RIGHT:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 40))
		{
			return true;
		}
		break;

	case Input::eKEY::KEY_UP:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -40))
		{
			return true;
		}
			break;

	case Input::eKEY::KEY_DOWN:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 40))
		{
			return true;
		}
		break;

	case Input::eKEY::KEY_ATTACK:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
		{
			return true;
		}
		break;

	case Input::eKEY::KEY_ESC:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return true;
		}
	}

	return false;
}