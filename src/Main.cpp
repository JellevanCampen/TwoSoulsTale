#include <iostream>

#include "engine/Game.hpp" // Include all engine components

int main(int argc, char* argv[])
{
	Engine::Game game;
	game.Initialize();
	game.Start();
	game.Terminate();

	return 0;
}