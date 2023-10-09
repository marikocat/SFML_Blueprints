#include "Game.h"
#include "Piece.h"
#include "random.h"

#include <string>
#include <cmath>

namespace book
{
	Game::Game() : m_window(sf::VideoMode(800, 600), "SFML Tetris"), m_board()
	{
		rand_init();

		m_board.setPosition(10, 10);
		m_stats.setPosition(300, 10);

		newPiece();
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

	void Game::processEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			else if (event.type == sf::Event::KeyPressed) // keyboard input
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					m_board.move(*m_currentPiece, 0, 1);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					m_board.move(*m_currentPiece, 0, -1);
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					m_board.move(*m_currentPiece, -1, 0);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					m_board.move(*m_currentPiece, 1, 0);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					m_board.drop(*m_currentPiece);
					newPiece();
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					m_board.rotateRight(*m_currentPiece);
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					m_board.rotateLeft(*m_currentPiece);
				}
			}
		}
	}

	void Game::update(sf::Time deltaTime)
	{
		if (not m_board.isGameOver())
		{
			m_stats.addLines(m_board.clearLines(*m_currentPiece));
			m_nextFall += deltaTime;
			if ((not m_board.isFallen(*m_currentPiece)) and (m_currentPiece->getTimeSinceLastMove() > sf::seconds(1.f)))
				newPiece();
			sf::Time max_time = sf::seconds(std::max(0.1, 0.6 - 0.005 * m_stats.getLvl()));
			while (m_nextFall > max_time)
			{
				m_nextFall -= max_time;
				m_board.move(*m_currentPiece, 0, 1);
			}
		}
		else
		{
			m_stats.gameOver();
		}
	}

	void Game::render()
	{
		m_window.clear();

		if (not m_board.isGameOver())
			m_window.draw(m_board);
		m_window.draw(m_stats);

		m_window.display();
	}

	void Game::newPiece()
	{
		m_currentPiece.reset(new Piece((Piece::TetriminoTypes)random(0, Piece::TetriminoTypes::SIZE - 1), 0));
		m_board.spawn(*m_currentPiece);
	}
}

// mine