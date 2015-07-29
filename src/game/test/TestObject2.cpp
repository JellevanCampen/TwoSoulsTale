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
	Engine::colorRGBA test(1.0f, 0.5f, 0.0f);
	// Engine::colorRGBA color(0.5f + 0.5f * sinf(gameTime.GetTotalTimeSeconds() * 4.0f), 0.5f + 0.5f * sinf(gameTime.GetTotalTimeSeconds() * 4.0f + (3.1415f * 2.0f / 3.0f) ), 0.5f + 0.5f * sin(gameTime.GetTotalTimeSeconds() * 4.0f + (3.1415f * 4.0f / 3.0f)));
	Engine::colorRGBA color(0.1f);
	Engine::GraphicsManager::GetInstance().DrawText(fps.str(), m_Font, Engine::transform2D(Engine::f2(8.0f, 240.0f - 8.0f), 0.0f, Engine::f2(0.5f)), 0.0f, color);

	std::string textDemo =
		"This is a test for bitmap font rendering. \n"
		"The engine supports ##w(0.5,0.4)wavy animation ##w(0.0,0.0)and ##s(0.1,0.1)shaky animation##s(0.0,0.0). \n"
		"As well as ##c(128,128,255)inline coloring##cd, specified as an ##c(255,0,0)R##c(0,255,0)G##c(0,0,255)B##cd color. \n"
		"Also: ##chc(1.0)hue cycling##chc(0.0), ##cip(0.75)intensity pulsing##cip(0.0) and ##cap(1.0)alpha pulsing##cap(0.0). \n\n"
		"All effects can be combined for: ##w(0.5,0.4)##s(0.1,0.1)##chc(1.0)##cip(0.5)CRAZY SHENANIGANS##r.";
	Engine::GraphicsManager::GetInstance().DrawTextAdvanced(textDemo, m_Font, Engine::transform2D(Engine::f2(8.0f, 240.0f - 8.0f - 8.0f), 0.0f, Engine::f2(0.5f)), 0.0f, color);
}