#include <SFML-book/server/Server.h>

#include <SFML-book/common/Configuration.h>

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
	int port = 5678;

	std::cout << "Usage is : " << argv[0] << " [port]" << std::endl;

	if (argc > 1)
		port = std::atoi(argv[1]);

	std::cout << "Server start on port " << port << std::endl;

	book::Configuration::initialize();

	book::Server server(port);
	server.run();

	return 0;
}