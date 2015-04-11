#include "GraphicsManager.hpp"

#include "../debugging/LoggingManager.hpp" // Logging manager for reporting statuses

// Initializes GLFW, GLEW and creates a window for rendering
void Engine::GraphicsManager::Initialize()
{
	// Initialize GLFW (for window creation and event handling) and GLEW (for crossplatform OpenGL compatibility)
	InitializeGLFW();
	InitializeGLEW();

	// Hook up the GLFW error callback function
	glfwSetErrorCallback(GLFWErrorCallback);
}

// Destroys the window for rendering and GLEW and GLFW
void Engine::GraphicsManager::Terminate()
{
	TerminateGLEW();
	TerminateGLFW();
}

// Swaps the buffers of the main window
void Engine::GraphicsManager::SwapWindowBuffers()
{
	glfwSwapBuffers(m_Window);
}

// Initializes GLFW
bool Engine::GraphicsManager::InitializeGLFW()
{
	if (!glfwInit())
	{
		return false;
	}

	// Set the window hints for the creation of the main window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE); // Prevent screen tearing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Programmable pipeline (OpenGL 3.0 and beyond)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Programmable pipeline (OpenGL 3.0 and beyond)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Prevent the use of deprecated OpenGL functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Prevent the use of non-core functionality

	// Create the window (in non-fullscreen mode, with no shared resources)
	m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowTitle.c_str(), NULL, NULL);

	// Use the OpenGL context of the main window for future rendering
	glfwMakeContextCurrent(m_Window);

	return true;
}

// Initializes GLEW
bool Engine::GraphicsManager::InitializeGLEW()
{
	return true;
}

// Terminates GLFW
void Engine::GraphicsManager::TerminateGLFW()
{
	// Destroy the main window
	glfwDestroyWindow(m_Window);

	// Terminate GLFW
	glfwTerminate();
}

// Terminates GLEW
void Engine::GraphicsManager::TerminateGLEW()
{

}

// GLFW error callback
void Engine::GraphicsManager::GLFWErrorCallback(int error, const char* description)
{
	LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "GLFW error " + std::to_string(error) + ": " + std::string(description));
}