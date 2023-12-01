#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <SFML-book/client/Client.h>
#include <SFML-book/client/Gui.h>
#include <SFML-book/client/Level.h>

namespace book
{
	class Game
	{
	public:
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game(int X = 1600, int Y = 900);
		~Game();

		bool connect(const sf::IpAddress& ip, unsigned short port, sf::Time timeout = sf::Time::Zero);

		void run(int frame_per_seconds = 60);

	private:
		void processEvents();
		void processNetworkEvents();
		void update(sf::Time deltaTime);
		void render();

		bool _asFocus;
		sf::RenderWindow _window;
		sf::Sprite _cursor;

		Client _client;
		bool _isConnected;

		enum Status
		{
			StatusMainMenu,
			StatusInGame,
			StatusDisconnected
		} _status;

		// Main
		MainMenu _mainMenu;
		// Game
		GameMenu _gameMenu;
		Level* _level;
		Level::FuncType _onPickup;
		int _team;

	};
}