#include <iostream>

#include "engine/Game.hpp" // Include all engine components
#include "engine\world\WorldManager.hpp"
#include "game\test\TestObject.hpp"
#include "engine\common\utility\XMLFileIO.hpp"
#include "engine\common\utility\Transform3D.hpp"

int main(int argc, char* argv[])
{
	Engine::Game game;
	game.Initialize();

	GameContent::TestObject testA;
	GameContent::TestObject testB;
	GameContent::TestObject testC;

	// TESTING
	Engine::GraphicsManager::GetInstance().SetCameraPosition(Engine::f2(256.0f / 2.0f, 240.0f / 2.0f));
	Engine::GraphicsManager::GetInstance().SetCameraZoom(4.0f);
	Engine::WorldManager::GetInstance().AddGameObject(new GameContent::TestObject());
	// TESTING

	game.Start();
	game.Terminate();

	return 0;
}