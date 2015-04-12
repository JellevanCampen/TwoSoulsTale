#pragma once
#ifndef ENGINE_INPUT_INPUTMANAGER_H
#define ENGINE_INPUT_INPUTMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern

struct GLFWwindow;

namespace Engine{
	class InputManager : public Singleton<InputManager>{

	public:

		// Initializes the event processing of various input devices
		void Initialize();

		// Terminates the event processing of various input devices
		void Terminate();

		// Polls all pending input events
		void PollInputEvents();

	private:

		// Checks how many and which gamepads are hooked up
		void CheckGamepads();

		// Hooks up the GLFW input events to their respective callbacks
		void HookUpInputCallbacks();

		// GLFW keyboard key callback
		static void GLFWKeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		// GLFW keyboard character callback
		static void GLFWKeyboardCharacterCallback(GLFWwindow* window, unsigned int codepoint); 

		// GLFW mouse position callback
		static void GLFWMousePositionCallback(GLFWwindow* window, double xPos, double yPos);

		// GLFW mouse enter leave callback
		static void GLFWMouseEnterLeaveCallback(GLFWwindow* window, int entered);

		// GLFW mouse button callback
		static void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		// GLFW mouse scroll callback
		static void GLFWMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);



	};
}

#endif