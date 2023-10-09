#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Stats.h"

#include <memory>

namespace book
{
	class Game
	{
	public:
		//not capyable class
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game();

		void run(int minimum_frames_per_second);

	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();

		void newPiece();

		sf::RenderWindow m_window;
		std::unique_ptr<Piece> m_currentPiece;
		Board m_board;
		Stats m_stats;
		sf::Time m_nextFall;
	};
}