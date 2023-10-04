#include "Game.h"
#include "Configuration.h"

int main(int argc, char* argv[])
{
	book::Configuration::initialize();

	book::Game game;
	game.run_with_minimum_time_steps();

	return 0;
}