#include "TestObject.hpp"

#include <iostream>

// Creates the game object
void GameContent::TestObject::Create()
{
	// Start playing music
	Engine::AudioResource* mscChina = Engine::AudioManager::GetInstance().LoadAudioResource("music/thunderstruck.flac");
	Engine::AudioManager::GetInstance().Play(mscChina);

	// Register for listening to input
	Engine::InputManager::GetInstance().RegisterKeyboardKeyListener(this);
	Engine::InputManager::GetInstance().RegisterKeyboardCharacterListener(this);
	Engine::InputManager::GetInstance().RegisterMousePositionListener(this);
	Engine::InputManager::GetInstance().RegisterMouseEnterLeaveListener(this);
	Engine::InputManager::GetInstance().RegisterMouseButtonListener(this);
	Engine::InputManager::GetInstance().RegisterMouseScrollListener(this);
	Engine::InputManager::GetInstance().RegisterGamepadAxisListener(this);
	Engine::InputManager::GetInstance().RegisterGamepadButtonListener(this);
}

// Destroys the game object
void GameContent::TestObject::Destroy()
{
	Engine::InputManager::GetInstance().DeregisterKeyboardKeyListener(this);
	Engine::InputManager::GetInstance().DeregisterKeyboardCharacterListener(this);
	Engine::InputManager::GetInstance().DeregisterMousePositionListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseEnterLeaveListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseButtonListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseScrollListener(this);
	Engine::InputManager::GetInstance().DeregisterGamepadAxisListener(this);
	Engine::InputManager::GetInstance().DeregisterGamepadButtonListener(this);
}

// Updates the game object
void GameContent::TestObject::Update()
{
	// std::cout << "Test Object Updated" << std::endl;
}

// Draws the game object
void GameContent::TestObject::Draw()
{
	std::cout << "Test Object Drawn" << std::endl;
}

/**************************************************************/
/* Input events                                               */
/**************************************************************/

void GameContent::TestObject::ProcessKeyboardKeyEvent(int key, Engine::KeyboardListener::KeyboardKeyAction action)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Keyboard key event detected by TestObject.");
}

void GameContent::TestObject::ProcessKeyboardCharacterEvent(unsigned int character)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Keyboard character event detected by TestObject.");
}

void GameContent::TestObject::ProcessMousePositionEvent(double xPos, double yPos)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse position event detected by TestObject.");
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
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Gamepad axis event detected by TestObject.");
}

void GameContent::TestObject::ProcessGamepadButtonEvent(unsigned char gamepad, int button, GamepadButtonAction action)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Gamepad button event detected by TestObject.");
}