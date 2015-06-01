#include "InputManager.hpp"

#include "../graphics/GraphicsManager.hpp" // GraphicsManager to get the main window for hooking up input callbacks
#include "../debugging/LoggingManager.hpp" // Logging manager for reporting statuses

#include <algorithm> // For finding listeners in the listener lists

// Initializes the event processing of various input devices
void Engine::InputManager::Initialize()
{
	CheckGamepads();
	HookUpInputCallbacks();
}

// Terminates the event processing of various input devices
void Engine::InputManager::Terminate()
{

}

// Updates the InputManager to retrieve input from active polling-only devices (such as Gamepads)
void Engine::InputManager::Update(const GameTime& gameTime)
{
	LoggingManager& mngrLogging = LoggingManager::GetInstance();

	int axisCount; // Used to store the number of results obtained from querying a gamepad's axis states
	int buttonCount; // Used to store the number of results obtained from querying a gamepad's button states
	
	for (int i = 0; i < m_NumGamepads; i++)
	{
		const float* axes = glfwGetJoystickAxes(i, &axisCount);
		const unsigned char* buttons = glfwGetJoystickButtons(i, &buttonCount);

		axisCount = (axisCount > 16) ? 16 : axisCount;
		for (int j = 0; j < axisCount; j++)
		{
			// Launch an event if the axis has changed
			if (axes[j] != m_GamepadStates[i].axis[j])
			{
				GamepadAxisCallback(i, j, axes[j]);
			}

			// Store the new axis state
			m_GamepadStates[i].axis[j] = axes[j];
		}

		buttonCount = (buttonCount > 16) ? 16 : buttonCount;
		for (int j = 0; j < buttonCount; j++)
		{
			// Launch an event if the axis has changed
			if (buttons[j] != m_GamepadStates[i].button[j])
			{
				GamepadListener::GamepadButtonAction action = GamepadListener::GamepadButtonAction::PRESSED;
				if (buttons[j] == GLFW_RELEASE)
				{
					action = GamepadListener::GamepadButtonAction::RELEASED;
				}

				GamepadButtonCallback(i, j, action);
			}

			// Store the new axis state
			m_GamepadStates[i].button[j] = buttons[j];
		}
	}
}

// Polls all pending input events
void Engine::InputManager::PollInputEvents()
{
	glfwPollEvents();
}

/**************************************************************/
/* Listener registration                                      */
/**************************************************************/

// Keyboard listeners
void Engine::InputManager::RegisterKeyboardKeyListener(KeyboardListener* keyboardListener)
{
	m_KeyboardKeyListeners.push_back(keyboardListener);
}

void Engine::InputManager::DeregisterKeyboardKeyListener(KeyboardListener* keyboardListener)
{
	std::list<KeyboardListener*>::iterator it;
	it = std::find(m_KeyboardKeyListeners.begin(), m_KeyboardKeyListeners.end(), keyboardListener); 
	if (it != m_KeyboardKeyListeners.end())
	{
		m_KeyboardKeyListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a keyboard key listener that could not be found in the listeners list.");
	}
}

void Engine::InputManager::RegisterKeyboardCharacterListener(KeyboardListener* keyboardListener)
{
	m_KeyboardCharacterListeners.push_back(keyboardListener);
}

void Engine::InputManager::DeregisterKeyboardCharacterListener(KeyboardListener* keyboardListener)
{
	std::list<KeyboardListener*>::iterator it;
	it = std::find(m_KeyboardCharacterListeners.begin(), m_KeyboardCharacterListeners.end(), keyboardListener);
	if (it != m_KeyboardCharacterListeners.end())
	{
		m_KeyboardCharacterListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a keyboard character listener that could not be found in the listeners list.");
	}
}

// Mouse listeners
void Engine::InputManager::RegisterMousePositionListener(MouseListener* mouseListener)
{
	m_MousePositionListeners.push_back(mouseListener);
}

void Engine::InputManager::DeregisterMousePositionListener(MouseListener* mouseListener)
{
	std::list<MouseListener*>::iterator it;
	it = std::find(m_MousePositionListeners.begin(), m_MousePositionListeners.end(), mouseListener);
	if (it != m_MousePositionListeners.end())
	{
		m_MousePositionListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a mouse position listener that could not be found in the listeners list.");
	}
}

void Engine::InputManager::RegisterMouseEnterLeaveListener(MouseListener* mouseListener)
{
	m_MouseEnterLeaveListeners.push_back(mouseListener);
}

void Engine::InputManager::DeregisterMouseEnterLeaveListener(MouseListener* mouseListener)
{
	std::list<MouseListener*>::iterator it;
	it = std::find(m_MouseEnterLeaveListeners.begin(), m_MouseEnterLeaveListeners.end(), mouseListener);
	if (it != m_MouseEnterLeaveListeners.end())
	{
		m_MouseEnterLeaveListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a mouse enter/leave listener that could not be found in the listeners list.");
	}
}

void Engine::InputManager::RegisterMouseButtonListener(MouseListener* mouseListener)
{
	m_MouseButtonListeners.push_back(mouseListener);
}

void Engine::InputManager::DeregisterMouseButtonListener(MouseListener* mouseListener)
{
	std::list<MouseListener*>::iterator it;
	it = std::find(m_MouseButtonListeners.begin(), m_MouseButtonListeners.end(), mouseListener);
	if (it != m_MouseButtonListeners.end())
	{
		m_MouseButtonListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a mouse button listener that could not be found in the listeners list.");
	}
}

void Engine::InputManager::RegisterMouseScrollListener(MouseListener* mouseListener)
{
	m_MouseScrollListeners.push_back(mouseListener);
}

void Engine::InputManager::DeregisterMouseScrollListener(MouseListener* mouseListener)
{
	std::list<MouseListener*>::iterator it;
	it = std::find(m_MouseScrollListeners.begin(), m_MouseScrollListeners.end(), mouseListener);
	if (it != m_MouseScrollListeners.end())
	{
		m_MouseScrollListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a mouse scroll listener that could not be found in the listeners list.");
	}
}

// Gamepad listeners
void Engine::InputManager::RegisterGamepadAxisListener(GamepadListener* gamepadListener)
{
	m_GamepadAxisListeners.push_back(gamepadListener);
}

void Engine::InputManager::DeregisterGamepadAxisListener(GamepadListener* gamepadListener)
{
	std::list<GamepadListener*>::iterator it;
	it = std::find(m_GamepadAxisListeners.begin(), m_GamepadAxisListeners.end(), gamepadListener);
	if (it != m_GamepadAxisListeners.end())
	{
		m_GamepadAxisListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a gamepad axis listener that could not be found in the listeners list.");
	}
}

void Engine::InputManager::RegisterGamepadButtonListener(GamepadListener* gamepadListener)
{
	m_GamepadButtonListeners.push_back(gamepadListener);
}

void Engine::InputManager::DeregisterGamepadButtonListener(GamepadListener* gamepadListener)
{
	std::list<GamepadListener*>::iterator it;
	it = std::find(m_GamepadButtonListeners.begin(), m_GamepadButtonListeners.end(), gamepadListener);
	if (it != m_GamepadButtonListeners.end())
	{
		m_GamepadButtonListeners.erase(it);
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "[InputManager] Tried to remove a gamepad button listener that could not be found in the listeners list.");
	}
}

// Checks how many and which gamepads are hooked up
void Engine::InputManager::CheckGamepads()
{
	LoggingManager& mngrLogging = LoggingManager::GetInstance();

	int isPresent;
	int gamepadID = 0;

	do
	{
		isPresent = glfwJoystickPresent(gamepadID);

		if (isPresent)
		{
			// Notify of the detection of the gamepad
			const char* name = glfwGetJoystickName(gamepadID);
			mngrLogging.Log(LoggingManager::LogType::Status, "Detected gamepad [" + std::to_string(gamepadID) + "]: " + std::string(name));

			// Detect the initial state of the gamepad and store it
			GamepadState16x16 gamepadState;

			int axisCount; // Used to store the number of results obtained from querying a gamepad's axis states
			int buttonCount; // Used to store the number of results obtained from querying a gamepad's button states

			const float* axes = glfwGetJoystickAxes(gamepadID, &axisCount);
			const unsigned char* buttons = glfwGetJoystickButtons(gamepadID, &buttonCount);

			if (axisCount > 16)
			{
				mngrLogging.Log(LoggingManager::LogType::Warning, "The detected gamepad has more than 16 axes! Only up to 16 can be stored, meaning some axes will be unresponsive.");
				axisCount = 16;
			}
			for (int i = 0; i < axisCount; i++)
			{
				gamepadState.axis[i] = axes[i];
			}

			if (buttonCount > 16)
			{
				mngrLogging.Log(LoggingManager::LogType::Warning, "The detected gamepad has more than 16 buttons! Only up to 16 can be stored, meaning some buttons will be unresponsive.");
				buttonCount = 16;
			}
			for (int i = 0; i < buttonCount; i++)
			{
				gamepadState.button[i] = buttons[i];
			}

			m_GamepadStates.push_back(gamepadState);
		}

		gamepadID++;

	} while (isPresent);

	m_NumGamepads = gamepadID - 1;
	mngrLogging.Log(LoggingManager::LogType::Status, "Number of gamepads: " + std::to_string(m_NumGamepads));
}

// Hooks up the GLFW input events to their respective callbacks
void Engine::InputManager::HookUpInputCallbacks()
{
	GraphicsManager& mngrGraphics = GraphicsManager::GetInstance();

	glfwSetKeyCallback(mngrGraphics.m_Window, GLFWKeyboardKeyCallback);
	glfwSetCharCallback(mngrGraphics.m_Window, GLFWKeyboardCharacterCallback);
	glfwSetCursorPosCallback(mngrGraphics.m_Window, GLFWMousePositionCallback);
	glfwSetCursorEnterCallback(mngrGraphics.m_Window, GLFWMouseEnterLeaveCallback);
	glfwSetMouseButtonCallback(mngrGraphics.m_Window, GLFWMouseButtonCallback);
	glfwSetScrollCallback(mngrGraphics.m_Window, GLFWMouseScrollCallback);
}

// GLFW keyboard key callback
void Engine::InputManager::GLFWKeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Translate the action
	KeyboardListener::KeyboardKeyAction keyboardKeyAction;

	switch (action)
	{
	case GLFW_PRESS:
		keyboardKeyAction = KeyboardListener::KeyboardKeyAction::PRESSED;
		break;
	case GLFW_RELEASE:
		keyboardKeyAction = KeyboardListener::KeyboardKeyAction::RELEASED;
		break;
	case GLFW_REPEAT:
		keyboardKeyAction = KeyboardListener::KeyboardKeyAction::REPEATED;
		break;
	default:
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "Detected a keyboard key input event with an unknown action.");
		return;
	}

	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (KeyboardListener* listener : mInput.m_KeyboardKeyListeners)
	{
		listener->ProcessKeyboardKeyEvent(key, keyboardKeyAction);
	}
}

// GLFW keyboard character callback
void Engine::InputManager::GLFWKeyboardCharacterCallback(GLFWwindow* window, unsigned int codepoint)
{
	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (KeyboardListener* listener : mInput.m_KeyboardCharacterListeners)
	{
		listener->ProcessKeyboardCharacterEvent(codepoint);
	}
}

// GLFW mouse position callback
void Engine::InputManager::GLFWMousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (MouseListener* listener : mInput.m_MousePositionListeners)
	{
		listener->ProcessMousePositionEvent(xPos, yPos);
	}
}

// GLFW mouse enter leave callback
void Engine::InputManager::GLFWMouseEnterLeaveCallback(GLFWwindow* window, int entered)
{
	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (MouseListener* listener : mInput.m_MouseEnterLeaveListeners)
	{
		listener->ProcessMouseEnterLeaveEvent(entered == GL_TRUE);
	}
}

// GLFW mouse button callback
void Engine::InputManager::GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	// Translate the action
	MouseListener::MouseButtonAction mouseButtonAction;

	switch (action)
	{
	case GLFW_PRESS:
		mouseButtonAction = MouseListener::MouseButtonAction::PRESSED;
		break;
	case GLFW_RELEASE:
		mouseButtonAction = MouseListener::MouseButtonAction::RELEASED;
		break;
	default:
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Warning, "Detected a mouse button input event with an unknown action.");
		return;
	}

	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (MouseListener* listener : mInput.m_MouseButtonListeners)
	{
		listener->ProcessMouseButtonEvent(button, mouseButtonAction);
	}
}

// GLFW mouse scroll callback
void Engine::InputManager::GLFWMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (MouseListener* listener : mInput.m_MouseScrollListeners)
	{
		listener->ProcessMouseScrollEvent(xOffset, yOffset);
	}
}

// Gamepad axis callback (not GLFW-generated)
void Engine::InputManager::GamepadAxisCallback(unsigned char gamepad, int axis, float position)
{
	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (GamepadListener* listener : mInput.m_GamepadAxisListeners)
	{
		listener->ProcessGamepadAxisEvent(gamepad, axis, position);
	}
}

// Gamepad button callback (not GLFW-generated)
void Engine::InputManager::GamepadButtonCallback(unsigned char gamepad, int button, GamepadListener::GamepadButtonAction action)
{
	// Pass the event to all listeners
	InputManager mInput = InputManager::GetInstance();
	for (GamepadListener* listener : mInput.m_GamepadButtonListeners)
	{
		listener->ProcessGamepadButtonEvent(gamepad, button, action);
	}
}