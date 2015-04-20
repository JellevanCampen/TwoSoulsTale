#include "TestObject.hpp"

#include <iostream>

// Creates the game object
void GameContent::TestObject::Create()
{
	std::cout << "Test Object Created" << std::endl;
}

// Destroys the game object
void GameContent::TestObject::Destroy()
{
	std::cout << "Test Object Destroyed" << std::endl;
}

// Updates the game object
void GameContent::TestObject::Update()
{
	std::cout << "Test Object Updated" << std::endl;
}

// Draws the game object
void GameContent::TestObject::Draw()
{
	std::cout << "Test Object Drawn" << std::endl;
}