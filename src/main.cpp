#include "core/Game.hpp"
#include "scenes/GameScene.hpp"

#include <memory>

#include <SFML/Graphics.hpp>

namespace NDefaultParam
{
	const sf::VideoMode mode = sf::VideoMode(1366u, 768u);
	//const sf::VideoMode mode = sf::VideoMode( 1366u, 768u );
	//const sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	//const sf::VideoMode mode = sf::VideoMode(*1024u, 768u);

	constexpr char* title = "Roguelike Template";
	constexpr sf::Uint32 style = sf::Style::Default /*sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize*/;

	constexpr unsigned int FPS = 60;
}


// Entry point of the application.
int main()
{
	/**  todo
	* 1 avoid creation windows directly - push into game, 
	    OR provide read param class and read param from disk
	* 2 get rid sf:: refers - provide adapter
	* 4 base scene or game is resurse managed
	* */


	// Create the main game object.
	sf::RenderWindow window(NDefaultParam::mode, NDefaultParam::title, NDefaultParam::style);
	Game game(&window, NDefaultParam::FPS);

	game.setScene(std::make_shared<GameScene>(game));

	game.run();

	// Exit the application.
	return EXIT_SUCCESS;
}