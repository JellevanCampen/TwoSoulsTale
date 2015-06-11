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

	GameContent::TestObject* testA(new GameContent::TestObject(Engine::Transform3D(0.0f, 1.0f, 1000.0f)));
	GameContent::TestObject* testB(new GameContent::TestObject(Engine::Transform3D(1.0f, 1.0f, 100.0f)));
	GameContent::TestObject* testC(new GameContent::TestObject(Engine::Transform3D(2.0f, 1.0f, 10.0f)));
	Engine::WorldManager::GetInstance().AddGameObject(testA);
	Engine::WorldManager::GetInstance().AddGameObject(testB);
	Engine::WorldManager::GetInstance().AddGameObject(testC);

	std::vector<Engine::GameObject*> gameObjects;
	Engine::WorldManager::GetInstance().RetrieveAllGameObjects(gameObjects);
	// ^^^^ Expected: <testA(GUID = 0), testB(GUID = 1), testC(GUID = 2)>
	Engine::GameObject* gameObject;
	Engine::WorldManager::GetInstance().RetrieveGameObject(1, gameObject);
	// ^^^^ Expected: <testB(GUID = 1)>
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveGameObjectsInAABB(Engine::aabb2Df(-0.5f, 1.5f, 0.0f, 2.0f), gameObjects);
	// ^^^^ Expected: <testA(GUID = 0), testB(GUID = 1)>
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveGameObjectsInAABB(Engine::aabb3Df(-0.5f, 1.5f, 0.0f, 2.0f, 0.0f, 500.0f), gameObjects);
	// ^^^^ Expected: <testB(GUID = 1)>
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveGameObjectsNearPosition(Engine::f3(0.0f, 0.0f, 0.0f), 50.0f, gameObjects);
	// ^^^^ Expected: <testA(GUID = 0)>
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveKNearestGameObjects(Engine::f3(0.0f, 0.0f, 0.0f), 2, gameObjects);
	// ^^^^ Expected: <testB(GUID = 1), testC(GUID = 2)>
	gameObject = NULL;
	Engine::WorldManager::GetInstance().RetrieveNearestGameObject(Engine::f3(0.0f, 1.0f, 100.0f), gameObject);
	// ^^^^ Expected: <testB(GUID = 1)>

	// TESTING
	Engine::GraphicsManager::GetInstance().SetCameraPosition(Engine::f2(256.0f / 2.0f, 240.0f / 2.0f));
	Engine::GraphicsManager::GetInstance().SetCameraZoom(4.0f);
	Engine::WorldManager::GetInstance().AddGameObject(new GameContent::TestObject(Engine::Transform3D(0.0f, 0.0f, 0.0f)));
	// TESTING

	game.Start();
	game.Terminate();

	return 0;
}