#pragma once
#ifndef ENGINE_GAME_TESTOBJECT_H
#define ENGINE_GAME_TESTOBJECT_H

#include "..\..\engine\world\GameObject.hpp"

#include "..\src\engine\debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "..\src\engine\graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager
#include "..\src\engine\input\InputManager.hpp" // [INPUT] Input Manager
#include "..\src\engine\audio\AudioManager.hpp" // [AUDIO] Audio Manager
#include "..\src\engine\world\WorldManager.hpp" // [WORLD] World Manager
#include "..\src\engine\resources\ResourceManager.hpp" // [RESOURCE] Resource Manager

#include "Box2D.h"

namespace GameContent{
	class TestObject : public Engine::GameObject, public Engine::KeyboardListener, public Engine::MouseListener, public Engine::GamepadListener{

	public:

		// Creates the game object
		void Create();

		// Destroys the game object
		void Destroy();

		// Updates the game object
		void Update(const Engine::GameTime& gameTime);

		// Draws the game object
		void Draw(const Engine::GameTime& gameTime);

		/**************************************************************/
		/* Input events                                               */
		/**************************************************************/

		virtual void ProcessKeyboardKeyEvent(int key, KeyboardKeyAction action);
		virtual void ProcessKeyboardCharacterEvent(unsigned int character);

		virtual void ProcessMousePositionEvent(double xPos, double yPos);
		virtual void ProcessMouseEnterLeaveEvent(bool entered);
		virtual void ProcessMouseButtonEvent(int button, MouseButtonAction action);
		virtual void ProcessMouseScrollEvent(int xOffset, int yOffset);

		virtual void ProcessGamepadAxisEvent(unsigned char gamepad, int axis, float axisState);
		virtual void ProcessGamepadButtonEvent(unsigned char gamepad, int button, GamepadButtonAction action);

	private:

		// Position
		double m_PosX;
		double m_PosY;

		double m_SpeedX;
		double m_SpeedY;

		// Sprite sheet
		SpriteSheet m_SpriteSheet;

		// TESTING
		b2World world = b2World(b2Vec2(0.0f, -10.0f));
		b2Body* body;
		b2Body* bodyDistance;
		float32 timestep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		float scale = 32.0f;
		// TESTING

	};
}

#endif