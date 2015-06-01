#include "TestObject.hpp"

#include "Box2D.h"

// Creates the game object
void GameContent::TestObject::Create()
{
	// Initialize position to the center of the screen
	m_PosX = 128;
	m_PosY = 120;

	m_SpeedX = 0;
	m_SpeedY = 0;

	// Start playing music
	Engine::AudioResource* mscChina = Engine::AudioManager::GetInstance().LoadAudioResource("music/thunderstruck.flac");
	// Engine::AudioManager::GetInstance().Play(mscChina);

	// Register for listening to input
	Engine::InputManager::GetInstance().RegisterKeyboardKeyListener(this);
	Engine::InputManager::GetInstance().RegisterKeyboardCharacterListener(this);
	Engine::InputManager::GetInstance().RegisterMousePositionListener(this);
	Engine::InputManager::GetInstance().RegisterMouseEnterLeaveListener(this);
	Engine::InputManager::GetInstance().RegisterMouseButtonListener(this);
	Engine::InputManager::GetInstance().RegisterMouseScrollListener(this);
	Engine::InputManager::GetInstance().RegisterGamepadAxisListener(this);
	Engine::InputManager::GetInstance().RegisterGamepadButtonListener(this);

	// Reserve a sprite sheet
	m_SpriteSheet = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("02 - Super Mario Bros/9CEvO.png");

	// Generate a physics world
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);
}

// Destroys the game object
void GameContent::TestObject::Destroy()
{
	// Deregister input listening
	Engine::InputManager::GetInstance().DeregisterKeyboardKeyListener(this);
	Engine::InputManager::GetInstance().DeregisterKeyboardCharacterListener(this);
	Engine::InputManager::GetInstance().DeregisterMousePositionListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseEnterLeaveListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseButtonListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseScrollListener(this);
	Engine::InputManager::GetInstance().DeregisterGamepadAxisListener(this);
	Engine::InputManager::GetInstance().DeregisterGamepadButtonListener(this);

	// Free a sprite sheet
	Engine::ResourceManager::GetInstance().FreeSpriteSheet(m_SpriteSheet);
}

// Updates the game object
void GameContent::TestObject::Update(const Engine::GameTime& gameTime)
{
	// Update the position
	m_PosX += m_SpeedX * ((float)gameTime.deltaTimeMicros / 10000.f);
	m_PosY += m_SpeedY * ((float)gameTime.deltaTimeMicros / 10000.f);;

	
	if ((gameTime.frameCount % 500) == 499)
	{
		Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "FPS: " + std::to_string(gameTime.frameCount * 1000000 / (gameTime.totalTimeMicros)));
		// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "FPS: " + std::to_string(1000000.f / gameTime.deltaTimeMicros));
	}
}

// Draws the game object
void GameContent::TestObject::Draw(const Engine::GameTime& gameTime)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Drawing TestObject.");
	Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrame(m_SpriteSheet, 6 + (gameTime.totalTimeMicros / 100000) % 5, m_PosX, m_PosY, 0);
	// Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrameTransformed(m_SpriteSheet, 6 + (gameTime.totalTimeMicros / 100000) % 5, m_PosX, m_PosY, 0, (gameTime.totalTimeMicros / 10000 / 100.0f), 1.0f + 0.2f * sinf(gameTime.totalTimeMicros / 100000 / 25.0f), 1.0f + 0.2f*cosf(gameTime.totalTimeMicros / 100000 / 25.0f));
}

/**************************************************************/
/* Input events                                               */
/**************************************************************/

void GameContent::TestObject::ProcessKeyboardKeyEvent(int key, Engine::KeyboardListener::KeyboardKeyAction action)
{
	if (key == GLFW_KEY_LEFT && action == KeyboardKeyAction::PRESSED) m_SpeedX -= 1;
	if (key == GLFW_KEY_LEFT && action == KeyboardKeyAction::RELEASED) m_SpeedX += 1;

	if (key == GLFW_KEY_RIGHT && action == KeyboardKeyAction::PRESSED) m_SpeedX += 1;
	if (key == GLFW_KEY_RIGHT && action == KeyboardKeyAction::RELEASED) m_SpeedX -= 1;

	if (key == GLFW_KEY_DOWN && action == KeyboardKeyAction::PRESSED) m_SpeedY -= 1;
	if (key == GLFW_KEY_DOWN && action == KeyboardKeyAction::RELEASED) m_SpeedY += 1;

	if (key == GLFW_KEY_UP && action == KeyboardKeyAction::PRESSED) m_SpeedY += 1;
	if (key == GLFW_KEY_UP && action == KeyboardKeyAction::RELEASED) m_SpeedY -= 1;

	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Keyboard key event detected by TestObject.");
}

void GameContent::TestObject::ProcessKeyboardCharacterEvent(unsigned int character)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Keyboard character event detected by TestObject.");
}

void GameContent::TestObject::ProcessMousePositionEvent(double xPos, double yPos)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse position event detected by TestObject.");
}

void GameContent::TestObject::ProcessMouseEnterLeaveEvent(bool entered)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse enter/leave event detected by TestObject.");
}

void GameContent::TestObject::ProcessMouseButtonEvent(int button, MouseButtonAction action)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse button event detected by TestObject.");
}

void GameContent::TestObject::ProcessMouseScrollEvent(int xOffset, int yOffset)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse scroll event detected by TestObject.");
}

void GameContent::TestObject::ProcessGamepadAxisEvent(unsigned char gamepad, int axis, float axisState)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Gamepad axis event detected by TestObject.");
	
	if (fabs(axisState) > 0.2f){
		if (axis == 0)
		{
			m_SpeedX = axisState  * 2.0f;
		}

		if (axis == 1)
		{
			m_SpeedY = -axisState * 2.0f;
		}
	}
	else
	{
		if (axis == 0)
		{
			m_SpeedX = 0.0f;
		}

		if (axis == 1)
		{
			m_SpeedY = 0.0f;
		}
	}
}

void GameContent::TestObject::ProcessGamepadButtonEvent(unsigned char gamepad, int button, GamepadButtonAction action)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Gamepad button event detected by TestObject.");
}