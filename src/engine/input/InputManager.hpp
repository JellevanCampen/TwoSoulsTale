#pragma once
#ifndef ENGINE_INPUT_INPUTMANAGER_H
#define ENGINE_INPUT_INPUTMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "KeyboardListener.hpp" // Interface for keyboard listeners
#include "MouseListener.hpp" // Interface for mouse listeners
#include "GamepadListener.hpp" // Interface for gamepad listeners

#include <vector> // Vector for storing the states of all gamepads
#include <list> // List for storing al listeners to specific input events

struct GLFWwindow;

namespace Engine{
	class InputManager : public Singleton<InputManager>{

		// Struct for storing the state of a gamepad containing at most 16 axes and 16 buttons
		typedef struct GamepadState16x16
		{
			double axis[16];
			unsigned char button[16];
		};

	public:

		// Initializes the event processing of various input devices
		void Initialize();

		// Terminates the event processing of various input devices
		void Terminate();

		// Updates the InputManager to retrieve input from active polling-only devices (such as Gamepads)
		void Update();

		// Polls all pending input events
		void PollInputEvents();

		/**************************************************************/
		/* Listener registration                                      */
		/**************************************************************/

		// Keyboard listeners
		void RegisterKeyboardKeyListener(KeyboardListener* keyboardListener);
		void DeregisterKeyboardKeyListener(KeyboardListener* keyboardListener);
		void RegisterKeyboardCharacterListener(KeyboardListener* keyboardListener);
		void DeregisterKeyboardCharacterListener(KeyboardListener* keyboardListener);

		// Mouse listeners
		void RegisterMousePositionListener(MouseListener* mouseListener);
		void DeregisterMousePositionListener(MouseListener* mouseListener);
		void RegisterMouseEnterLeaveListener(MouseListener* mouseListener);
		void DeregisterMouseEnterLeaveListener(MouseListener* mouseListener);
		void RegisterMouseButtonListener(MouseListener* mouseListener);
		void DeregisterMouseButtonListener(MouseListener* mouseListener);
		void RegisterMouseScrollListener(MouseListener* mouseListener);
		void DeregisterMouseScrollListener(MouseListener* mouseListener);

		// Gamepad listeners
		void RegisterGamepadAxisListener(GamepadListener* gamepadListener);
		void DeregisterGamepadAxisListener(GamepadListener* gamepadListener);
		void RegisterGamepadButtonListener(GamepadListener* gamepadListener);
		void DeregisterGamepadButtonListener(GamepadListener* gamepadListener);

	private:

		// The number of gamepads detected
		unsigned char m_NumGamepads;

		// Holds the state of all gamepads (with up to 16 axes and up to 16 buttons)
		std::vector<GamepadState16x16> m_GamepadStates;

		// Checks how many and which gamepads are hooked up
		void CheckGamepads();

		// Hooks up the GLFW input events to their respective callbacks
		void HookUpInputCallbacks();

		/**************************************************************/
		/* Keyboard callbacks                                         */
		/**************************************************************/

		// GLFW keyboard key callback
		static void GLFWKeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		std::list<KeyboardListener*> m_KeyboardKeyListeners;

		// GLFW keyboard character callback
		static void GLFWKeyboardCharacterCallback(GLFWwindow* window, unsigned int codepoint); 
		std::list<KeyboardListener*> m_KeyboardCharacterListeners;

		/**************************************************************/
		/* Mouse callbacks                                            */
		/**************************************************************/

		// GLFW mouse position callback
		static void GLFWMousePositionCallback(GLFWwindow* window, double xPos, double yPos);
		std::list<MouseListener*> m_MousePositionListeners;

		// GLFW mouse enter leave callback
		static void GLFWMouseEnterLeaveCallback(GLFWwindow* window, int entered);
		std::list<MouseListener*> m_MouseEnterLeaveListeners;

		// GLFW mouse button callback
		static void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		std::list<MouseListener*> m_MouseButtonListeners;

		// GLFW mouse scroll callback
		static void GLFWMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		std::list<MouseListener*> m_MouseScrollListeners;

		/**************************************************************/
		/* Gamepad callbacks                                          */
		/**************************************************************/

		// Gamepad axis callback (not GLFW-generated)
		static void GamepadAxisCallback(unsigned char gamepad, int axis, float position);
		std::list<GamepadListener*> m_GamepadAxisListeners;

		// Gamepad button callback (not GLFW-generated)
		static void GamepadButtonCallback(unsigned char gamepad, int button, GamepadListener::GamepadButtonAction action);
		std::list<GamepadListener*> m_GamepadButtonListeners;

	};
}

#endif