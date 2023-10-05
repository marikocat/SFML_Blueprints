#include "Game.h"

#include "Configuration.h"
#include "Random.h"
#include "Meteor.h"
#include "Saucer.h"
#include "Player.h"

namespace book
{
	Game::Game(int x, int y) : 
		m_window(sf::VideoMode(x, y), "03_Asteroid"), m_world(x, y)
	{
		m_txt.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
		m_txt.setCharacterSize(70);
		m_txt.setString("Press any Key to start");

		sf::FloatRect size = m_txt.getGlobalBounds();
		m_txt.setOrigin(size.width / 2, size.height / 2);
		m_txt.setPosition(x / 2, y / 2);
	}

	void Game::run(int minimum_frames_per_second)
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

	void Game::initLevel()
	{
		int nb_meteors;
		switch (Configuration::level)
		{
		case 1: nb_meteors = 4; break;
		case 2: nb_meteors = 5; break;
		case 3: nb_meteors = 7; break;
		case 4: nb_meteors = 9; break;
		default: nb_meteors = 11; break;
		}

		for (int i = 0; i < nb_meteors; ++i)
		{
			Meteor* meteor = new BigMeteor(m_world);
			do
			{
				meteor->setPosition(random(0.f, (float)m_world.getX()), random(0.f, (float)m_world.getY()));
			} while (m_world.isCollide(*meteor));
			m_world.add(meteor);
		}
	}

	void Game::processEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}

			if (Configuration::isGameOver())
			{
				if (event.type == sf::Event::KeyPressed)
					reset();
			}
			else
			{
				if (Configuration::player != nullptr)
					Configuration::player->processEvent(event);
			}
		}

		if (not Configuration::isGameOver() and Configuration::player != nullptr)
			Configuration::player->processEvents();
	}

	void Game::update(sf::Time deltaTime)
	{
		if (not Configuration::isGameOver())
		{
			m_world.update(deltaTime);
			if (Configuration::player == nullptr)
			{
				Configuration::player = new Player(m_world);
				Configuration::player->setPosition(m_world.getX() / 2, m_world.getY() / 2);
				m_world.add(Configuration::player);
			}

			m_nextSaucer -= deltaTime;

			if (m_nextSaucer < sf::Time::Zero)
			{
				Saucer::newSaucer(m_world);
				m_nextSaucer = sf::seconds(random(5.f, 15.f - Configuration::level * 2));
			}

			if (m_world.size() <= 1)
			{
				++Configuration::level;
				initLevel();
			}
		}
	}

	void Game::render()
	{
		m_window.clear();
		
		if (Configuration::isGameOver())
		{
			m_window.draw(m_txt);
		}
		else
		{
			m_window.draw(m_world);

			Configuration::draw(m_window);
		}

		m_window.display();
	}

	void Game::reset()
	{
		m_nextSaucer = sf::seconds(random(3.f, 6.f - Configuration::level * 2));
		m_world.clear();
		Configuration::player = nullptr;
		Configuration::reset();
		initLevel();
	}
}