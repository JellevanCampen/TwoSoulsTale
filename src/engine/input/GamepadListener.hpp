#pragma once
#ifndef ENGINE_INPUT_GAMEPADLISTENER_H
#define ENGINE_INPUT_GAMEPADLISTENER_H

namespace Engine{

	// Interface for objects that listen to gamepad events
	class GamepadListener{

	public:

		// Describes the action performed for a gamepad button event
		typedef enum GamepadButtonAction
		{
			PRESSED,
			RELEASED
		};

		virtual ~GamepadListener() { };
		virtual void ProcessGamepadAxisEvent(int axis, float axisState) { };
		virtual void ProcessGamepadButtonEvent(int button, GamepadButtonAction action) { };

	};
}

#endif