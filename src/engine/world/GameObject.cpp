#include "GameObject.hpp"

// Constructor (with transform and aabb)
Engine::GameObject::GameObject(const transform3D& transform, const aabb3Df& aabb)
	: m_GUID(s_GUIDCounter++)
	, m_Transform(transform)
	, m_AABB(aabb)
{

}

////////////////////////////////////////////////////////////////
// Property setters and getters                               //
////////////////////////////////////////////////////////////////

// Gets the globally unique ID of the game object
const Engine::GameObjectGUID& Engine::GameObject::guid() const 
{ 
	return m_GUID; 
}

// Incrementing GUID counter
Engine::GameObjectGUID Engine::GameObject::s_GUIDCounter = 0;

////////////////////////////////////////////////////////////////
// Transform and motion			                              //
////////////////////////////////////////////////////////////////

// Calculates the AABB in world coordinates
void Engine::GameObject::CalculateAABBs()
{
	m_Transform2D = (transform2D)m_Transform;
	m_AABBWorld = (m_AABB * m_Transform.s()) + m_Transform.t();
	m_AABB2D = (aabb2Df)m_AABB;
	m_AABB2DWorld = (aabb2Df)m_AABBWorld;
	m_TransformIsDirty = false;
}