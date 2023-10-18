#include "Configuration.h"
#include "Game.h"

#include "Gui.h"

int main(int argc, char* argv[])
{
	book::Configuration::initialize();

	book::Game game(600, 900, 10, 20);
	game.run(30, 60);

	return 0;
}