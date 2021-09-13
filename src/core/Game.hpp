#ifndef GAME_H
#define GAME_H

#include "Enums.hpp"

#include <memory>

#include <SFML/Graphics.hpp>

class Scene;

class Game
{
public:

	/**
	 * Constructor.
	 * @param window A pointer to the main render window.
	 */
	Game(sf::RenderWindow* window, const unsigned int FPS = 60);

	/**
	 * The main game loop. This loop in turn updates the game, and draws all objects to screen.
	 * It's also responsible for the game logic timing.
	 */
	void run();

	/**
	 * Returns true if the game is currently running.
	 * @return True if the game is running.
	 */
	bool isRunning();

	/**
	 * Set current scene.
	 * 
	 * \param scene
	 * \return true if scene is loaded
	 */
	bool setScene(std::shared_ptr<Scene> scene);

	/**
	 * The default view of the window
	 * TODO: get rid sf types
	 */
	const sf::View& getDefaultView() const;

	/**
	 * The size of the screen and window.
	 */
	sf::Vector2u getScreenSize() const;

	/**
	* The center of the screen.
	*/
	sf::Vector2f getScreenCenter() const;

	void pause();
	void resume();
	bool isPaused() const;


private:

/**
 * The main application window.
 */
 sf::RenderWindow& m_window;

/**
 * The game state.
 */
GAME_STATE m_gameState;

/**
 * A bool that tracks the running state of the game. It's used in the main loop.
 */
bool m_isRunning;

/**
 * Used in the main game time step.
 */
sf::Clock m_timestepClock;

std::shared_ptr<Scene> m_curScene;

mutable bool m_isPaused;

};
#endif