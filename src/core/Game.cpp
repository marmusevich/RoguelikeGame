#include "core/Game.hpp"
#include "core/Input.hpp"
#include "core/Scene.hpp"
#include "utils/MathUtils.hpp"

#include "utils/Util.hpp"

Game::Game(sf::RenderWindow* window, const unsigned int FPS)
	:
m_window(*window),
m_gameState(GAME_STATE::PLAYING),
m_isRunning(true),
m_timestepClock(),
m_curScene(nullptr),
m_isPaused(false)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setMouseCursorVisible(false);
	m_window.setFramerateLimit(FPS);

	RandomSeedByTime();
}

const sf::View& Game::getDefaultView() const
{
	return m_window.getDefaultView();
}

sf::Vector2u Game::getScreenSize() const
{
	return m_window.getSize();
}

sf::Vector2f Game::getScreenCenter() const
{
	return { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f };
}

bool Game::setScene(std::shared_ptr<Scene> scene)
{
	m_curScene = scene;
	bool isOk = m_curScene != nullptr;

	if (isOk)
	{
		isOk = m_curScene->beforeLoad();
		if (isOk)
		{
			isOk = m_curScene->loadResurce();
		}
		m_curScene->afterLoad(isOk);
	}
	if (!isOk)
	{
		m_curScene.reset();
	}

	return isOk;
}

bool Game::isRunning()
{
	return m_isRunning;
}

void Game::pause()
{
	m_isPaused = true;
}

void Game::resume()
{
	m_isPaused = false;
}

bool Game::isPaused() const
{
	return m_isPaused;
}


void Game::run()
{
	resume();

	float currentTime = m_timestepClock.restart().asSeconds();
	float timeDelta = 0.f;

	// Loop until there is a quite message from the window or the user pressed escape.
	while (m_isRunning)
	{
		// Check if the game was closed.
		sf::Event event;
		if (m_window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
			{
				m_isRunning = false;
				m_window.close();
				return;
			}


			if (event.type == sf::Event::LostFocus || event.type == sf::Event::MouseLeft)
			{
				pause();
			}

			if (event.type == sf::Event::GainedFocus || event.type == sf::Event::MouseEntered)
			{
				resume();
			}
		}

		float newTime = m_timestepClock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		
#ifdef DEBUG
{
	float fps = frameTime > 0.0f ? 1 / frameTime : 0.0f;
	m_window.setTitle(ToStringFormated("fps = %.1f", fps));
}
#endif // DEBUG


		if (m_curScene)
		{
			if(!isPaused())
			{
				// update all items in the level.
				m_curScene->update(frameTime);
			}

			// Draw all items in the level.
			m_curScene->draw(m_window, frameTime);
		}

		// Present the back-buffer to the screen.
		m_window.display();
	}

	// Shut the game down.
	m_window.close();
}
