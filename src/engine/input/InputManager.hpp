#pragma once
#ifndef ENGINE_INPUT_INPUTMANAGER_H
#define ENGINE_INPUT_INPUTMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern

namespace Engine{
	class InputManager : public Singleton<InputManager>{

	public:

		// Initializes the event processing of various input devices
		void Initialize();

		// Terminates the event processing of various input devices
		void Terminate();

	private:

	};
}

#endif