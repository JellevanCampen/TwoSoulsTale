#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICSMANAGER_H
#define ENGINE_GRAPHICS_GRAPHICSMANAGER_H

#include "glew\glew.h"
#include "glfw\glfw3.h"
#include <string>

#include "../input/InputManager.hpp" // InputManager to make the callback hookup a friend function
#include "../common/patterns/Singleton.hpp" // Singleton pattern

namespace Engine{
	class GraphicsManager : public Singleton<GraphicsManager>{

	public:

		// Initializes GLEW, GLFW and creates a window for rendering
		void Initialize();

		// Destroys the window for rendering and GLEW and GLFW
		void Terminate();

		// Swaps the buffers of the main window
		void SwapWindowBuffers();

	private:

		// Settings for the window
		int m_WindowWidth = 256 * 4;
		int m_WindowHeight = 240 * 4;
		std::string m_WindowTitle = "Two Souls Tale";

		// The GLFW window object corresponding to the main window
		GLFWwindow* m_Window;

		// Initializes GLFW
		bool InitializeGLFW();

		// Initializes GLEW
		bool InitializeGLEW();

		// Terminates GLFW
		void TerminateGLFW();

		// Terminates GLEW
		void TerminateGLEW();

		// GLFW error callback
		static void GLFWErrorCallback(int error, const char* description);

		friend class InputManager;

	};
}

#endif