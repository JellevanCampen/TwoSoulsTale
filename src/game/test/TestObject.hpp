#pragma once
#ifndef ENGINE_GAME_TESTOBJECT_H
#define ENGINE_GAME_TESTOBJECT_H

#include "..\..\engine\world\GameObject.hpp"

#include "..\identifiers\GameObjectTypeIdentifiers.hpp" // For retrieving the ID of this object

#include "..\src\engine\debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "..\src\engine\graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager
#include "..\src\engine\input\InputManager.hpp" // [INPUT] Input Manager
#include "..\src\engine\audio\AudioManager.hpp" // [AUDIO] Audio Manager
#include "..\src\engine\world\WorldManager.hpp" // [WORLD] World Manager
#include "..\src\engine\world\CollisionManager.hpp" // [WORLD] Collision Manager
#include "..\src\engine\resources\ResourceManager.hpp" // [RESOURCE] Resource Manager
#include "..\src\engine\timing\TimingManager.hpp" // [TIMING] Timing Manager

#include "Box2D.h"

namespace GameContent{
	class TestObject : public Engine::GameObject, public Engine::KeyboardListener, public Engine::MouseListener, public Engine::GamepadListener, public Engine::AlarmListener{

	public:

		// Constructor (given transform)
		TestObject(Engine::transform3D transform, Engine::aabb3Df aabb);

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
		virtual Engine::GameObjectType type() const { return ID_TYPE::OBJ_TESTOBJECT; }

		////////////////////////////////////////////////////////////////
		// Event processing                                           //
		////////////////////////////////////////////////////////////////

		virtual void ProcessKeyboardKeyEvent(int key, KeyboardKeyAction action);
		virtual void ProcessKeyboardCharacterEvent(unsigned int character);

		virtual void ProcessMousePositionEvent(double xPos, double yPos);
		virtual void ProcessMouseEnterLeaveEvent(bool entered);
		virtual void ProcessMouseButtonEvent(int button, MouseButtonAction action);
		virtual void ProcessMouseScrollEvent(double xOffset, double yOffset);

		virtual void ProcessGamepadAxisEvent(unsigned char gamepad, int axis, float axisState);
		virtual void ProcessGamepadButtonEvent(unsigned char gamepad, int button, GamepadButtonAction action);

		virtual void ProcessAlarmEvent(Engine::AlarmID alarmID, Engine::Timestamp timestamp);

	private:

		// Position
		double m_PosX;
		double m_PosY;

		double m_SpeedX;
		double m_SpeedY;

		// Sprite sheet
		Engine::SpriteSheet m_SpriteSheetSpiny;
		Engine::SpriteSheet m_SpriteSheetGoomba;

		// TESTING
		b2World world = b2World(b2Vec2(0.0f, -10.0f));
		b2Body* body;
		b2Body* bodyDistance;
		float32 timestep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		float scale = 32.0f;

		Engine::AlarmID m_AlarmSlow;
		Engine::AlarmID m_AlarmFast;
		Engine::AlarmID m_AlarmOnce;
		Engine::AlarmID m_AlarmInfinite;

		Engine::circlef m_Circle;
		Engine::ray2Df m_Ray;
		Engine::aabb2Df m_AABBRect;
		// TESTING

	};
}

#endif