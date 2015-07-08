#include <iostream>

#include "engine/Game.hpp" // Include all engine components
#include "engine\world\WorldManager.hpp"
#include "game\test\TestObject.hpp"
#include "game\test\TestObject2.hpp"
#include "engine\common\utility\XMLFileIO.hpp"
#include "engine\common\utility\TransformTypes.hpp"

#include <algorithm> // For testing game object retrieval by finding out what elements are in GameObjectCollections

int main(int argc, char* argv[])
{
	Engine::Game game;
	game.Initialize();

	GameContent::TestObject* testA(new GameContent::TestObject(Engine::transform3D(0.0f, 1.0f, 1000.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	GameContent::TestObject* testB(new GameContent::TestObject(Engine::transform3D(1.0f, 1.0f, 100.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	GameContent::TestObject* testC(new GameContent::TestObject(Engine::transform3D(2.0f, 1.0f, 10.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	GameContent::TestObject2* testA2(new GameContent::TestObject2(Engine::transform3D(0.0f, 1.0f, 1000.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	GameContent::TestObject2* testB2(new GameContent::TestObject2(Engine::transform3D(1.0f, 1.0f, 100.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	GameContent::TestObject2* testC2(new GameContent::TestObject2(Engine::transform3D(2.0f, 1.0f, 10.0f), Engine::aabb3Df(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
	Engine::WorldManager::GetInstance().AddGameObject(testA);
	Engine::WorldManager::GetInstance().AddGameObject(testB);
	Engine::WorldManager::GetInstance().AddGameObject(testC);
	Engine::WorldManager::GetInstance().AddGameObject(testA2);
	Engine::WorldManager::GetInstance().AddGameObject(testB2);
	Engine::WorldManager::GetInstance().AddGameObject(testC2);

	Engine::GameObjectCollection gameObjects;

test1:
	Engine::WorldManager::GetInstance().RetrieveAll(gameObjects);
	if (gameObjects.list().size() != 6) { std::cout << "FAILED: RetrieveAlls" << std::endl; goto test2; }
	if (std::find(gameObjects.list().begin(), gameObjects.list().end(), testA) != gameObjects.list().end() 
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testC) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA2) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB2) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testC2) != gameObjects.list().end()
		)
	{
		std::cout << "PASSED: RetrieveAll" << std::endl; goto test2;
	}
	else
	{
		std::cout << "FAILED: RetrieveAll" << std::endl; goto test2;
	}

test2:
	gameObjects.list().clear();
	Engine::WorldManager::GetInstance().RetrieveByGUID(1, gameObjects);
	if (gameObjects.list().size() == 1 
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB) != gameObjects.list().end()
		) { std::cout << "PASSED: RetrieveByGUID" << std::endl; goto test3; }
	else { std::cout << "FAILED: RetrieveByGUID" << std::endl; goto test3; }

test3:
	gameObjects.list().clear();
	Engine::WorldManager::GetInstance().RetrieveByType(ID_TYPE::OBJ_TESTOBJECT, gameObjects);
	if (gameObjects.list().size() == 3
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testC) != gameObjects.list().end()
		) {
		std::cout << "PASSED: RetrieveByType" << std::endl; goto test4;
	}
	else { std::cout << "FAILED: RetrieveByType" << std::endl; goto test4; }

test4:
	gameObjects.list().clear();
	Engine::WorldManager::GetInstance().RetrieveAll(gameObjects);
	gameObjects.FilterByGUID(2);
	if (gameObjects.list().size() == 1
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testC) != gameObjects.list().end()
		) {
		std::cout << "PASSED: FilterByGUID" << std::endl; goto test5;
	}
	else { std::cout << "FAILED: FilterByGUID" << std::endl; goto test5; }

test5:

	gameObjects.list().clear();
	Engine::WorldManager::GetInstance().RetrieveAll(gameObjects);
	gameObjects.FilterByType(ID_TYPE::OBJ_TESTOBJECT2);
	if (gameObjects.list().size() == 3
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA2) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB2) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testC2) != gameObjects.list().end()
		) {
		std::cout << "PASSED: FilterByType" << std::endl; goto test6;
	}
	else { std::cout << "FAILED: FilterByType" << std::endl; goto test6; }

test6:

	gameObjects.list().clear();
	Engine::WorldManager::GetInstance().RetrieveAll(gameObjects);
	gameObjects.FilterByLocation(Engine::interval2Df(-0.5f, 1.5f, 0.0f, 2.0f));
	if (gameObjects.list().size() == 4
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA2) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB2) != gameObjects.list().end()
		) {
		std::cout << "PASSED: FilterByLocation" << std::endl; goto test7;
	}
	else { std::cout << "FAILED: FilterByLocation" << std::endl; goto test7; }

test7:

	gameObjects.list().clear();
	Engine::WorldManager::GetInstance().RetrieveAll(gameObjects);
	gameObjects.FilterByOverlap(testA->aabb2D_world());
	if (gameObjects.list().size() == 4
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testA2) != gameObjects.list().end()
		&& std::find(gameObjects.list().begin(), gameObjects.list().end(), testB2) != gameObjects.list().end()
		) {
		std::cout << "PASSED: FilterByOverlap" << std::endl; goto test8;
	}
	else { std::cout << "FAILED: FilterByOverlap" << std::endl; goto test8; }

test8:

	// TESTING
	game.ToggleBoundingBoxRendering(false);
	Engine::GraphicsManager::GetInstance().SetCameraPosition(Engine::f2(256.0f / 2.0f, 240.0f / 2.0f));
	Engine::GraphicsManager::GetInstance().SetCameraZoom(4.0f);
	Engine::WorldManager::GetInstance().AddGameObject(new GameContent::TestObject(Engine::transform3D(0.0f, 0.0f, 0.0f), Engine::aabb3Df(-12.0f, 12.0f, 0.0f, 24.0f, 0.0f, 0.0f)));
	// TESTING

	game.Start();
	game.Terminate();

	return 0;
}