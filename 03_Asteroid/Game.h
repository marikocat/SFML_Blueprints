#pragma once
#include <SFML/Graphics.hpp>

#include "World.h"

namespace book
{
	class Game
	{
	public:
		// non copyable class
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game(int x = 800, int y = 600);

		void run(int minimum_frames_per_second = 30);

		void initLevel();
	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();

		void reset();

		sf::RenderWindow m_window;
		World m_world;

		sf::Time m_nextSaucer;
		sf::Text m_txt;
	};
}