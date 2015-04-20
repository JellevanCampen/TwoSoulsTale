#pragma once
#ifndef ENGINE_GAME_TESTOBJECT_H
#define ENGINE_GAME_TESTOBJECT_H

#include "..\..\engine\world\GameObject.hpp"

namespace GameContent{
	class TestObject : public Engine::GameObject{

	public:

		// Creates the game object
		void Create();

		// Destroys the game object
		void Destroy();

		// Updates the game object
		void Update();

		// Draws the game object
		void Draw();

	};
}

#endif