#pragma once
#ifndef ENGINE_WORLD_COLLISIONMANAGER_H
#define ENGINE_WORLD_COLLISIONMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "../common/utility/IntervalTypes.hpp" // For representing AABBs
#include "../common/utility/VectorTypes.hpp" // For representing positions
#include "../common/utility/ShapeTypes.hpp" // For representing collision shapes

namespace Engine{

	class CollisionManager : public Singleton<CollisionManager>
	{

	public:

		// Initializes the collision manager
		void Initialize();

		// Destroys the collision manager
		void Terminate();

		////////////////////////////////////////////////////////////////
		// 2D intersection testing                                    //
		////////////////////////////////////////////////////////////////

		// Tests whether two circles intersect
		static bool IsIntersecting(const circled& c1, const circled& c2);

		// Calculates the distance between two circles
		static double GetDistance(const circled& c1, const circled& c2);

		// Calculates the penetration of two circles
		static double GetPenetration(const circled& c1, const circled& c2);

		// Tests whether a ray intersects with a circle
		static bool IsIntersecting(const ray2Dd& r, const circled& c);

		// Finds the points where a ray enters and exits a circle
		static bool IsIntersecting(const ray2Dd& r, const circled& c, d2& out_Enter, d2& out_Exit);

		// Tests whether a moving circle intersects with another circle [TODO: TEST]
		static bool IsIntersecting(const circled& c1, const circled& c2, const d2& motion_c1);

		// Finds the points where a moving circle enters and exits another circle [TODO: TEST]
		static bool IsIntersecting(const circled& c1, const circled& c2, const d2& motion_c1, d2& out_Enter, d2& out_Exit);

		////////////////////////////////////////////////////////////////
		// 3D intersection testing                                    //
		////////////////////////////////////////////////////////////////

		// TODO

	};
}

#endif