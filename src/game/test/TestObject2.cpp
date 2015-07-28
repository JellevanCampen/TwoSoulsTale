#include "TestObject2.hpp"

#include <sstream> // For printing the FPS onscreen
#include <iomanip> // For specifying precision of floats during string conversions

// Constructor (given transform)
GameContent::TestObject2::TestObject2(Engine::transform3D transform, Engine::aabb3Df aabb)
	: GameObject(transform, aabb)
{
	velocity(Engine::f2(4.0f, -8.0f));
}

// Creates the game object
void GameContent::TestObject2::Create()
{
	m_SpriteSheetGoomba = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("goomba.spritesheet");
	m_Font = Engine::ResourceManager::GetInstance().ReserveBitmapFont("nesfont.bitmapfont");
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
	Engine::WorldManager::GetInstance().RetrieveByType(ID_TYPE::OBJ_TESTOBJECT, g);
	Engine::WorldManager::GetInstance().Move2D((*this), gameTime.GetDeltaTimeSeconds(), Engine::WorldManager::CollisionResponse::STOP, g); 
}

// Draws the game object
void GameContent::TestObject2::Draw(const Engine::GameTime& gameTime)
{
	Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrame(m_SpriteSheetGoomba, 0, tf());
	Engine::GraphicsManager::GetInstance().DrawRectangle(aabb2D_world());

	/*std::string test = "";
	for (int i = 0; i < 10000; i++)
	{
		test += "abcdefgh!?\n";
	}
	Engine::GraphicsManager::GetInstance().DrawText(test, m_Font, Engine::transform2D(Engine::f2(128.0f, 120.0f)));*/
	std::stringstream fps;
	fps << "FPS: " << std::setprecision(4) << Engine::TimingManager::GetInstance().GetFrameRate() << " (" << gameTime.GetFrameCount() << ") " << std::endl;
	Engine::GraphicsManager::GetInstance().DrawText(fps.str(), m_Font, Engine::transform2D(Engine::f2(16.0f, 240.0f - 16.0f)));
}