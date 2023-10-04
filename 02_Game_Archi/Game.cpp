#include "Game.h"

namespace book
{
	Game::Game() : m_window(sf::VideoMode(800, 600), "02_Game_Archi")
	{
		m_player.setPosition(400, 200);
	}

	void Game::run()
	{
		while (m_window.isOpen())
		{
			processEvents();
			update();
			render();
		}
	}

	void Game::run_with_fixed_time_steps(int frames_per_second)
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time TimePerFrame = sf::seconds(1.f / frames_per_second);

		while (m_window.isOpen())
		{
			processEvents();

			bool repaint = false;

			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				update(TimePerFrame);
			}

			if (repaint)
				render();
		}
	}

	void Game::run_with_variable_time_steps()
	{
		sf::Clock clock;

		while (m_window.isOpen())
		{
			processEvents();
			update(clock.restart());
			render();
		}
	}

	void Game::run_with_minimum_time_steps(int minimum_frames_per_second)
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate;
		sf::Time TimePerFrame = sf::seconds(1.f / minimum_frames_per_second);

		while (m_window.isOpen())
		{
			processEvents();

			timeSinceLastUpdate = clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				update(TimePerFrame);
			}
			update(timeSinceLastUpdate);
			render();
		}
	}

	void Game::processEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event)) // always define type first
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
		}

		m_player.processEvents();
	}

	void Game::update()
	{

	}

	void Game::update(sf::Time deltaTime)
	{
		m_player.update(deltaTime);
	}

	void Game::render()
	{
		m_window.clear();
		m_window.draw(m_player);
		m_window.display();
	}
}