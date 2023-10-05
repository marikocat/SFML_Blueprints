#include "Game.h"
#include "Configuration.h"

int main(int argc, char* argv[])
{
	book::Configuration::initialize();

	book::Game game;
	game.run();

	return 0;
}