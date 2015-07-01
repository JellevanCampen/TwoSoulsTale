#pragma once
#ifndef ENGINE_WORLD_COLLISIONMANAGER_H
#define ENGINE_WORLD_COLLISIONMANAGER_H

#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "../common/utility/IntervalTypes.hpp" // For representing AABBs
#include "../common/utility/VectorTypes.hpp" // For representing positions

namespace Engine{

	// Typedefs for the available collision shapes
	typedef struct circle
	{ 
		d2 p;
		double r; 
		circle() : p(0.0, 0.0), r(0.0) { }
		circle(d2 p, double r) : p(p), r(r) { }
		circle(double x, double y, double r) : p(x, y), r(r) { }
	};

	typedef struct sphere 
	{ 
		double x, y, z, r; 
		sphere() : x(0.0), y(0.0), z(0.0), r(0.0) { }
		sphere(double x, double y, double z, double r) : x(x), y(y), z(z), r(r) { }
	};

	typedef struct ray2D
	{ 
		d2 p1, p2; 
		ray2D() : p1(0.0, 0.0), p2(0.0, 0.0) { }
		ray2D(d2 p1, d2 p2) : p1(p1), p2(p2) { }
		ray2D(double x1, double y1, double x2, double y2) : p1(x1, y1), p2(x2, y2) { }
		inline ray2D operator- (d2 other) const { return ray2D(p1 - other, p2 - other); }
		inline d2 GetSlope() const { return d2(p2.x() - p1.x(), p2.y() - p1.y()); }
	};

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
		static bool IsIntersecting(const circle& c1, const circle& c2);

		// Calculates the distance between two circles
		static double GetDistance(const circle& c1, const circle& c2);

		// Calculates the penetration of two circles
		static double GetPenetration(const circle& c1, const circle& c2);

		// Tests whether a ray intersects with a circle
		static bool IsIntersecting(const ray2D& r, const circle& c);

		// Finds the points where a ray enters and exits a circle
		static bool IsIntersecting(const ray2D& r, const circle& c, d2& out_Enter, d2& out_Exit);

		// Tests whether a moving circle intersects with another circle [TODO: TEST]
		static bool IsIntersecting(const circle& c1, const circle& c2, const d2& motion_c1);

		// Finds the points where a moving circle enters and exits another circle [TODO: TEST]
		static bool IsIntersecting(const circle& c1, const circle& c2, const d2& motion_c1, d2& out_Enter, d2& out_Exit);

		////////////////////////////////////////////////////////////////
		// 3D intersection testing                                    //
		////////////////////////////////////////////////////////////////

		// Tests whether two spheres intersect
		static bool IsIntersecting(const sphere& s1, const sphere& s2);
		static bool IsIntersecting(const sphere& s1, const sphere& s2, double& out_Distance);

	};
}

#endif