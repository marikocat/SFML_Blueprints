#include <SFML-book/server/Server.h>

#include <csignal>
#include <iostream>

#include <SFML-book/server/Client.h>
#include <SFML-book/server/Game.h>

#include <SFML-book/common/FuncIds.h>
#include <SFML-book/common/Packet.h>
#include <SFML-book/common/random.h>

namespace book
{
	sig_atomic_t stop = false;

	void signalHandler(int sig)
	{
		std::cout << "Signal receive. Stopping server, please wait." << std::endl;
		stop = true;
	}

	Server::Server(int port) : _port(port), _gameThread(&Server::runGame, this), _listenThread(&Server::listen, this)
	{
		rand_init();
		_currentClient = nullptr;
	}

	Server::~Server()
	{
		_gameMutex.lock();
		for (Game* game : _games)
		{
			game->stop();
			delete game;
		}
		_gameMutex.unlock();

		_clientMutex.lock();
		for (Client* client : _clients)
		{
			client->stop();
			delete client;
		}
		_clientMutex.unlock();

		delete _currentClient;
	}

	void Server::run()
	{
		std::signal(SIGINT, signalHandler);

		_gameThread.launch();
		_listenThread.launch();

		std::cout << "Server is running " << std::endl;

		_gameThread.wait();

		_listenThread.terminate();
	}

	void Server::runGame()
	{
		std::cout << "Start Game service" << std::endl;
		while (!stop)
		{
			sf::Lock guard(_clientMutex);
			// for all clients
			for (auto it = _clients.begin(); it != _clients.end();)
			{
				Client* client = *it;
				packet::NetworkEvent* msg;
				while (client and client->pollEvent(msg))
				{
					std::cout << "Client " << client->id() << " receive data of type : " << msg->type() << std::endl;
					switch (msg->type())
					{
					case FuncIds::IdGetListGame:
					{
						sf::Packet response;
						packet::SetListGame list;
						sf::Lock guard(_gameMutex);
						for (Game* game : _games)
						{
							list.add(game->id(), game->getPlayersCount(), game->getTeamCount());
						}

						response << list;
						client->send(response);
					} break;
					case FuncIds::IdCreateGame:
					{
						sf::Packet response;
						packet::SetListGame list;
						sf::Lock guard(_gameMutex);
						_games.emplace_back(new Game("./media/map.json"));
						for (Game* game : _games)
						{
							list.add(game->id(), game->getPlayersCount(), game->getTeamCount());
						}

						_games.back()->onLogOut = [this](Client* client)
						{
							_clients.emplace_back(client);
						};

						_games.back()->run();

						response << list;
						// send new game to all clients
						for (auto it2 = _clients.begin(); it2 != _clients.end(); ++it2)
							(*it2)->send(response);

					} break;
					case FuncIds::IdJoinGame:
					{
						int gameId = static_cast<packet::JoinGame*>(msg)->gameId();
						sf::Lock guard(_gameMutex);
						for (Game* game : _games)
						{
							if (game->id() == gameId)
							{
								if (game->addClient(client))
								{
									it = _clients.erase(it);
									if (it != _clients.begin())
										--it;
									client = nullptr;
								}
								break;
							}
						}
					} break;
					case FuncIds::IdDisconnected:
					{
						it = _clients.erase(it);
						if (it != _clients.begin())
							--it;
						client = nullptr;
					}
					default: break;
					}
					delete msg;
				}

				if (it != _clients.end())
					++it;
			}
		}
		std::cout << "Stop Game service" << std::endl;
	}

	void Server::listen()
	{
		std::cout << "Start Network service" << std::endl;
		if (_socketListener.listen(_port) != sf::Socket::Done)
		{
			stop = true;
			std::cout << "Error when initializing port " << _port << ". Stopping server" << std::endl;
			return;
		}

		_currentClient = new Client;
		while (!stop)
		{
			std::cout << "Waiting for new connections" << std::endl;
			if (_socketListener.accept(_currentClient->getSockIn()) == sf::Socket::Done)
			{
				std::cout << "New connection received from " << _currentClient->getRemoteAddress() << std::endl;
				if (_currentClient->connect())
				{
					std::cout << "Client accepted" << std::endl;

					sf::Lock guard(_clientMutex);

					_clients.emplace_back(_currentClient);
					_currentClient->run();

					_currentClient = new Client;
				}
				else
				{
					std::cout << "Client rejected" << std::endl;
					_currentClient->disconnect();
				}
			}
		}

		std::cout << "Stop Network service" << std::endl;
	}
}