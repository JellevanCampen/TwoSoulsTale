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

	Engine::GameObjectType type1 = testA->GetType();
	Engine::GameObjectType type2 = testA2->GetType();

	std::vector<Engine::GameObject*> gameObjects;
	Engine::GameObject* gameObject;

test1:
	Engine::WorldManager::GetInstance().RetrieveAllGameObjects(gameObjects, ID_TYPE::OBJ_TESTOBJECT);
	if (gameObjects.size() != 3) { std::cout << "FAILED: RetrieveAllGameObjects" << std::endl; goto test2; }
	if (gameObjects[0]->GetGUID() == 0 && gameObjects[1]->GetGUID() == 1 && gameObjects[2]->GetGUID() == 2)
	{
		std::cout << "PASSED: RetrieveAllGameObjects" << std::endl; goto test2;
	}
	else
	{
		std::cout << "FAILED: RetrieveAllGameObjects" << std::endl; goto test2;
	}

test2:
	Engine::WorldManager::GetInstance().RetrieveGameObject(1, gameObject);
	if (gameObject->GetGUID() == 1) { std::cout << "PASSED: RetrieveGameObject" << std::endl; goto test3; }
	else { std::cout << "FAILED: RetrieveGameObject" << std::endl; goto test3; }

test3:
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveGameObjectsInAABB(Engine::aabb2Df(-0.5f, 1.5f, 0.0f, 2.0f), gameObjects, ID_TYPE::OBJ_TESTOBJECT);
	if (gameObjects.size() != 2) { std::cout << "FAILED: RetrieveGameObjectsInAABB" << std::endl; goto test4; }
	if (gameObjects[0]->GetGUID() == 0 && gameObjects[1]->GetGUID() == 1)
	{
		std::cout << "PASSED: RetrieveGameObjectsInAABB(aabb2D)" << std::endl; goto test4;
	}
	else
	{
		std::cout << "FAILED: RetrieveGameObjectsInAABB(aabb2D)" << std::endl; goto test4;
	}

test4:
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveGameObjectsInAABB(Engine::aabb3Df(-0.5f, 1.5f, 0.0f, 2.0f, 0.0f, 500.0f), gameObjects, ID_TYPE::OBJ_TESTOBJECT);
	if (gameObjects.size() != 1) { std::cout << "FAILED: RetrieveGameObjectsInAABB" << std::endl; goto test5; }
	if (gameObjects[0]->GetGUID() == 1)
	{
		std::cout << "PASSED: RetrieveGameObjectsInAABB(aabb3D)" << std::endl; goto test5;
	}
	else
	{
		std::cout << "FAILED: RetrieveGameObjectsInAABB(aabb3D)" << std::endl; goto test5;
	}

test5:
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveGameObjectsNearPosition(Engine::f3(0.0f, 0.0f, 0.0f), 50.0f, gameObjects, ID_TYPE::OBJ_TESTOBJECT);
	if (gameObjects.size() != 1) { std::cout << "FAILED: RetrieveGameObjectsNearPosition" << std::endl; goto test6; }
	if (gameObjects[0]->GetGUID() == 2)
	{
		std::cout << "PASSED: RetrieveGameObjectsNearPosition" << std::endl; goto test6;
	}
	else
	{
		std::cout << "FAILED: RetrieveGameObjectsNearPosition" << std::endl; goto test6;
	}

test6:
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveKNearestGameObjects(Engine::f3(0.0f, 0.0f, 0.0f), 2, gameObjects, ID_TYPE::OBJ_TESTOBJECT);
	if (gameObjects.size() != 2) { std::cout << "FAILED: RetrieveKNearestGameObjects" << std::endl; goto test7; }
	if (gameObjects[0]->GetGUID() == 2 && gameObjects[1]->GetGUID() == 1)
	{
		std::cout << "PASSED: RetrieveKNearestGameObjects" << std::endl; goto test7;
	}
	else
	{
		std::cout << "FAILED: RetrieveKNearestGameObjects" << std::endl; goto test7;
	}

test7:
	gameObject = NULL;
	Engine::WorldManager::GetInstance().RetrieveNearestGameObject(Engine::f3(0.0f, 1.0f, 100.0f), gameObject, ID_TYPE::OBJ_TESTOBJECT);
	if (gameObject->GetGUID() == 1) { std::cout << "PASSED: RetrieveNearestGameObject" << std::endl; goto test8; }
	else { std::cout << "FAILED: RetrieveNearestGameObject" << std::endl; goto test8; }

	system("pause");

test8:
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveOverlappingAABBGameObjects2D(*testA, gameObjects);
	if (gameObjects.size() != 4) { std::cout << "FAILED: RetrieveOverlappingAABBGameObjects2D" << std::endl; goto test9; }
	if (gameObjects[0]->GetGUID() == 0 && gameObjects[1]->GetGUID() == 3 && gameObjects[2]->GetGUID() == 1 && gameObjects[3]->GetGUID() == 4)
	{
		std::cout << "PASSED: RetrieveOverlappingAABBGameObjects2D" << std::endl; goto test9;
	}
	else
	{
		std::cout << "FAILED: RetrieveOverlappingAABBGameObjects2D" << std::endl; goto test9;
	}

test9:
	gameObjects.clear();
	Engine::WorldManager::GetInstance().RetrieveOverlappingAABBGameObjects3D(*testA, gameObjects);
	if (gameObjects.size() != 2) { std::cout << "FAILED: RetrieveOverlappingAABBGameObjects3D" << std::endl; goto test10; }
	if (gameObjects[0]->GetGUID() == 0 && gameObjects[1]->GetGUID() == 3)
	{
		std::cout << "PASSED: RetrieveOverlappingAABBGameObjects3D" << std::endl; goto test10;
	}
	else
	{
		std::cout << "FAILED: RetrieveOverlappingAABBGameObjects3D" << std::endl; goto test10;
	}

test10:

	game.Start();
	game.Terminate();

	return 0;
}