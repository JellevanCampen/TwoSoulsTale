#include "TestObject2.hpp"

// Constructor (given transform)
GameContent::TestObject2::TestObject2(Engine::transform3D transform, Engine::aabb3Df aabb)
	: GameObject(transform, aabb)
{

}

// Creates the game object
void GameContent::TestObject2::Create()
{
	
}

// Destroys the game object
void GameContent::TestObject2::Destroy()
{
	
}

// Updates the game object
void GameContent::TestObject2::Update(const Engine::GameTime& gameTime)
{
	// Engine::WorldManager::Move(*this, Engine::f2(0.1f, -0.2f), Engine::WorldManager::CollisionResponse::IGNORE, )
}

// Draws the game object
void GameContent::TestObject2::Draw(const Engine::GameTime& gameTime)
{
	
}