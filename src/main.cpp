//#include <PCH.hpp>
#include "core/Game.hpp"

#include "scenes/GameScene.hpp"


#include <memory>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Entry point of the application.
int main()
{
	/* todo
	* 1 avoid creation windows directly - push into game
	* 2 get rid sf:: refers - provide adapter
	* 4 base scene or game is resurse managed
	* */




	// Create the main game object.
	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Roguelike Template", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(1366u, 768u/*1024u, 768u*/), "Roguelike Template", sf::Style::Default /*sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize*/);
	Game game(&window);

	game.setScene(std::make_shared<GameScene>(game));

	game.Run();

	// Exit the application.
	return EXIT_SUCCESS;
}