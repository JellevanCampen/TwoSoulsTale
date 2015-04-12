#include "InputManager.hpp"

#include "../graphics/GraphicsManager.hpp" // GraphicsManager to get the main window for hooking up input callbacks
#include "../debugging/LoggingManager.hpp" // Logging manager for reporting statuses

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
void Engine::InputManager::Update()
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
	if (action == GLFW_PRESS){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Key Pressed");
	}

	if (action == GLFW_RELEASE){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Key Released");
	}

	if (action == GLFW_REPEAT){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Key Repeated");
	}
}

// GLFW keyboard character callback
void Engine::InputManager::GLFWKeyboardCharacterCallback(GLFWwindow* window, unsigned int codepoint)
{
	LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Entered character: " + std::to_string(codepoint));
}

// GLFW mouse position callback
void Engine::InputManager::GLFWMousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Mouse position changed to: <" + std::to_string(xPos) + " , " + std::to_string(yPos) + "> ");
}

// GLFW mouse enter leave callback
void Engine::InputManager::GLFWMouseEnterLeaveCallback(GLFWwindow* window, int entered)
{
	if (entered == GL_TRUE)
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Mouse entered the window");
	}else{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Mouse left the window");
	}	
}

// GLFW mouse button callback
void Engine::InputManager::GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Mouse button pressed: " + std::to_string(button));
	}

	if (action == GLFW_RELEASE){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Mouse button released: " + std::to_string(button));
	}
}

// GLFW mouse scroll callback
void Engine::InputManager::GLFWMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Mouse scrolled with offset: <" + std::to_string(xOffset) + " , " + std::to_string(yOffset) + "> ");
}

// Gamepad axis callback (not GLFW-generated)
void Engine::InputManager::GamepadAxisCallback(unsigned char gamepad, int axis, float position)
{
	LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Gamepad[" + std::to_string(gamepad) + "] axis[" + std::to_string(axis) + "] to: " + std::to_string(position));
}

// Gamepad button callback (not GLFW-generated)
void Engine::InputManager::GamepadButtonCallback(unsigned char gamepad, int button, GamepadListener::GamepadButtonAction action)
{
	if (action == GamepadListener::GamepadButtonAction::PRESSED){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Gamepad[" + std::to_string(gamepad) + "] button pressed: " + std::to_string(button));
	}

	if (action == GamepadListener::GamepadButtonAction::RELEASED){
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Status, "Gamepad[" + std::to_string(gamepad) + "] button released: " + std::to_string(button));
	}
}