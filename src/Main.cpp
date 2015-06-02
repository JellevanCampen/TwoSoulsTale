#include <iostream>

#include "engine/Game.hpp" // Include all engine components
#include "engine\world\WorldManager.hpp"
#include "game\test\TestObject.hpp"

int main(int argc, char* argv[])
{
	Engine::Game game;
	game.Initialize();

	// TESTING
	Engine::WorldManager::GetInstance().AddGameObject(new GameContent::TestObject());
	// TESTING

	game.Start();
	game.Terminate();

	return 0;
}