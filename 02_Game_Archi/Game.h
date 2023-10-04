#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

namespace book
{
	class Game
	{
	public:
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game();

		void run();
		void run_with_fixed_time_steps(int frames_per_second);
		void run_with_variable_time_steps();
		void run_with_minimum_time_steps(int minimum_frames_per_second = 30);
	private:
		void processEvents();
		void update();
		void update(sf::Time deltaTime);
		void render();

		sf::RenderWindow m_window;
		Player m_player;
	};
}