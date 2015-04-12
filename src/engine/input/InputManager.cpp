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
			const char* name = glfwGetJoystickName(gamepadID);
			mngrLogging.Log(LoggingManager::LogType::Status, "Detected gamepad [" + std::to_string(gamepadID) + "]: " + std::string(name));
		}

		gamepadID++;
	} while (isPresent);

	mngrLogging.Log(LoggingManager::LogType::Status, "Number of gamepads: " + std::to_string(gamepadID - 1));
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