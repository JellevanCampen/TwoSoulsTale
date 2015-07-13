#include "TestObject2.hpp"

// Constructor (given transform)
GameContent::TestObject2::TestObject2(Engine::transform3D transform, Engine::aabb3Df aabb)
	: GameObject(transform, aabb)
{
	velocity(Engine::f2(0.1f, -0.2f));
}

// Creates the game object
void GameContent::TestObject2::Create()
{
	m_SpriteSheetGoomba = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("02 - Super Mario Bros/02goomba.png");
}

// Destroys the game object
void GameContent::TestObject2::Destroy()
{
	
}

// Updates the game object
void GameContent::TestObject2::Update(const Engine::GameTime& gameTime)
{
	TestObject2 bla(Engine::transform3D(), Engine::aabb3Df);

	Engine::GameObjectCollection g;
	Engine::WorldManager::GetInstance().RetrieveAll(g);
	Engine::WorldManager::GetInstance().Move2D((*this), Engine::WorldManager::CollisionResponse::STOP, g); 
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::Status, "Velocity: [" + std::to_string(velocity2D().x()) + ", " + std::to_string(velocity2D().y()) + "] ");
}

// Draws the game object
void GameContent::TestObject2::Draw(const Engine::GameTime& gameTime)
{
	Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrameTransformed(m_SpriteSheetGoomba, 0, tf());
	Engine::GraphicsManager::GetInstance().DrawRectangle(aabb2D_world());
}