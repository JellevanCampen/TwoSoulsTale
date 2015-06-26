#include <iostream>

#include "engine/Game.hpp" // Include all engine components
#include "engine\world\WorldManager.hpp"
#include "game\test\TestObject.hpp"
#include "game\test\TestObject2.hpp"
#include "engine\common\utility\XMLFileIO.hpp"
#include "engine\common\utility\TransformTypes.hpp"

int main(int argc, char* argv[])
{
	Engine::Game game;
	game.Initialize();

	// TESTING
	Engine::GraphicsManager::GetInstance().SetCameraPosition(Engine::f2(256.0f / 2.0f, 240.0f / 2.0f));
	Engine::GraphicsManager::GetInstance().SetCameraZoom(4.0f);
	Engine::WorldManager::GetInstance().AddGameObject(new GameContent::TestObject(Engine::transform3D(0.0f, 0.0f, 0.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	// TESTING

	game.Start();
	game.Terminate();

	return 0;
}