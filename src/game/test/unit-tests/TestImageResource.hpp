#pragma once
#ifndef ENGINE_GAME_TESTIMAGERESOURCE_H
#define ENGINE_GAME_TESTIMAGERESOURCE_H

#include "..\..\..\engine\world\GameObject.hpp"

#include "..\..\identifiers\GameObjectTypeIdentifiers.hpp" // For retrieving the ID of this object

#include "..\src\engine\debugging\LoggingManager.hpp" // [DEBUGGING] Logging Manager
#include "..\src\engine\graphics\GraphicsManager.hpp" // [GRAPHICS] Graphics Manager
#include "..\src\engine\input\InputManager.hpp" // [INPUT] Input Manager
#include "..\src\engine\audio\AudioManager.hpp" // [AUDIO] Audio Manager
#include "..\src\engine\world\WorldManager.hpp" // [WORLD] World Manager
#include "..\src\engine\resources\ResourceManager.hpp" // [RESOURCE] Resource Manager
#include "..\src\engine\timing\TimingManager.hpp" // For switching the filter periodically

namespace GameContent{
	class TestImageResource: public Engine::GameObject, public Engine::AlarmListener{

	public:

		// Constructor (given transform)
		TestImageResource(Engine::transform3D transform);

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
		virtual Engine::GameObjectType type() const { return ID_TYPE::OBJ_TESTIMAGERESOURCE; }

		// Switch filters when the filteralarm is triggered
		virtual void ProcessAlarmEvent(Engine::AlarmID alarmID, Engine::Timestamp timestamp);

	private:

		// Spritesheet
		Engine::SpriteSheet m_SpriteSheetGoomba;

		// Index of the filter to apply
		unsigned char m_FilterIndex;

		// Alarm for applying a filter to the image
		Engine::AlarmID m_FilterAlarm;

	};
}

#endif