#include <SFML-utils/Map.h>

#include <iostream>

#include <SFML-Book/Configuration.h>
#include <SFML-Book/Game.h>

int main(int argc, char* argv[])
{
	book::Configuration::initialize();

	book::Game game(1600, 900);
	game.load("./media/map.json");
	game.run();

	return 0;
}