#pragma once
#ifndef ENGINE_INPUT_KEYBOARDLISTENER_H
#define ENGINE_INPUT_KEYBOARDLISTENER_H

namespace Engine{

	// Interface for objects that listen to keyboard events
	class KeyboardListener{

	public:

		// Describes the action performed for a keyboard key event
		typedef enum KeyboardKeyAction
		{
			PRESSED,
			RELEASED,
			REPEATED
		};

		virtual ~KeyboardListener() {}
		virtual void ProcessKeyboardKeyEvent(int key, KeyboardKeyAction action) = 0;
		virtual void ProcessKeyboardCharacterEvent(unsigned int character) = 0;

	};
}

#endif