#pragma once
#include <SFML/Graphics.hpp>
#include "ActionTarget.h"
#include "World.h"
#include "Stats.h"

namespace book
{
	class Piece;
	class Game : public ActionTarget<int>
	{
	public:
		//not capyable class
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game(int x, int y, int word_x, int word_y);

		void run(int minimum_frames_per_second = 30, int physics_frames_per_second = 60);

	private:
		void processEvents();
		void update(const sf::Time& deltaTime, const sf::Time& timePerFrame);
		void update_physics(const sf::Time& deltaTime, const sf::Time& timePerFrame);
		void render();

		sf::RenderWindow m_window;

		int m_moveDirection;
		int m_rotateDirection;

		Piece* m_currentPiece;

		World m_world;

		Stats m_stats;

		sf::Time timeSinceLastFall;
	};
}