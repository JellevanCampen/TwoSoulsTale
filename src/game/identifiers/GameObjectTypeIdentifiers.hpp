#pragma once
#ifndef GAME_IDENTIFIERS_GAMEOBJECTTYPEIDENTIFIERS_H
#define GAME_IDENTIFIERS_GAMEOBJECTTYPEIDENTIFIERS_H

#include "..\src\engine\world\GameObject.hpp" // For defining GameObjectTypes
#include "..\src\engine\world\WorldManager.hpp" // For retrieving the GameObjectType index offset

namespace ID_TYPE{

	static const Engine::GameObjectType OFFSET = __LINE__;
#define AUTOID_ID_TYPE Engine::OBJ_OFFSET + __LINE__ - (ID_TYPE::OFFSET+2)
	static const Engine::GameObjectType OBJ_TESTOBJECT = Engine::GameObjectType(AUTOID_ID_TYPE);
	static const Engine::GameObjectType OBJ_TESTOBJECT2 = Engine::GameObjectType(AUTOID_ID_TYPE);

}

#endif