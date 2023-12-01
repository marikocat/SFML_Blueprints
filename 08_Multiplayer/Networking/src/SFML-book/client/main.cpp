#include <SFML-book/client/Game.h>

#include <SFML-book/common/Configuration.h>

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
	int port = 5678;
	std::string ip = "127.0.0.1";

	std::cout << "Usage is: " << argv[0] << "[ip] [port]" << std::endl;

	if (argc > 1)
		ip = argv[1];

	if (argc > 2)
		port = std::atoi(argv[2]);

	book::Configuration::initialize();

	std::cout << "Client start on address " << ip << ":" << port << std::endl;

	book::ServerGame game;
	if (not game.connect(sf::IpAddress(ip), port, sf::seconds(5)))
		return 1;

	std::cout << "OK" << std::endl;

	game.run();

	return 0;
}