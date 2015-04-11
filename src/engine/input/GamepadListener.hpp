#pragma once
#ifndef ENGINE_INPUT_GAMEPADLISTENER_H
#define ENGINE_INPUT_GAMEPADLISTENER_H

namespace Engine{

	// Interface for objects that listen to gamepad events
	class GamepadListener{

	public:

		virtual ~GamepadListener() {}
		virtual void ProcessGamepadAxisEvent(int axis, float axisState) = 0;
		virtual void ProcessGamepadButtonEvent(int button, int action) = 0;

	};
}

#endif