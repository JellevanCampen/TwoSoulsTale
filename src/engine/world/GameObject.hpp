#pragma once
#ifndef ENGINE_WORLD_GAMEOBJECT_H
#define ENGINE_WORLD_GAMEOBJECT_H

#include "../common/utility/GameTime.hpp" // For representing timing information on the game loop
#include "../common/utility/TransformTypes.hpp" // For representing the transform of the GameObject
#include "../common/utility/ShapeTypes.hpp" // For representing AABBs

namespace Engine{

	// Typedef for game object globally unique IDs
	typedef unsigned long long GameObjectGUID;

	// Typedef for game object types
	typedef unsigned int GameObjectType;

	class GameObject{

	public:

		// Constructor (default)
		GameObject();

		// Constructor (with transform)
		GameObject(transform3D transform);

		// Constructor (with transform and aabb)
		GameObject(transform3D transform, aabb3Df aabb);

		////////////////////////////////////////////////////////////////
		// Game loop functionality                                    //
		////////////////////////////////////////////////////////////////

		// Creates the game object
		virtual void Create() { };

		// Destroys the game object
		virtual void Destroy() { };

		// Updates the game object
		virtual void Update(const GameTime& gameTime) { };

		// Draws the game object
		virtual void Draw(const GameTime& gameTime) { };

		////////////////////////////////////////////////////////////////
		// Game object properties		                              //
		////////////////////////////////////////////////////////////////

	private:

		// Globally unique ID of the game object
		const GameObjectGUID m_GUID;

		// Incrementing GUID counter
		static GameObjectGUID s_GUIDCounter;

	public:

		// Gets the globally unique ID of the game object
		const GameObjectGUID& guid() const;

		// Gets the type of the game object
		virtual GameObjectType type() const = 0;
		
		////////////////////////////////////////////////////////////////
		// Transform and motion			                              //
		////////////////////////////////////////////////////////////////

	private:

		// Dirty bit for the transform
		bool m_TransformIsDirty = true;

		// 3D Transform of the game object
		transform3D m_Transform;

		// 2D Transform of the game object
		transform2D m_Transform2D;

		// 3D AABB of the game object in local coordinates
		aabb3Df m_AABB;

		// 2D AABB of the game object in local coordinates
		aabb2Df m_AABB2D;

		// 3D AABB of the game object in world coordinates
		aabb3Df m_AABBWorld;

		// 2D AABB of the game object in world coordinates
		aabb2Df m_AABB2DWorld;

		// Calculates the AABB in world coordinates
		void CalculateAABBs();

		// Velocity vector of the game object
		f3 m_Velocity;

	public:

		// 3D transform getters
		inline const transform3D& tf() const { return m_Transform; }
		inline const f3& t() const { return m_Transform.t(); }
		inline const f3& r() const { return m_Transform.r(); }
		inline const f3& s() const { return m_Transform.s(); }
		inline transform3D& tf() { m_TransformIsDirty = true; return m_Transform; }
		inline f3& t() { m_TransformIsDirty = true; return m_Transform.t(); }
		inline f3& r() { m_TransformIsDirty = true; return m_Transform.r(); }
		inline f3& s() { m_TransformIsDirty = true; return m_Transform.s(); }

		// 3D transform setters
		inline void tf(const transform3D& transform) { m_TransformIsDirty = true; m_Transform = transform; }
		inline void t(const f3& t) { m_TransformIsDirty = true; m_Transform.t(t); }
		inline void r(const f3& r) { m_TransformIsDirty = true; m_Transform.r(r); }
		inline void s(const f3& s) { m_TransformIsDirty = true; m_Transform.s(s); }

		// 2D transform getters
		inline const transform2D& tf2D() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_Transform2D; }
		inline const f2& t2D() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_Transform2D.t(); }
		inline const float& r2D() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_Transform2D.r(); }
		inline const f2& s2D() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_Transform2D.s(); }

		// 2D transform setters
		inline void tf(const transform2D& transform) { m_TransformIsDirty = true; m_Transform = transform; }
		inline void t(const f2& t) { m_TransformIsDirty = true; m_Transform.t().x(t.x()); m_Transform.t().y(t.y()); }
		inline void r(const float& r) { m_TransformIsDirty = true; m_Transform.r().x(r); }
		inline void s(const f2& s) { m_TransformIsDirty = true; m_Transform.s().x(s.x()); m_Transform.s().y(s.y()); }

		// 3D AABB getters
		inline const aabb3Df& aabb_local() const { return m_AABB; }
		inline const aabb3Df& aabb_world() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_AABBWorld; }

		// 2D AABB getters
		inline const aabb2Df& aabb2D_local() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_AABB2D; }
		inline const aabb2Df& aabb2D_world() { if (m_TransformIsDirty) { CalculateAABBs(); } return m_AABB2DWorld; }

		// Velocity getters
		inline const f3& velocity() const { return m_Velocity; }
		inline f3& velocity() { return m_Velocity; }
		inline f2 velocity2D() const { return m_Velocity.xy(); }

		// Velocity setters
		inline void velocity(const f3& v) { m_Velocity = v; }
		inline void velocity(const f2& v) { m_Velocity.x(v.x()); m_Velocity.y(v.y()); }
	};
}

#endif