#include "GameObject.hpp"

// Constructor (default)
Engine::GameObject::GameObject()
	: m_GUID(s_GUIDCounter++) 
{ 
	
}

// Constructor (with transform)
Engine::GameObject::GameObject(transform3D transform)
	: m_GUID(s_GUIDCounter++)
	, m_Transform(transform)
{

}

////////////////////////////////////////////////////////////////
// Property setters and getters                               //
////////////////////////////////////////////////////////////////

// Gets the globally unique ID of the game object
const Engine::GameObjectGUID& Engine::GameObject::GetGUID() const 
{ 
	return m_GUID; 
}

// Incrementing GUID counter
Engine::GameObjectGUID Engine::GameObject::s_GUIDCounter = 0;