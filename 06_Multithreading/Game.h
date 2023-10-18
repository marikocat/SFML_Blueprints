#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "ActionTarget.h"
#include "World.h"
#include "Stats.h"

#include "Gui.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>

namespace book
{
	class Piece;
	class Game : public ActionTarget<int>
	{
	public:
		//not capyable class
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game(int x, int y, int word_x = 10, int word_y = 20);

		void run(int minimum_frames_per_second = 30, int physics_frames_per_second = 60);

	private:
		void processEvents();
		void update(const sf::Time& deltaTime, const sf::Time& timePerFrame);
		void updatePhysics();

		void initGui();
		void initGame();

		void render();

		sf::RenderWindow m_window;

		int m_moveDirection;
		int m_rotateDirection;

		Piece* m_currentPiece;

		World m_world;

		Stats m_stats;

		sf::Time timeSinceLastFall;

		gui::Frame m_mainMenu;
		gui::Frame m_pauseMenu;
		gui::Frame m_configurationMenu;

		enum Status
		{
			StatusMainMenu,
			StatusGame,
			StatusConfiguration,
			StatusPaused,
			StatusExit
		} m_status;

		sfg::SFGUI m_sfgui;
		sfg::Desktop m_sfgDesktop;

		sf::Thread m_physicsThread;
		sf::Mutex m_mutex;
		bool m_isRunning;
		int m_physicsFramesPerSecond;
	};
}