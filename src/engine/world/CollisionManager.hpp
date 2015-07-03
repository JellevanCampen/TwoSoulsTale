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

		//////////////////////////////////////////////////////// Circles

		// Tests whether two circles intersect
		template<typename valuetype>
		static bool IsIntersecting(const circle<valuetype>& c1, const circle<valuetype>& c2)
		{
			vector2D<valuetype> d(c1.p() - c2.p());
			return (d * d) <= pow(c1.r() + c2.r(), 2);
		}

		// Calculates the distance between two circles
		template<typename valuetype>
		static double GetDistance(const circle<valuetype>& c1, const circle<valuetype>& c2)
		{
			vector2D<valuetype> d(c1.p() - c2.p());
			return fmax(d.Length() - (c1.r() + c2.r()), 0);
		}

		// Calculates the penetration of two circles
		template<typename valuetype>
		static double GetPenetration(const circle<valuetype>& c1, const circle<valuetype>& c2)
		{
			vector2D<valuetype> d(c1.p() - c2.p());
			return fmax((c1.r() + c2.r()) - d.Length(), 0);
		}

		// Tests whether a ray intersects with a circle
		template<typename valuetype>
		static bool IsIntersecting(const ray2D<valuetype>& r, const circle<valuetype>& c)
		{
			// Ray in local coordinates of the circle
			ray2D<valuetype> ray(r - c.p());
			vector2D<valuetype> slope(ray.slope());
			valuetype delta = -(ray.p1() * slope);

			// The start of the ray is the nearest point to the circle
			if (delta <= 0) { vector2D<valuetype> nP = r.p1(); return (nP * nP) <= pow(c.r(), 2); }

			// The end of the ray is the nearest point to the circle
			if (delta >= (slope * slope)) { vector2D<valuetype> nP = r.p2(); return (nP * nP) <= pow(c.r(), 2); }

			// A non-end point of the ray is the nearest point to the circle
			valuetype lambda = delta / (slope * slope);
			vector2D<valuetype> nP = ray.p1() + slope * lambda;
			return (nP * nP) <= pow(c.r(), 2);
		}

		// Finds the points where a ray enters and exits a circle
		template<typename valuetype>
		static bool IsIntersecting(const ray2D<valuetype>& r, const circle<valuetype>& c, vector2D<valuetype>& out_Enter, vector2D<valuetype>& out_Exit)
		{
			// Ray in local coordinates of the circle
			ray2D<valuetype> ray(r - c.p());
			vector2D<valuetype> slope(ray.slope());
			valuetype sigma = pow(ray.p1() * slope, 2) - (slope * slope) * ((ray.p1() * ray.p1()) - pow(c.r(), 2));

			// The infinite extension of the ray intersects the sphere
			if (sigma >= 0)
			{
				valuetype lambda1 = (-(ray.p1() * slope) - sqrt(sigma)) / (slope * slope);
				valuetype lambda2 = (-(ray.p1() * slope) + sqrt(sigma)) / (slope * slope);

				// The ray intersects the sphere
				if (lambda1 <= 1 && lambda2 >= 0)
				{
					out_Enter = r.p1() + (slope * fmax(lambda1, 0));
					out_Exit = r.p1() + (slope * fmin(lambda2, 1));
					return true;
				}
			}

			return false;
		}

		// Tests whether a moving circle intersects with another circle
		template<typename valuetype>
		static bool IsIntersecting(const circle<valuetype>& c1, const circle<valuetype>& c2, const vector2D<valuetype>& motion_c1)
		{
			vector2D<valuetype> start(c1.p());
			vector2D<valuetype> end(c1.p() + motion_c1);
			ray2D<valuetype> r(start, end);
			circle<valuetype> c(c2.p(), c1.r() + c2.r());
			return IsIntersecting(r, c);
		}

		// Finds the points where a moving circle enters and exits another circle
		template<typename valuetype>
		static bool IsIntersecting(const circle<valuetype>& c1, const circle<valuetype>& c2, const vector2D<valuetype>& motion_c1, vector2D<valuetype>& out_Enter, vector2D<valuetype>& out_Exit)
		{
			vector2D<valuetype> start(c1.p());
			vector2D<valuetype> end(c1.p() + motion_c1);
			ray2D<valuetype> r(start, end);
			circle<valuetype> c(c2.p(), c1.r() + c2.r());
			vector2D<valuetype> enter, exit;
			return IsIntersecting(r, c, out_Enter, out_Exit);
		}

		///////////////////////////////////////////////////////// AABBs

		// Tests whether two AABBs intersect
		template<typename valuetype>
		static bool IsIntersecting(const rectangle<valuetype>& r1, const rectangle<valuetype>& r2)
		{
			vector2D<valuetype> d(c1.p() - c2.p());
			return (d * d) <= pow(c1.r() + c2.r(), 2);
		}

		////////////////////////////////////////////////////////////////
		// 3D intersection testing                                    //
		////////////////////////////////////////////////////////////////

		// TODO

	};
}

#endif