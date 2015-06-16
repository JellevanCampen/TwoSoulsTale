#pragma once
#ifndef ENGINE_GAME_TESTOBJECT2_H
#define ENGINE_GAME_TESTOBJECT2_H

#include "..\..\engine\world\GameObject.hpp"

#include "..\identifiers\GameObjectTypeIdentifiers.hpp" // For retrieving the ID of this object

#include "..\src\engine\debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "..\src\engine\graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager
#include "..\src\engine\input\InputManager.hpp" // [INPUT] Input Manager
#include "..\src\engine\audio\AudioManager.hpp" // [AUDIO] Audio Manager
#include "..\src\engine\world\WorldManager.hpp" // [WORLD] World Manager
#include "..\src\engine\resources\ResourceManager.hpp" // [RESOURCE] Resource Manager

#include "Box2D.h"

namespace GameContent{
	class TestObject2 : public Engine::GameObject{

	public:

		// Constructor (given transform)
		TestObject2(Engine::transform3D transform);

		// Creates the game object
		void Create();

		// Destroys the game object
		void Destroy();

		// Updates the game object
		void Update(const Engine::GameTime& gameTime);

		// Draws the game object
		void Draw(const Engine::GameTime& gameTime);

		////////////////////////////////////////////////////////////////
		// Property setters and getters                               //
		////////////////////////////////////////////////////////////////

		// Gets the type of the game object
		virtual Engine::GameObjectType GetType() const { return ID_TYPE::OBJ_TESTOBJECT2; }

	};
}

#endif