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

		// Tests whether a point overlaps with a circle
		template<typename valuetype>
		static bool IsIntersecting(const vector2D<valuetype>& p, const circle<valuetype>& c)
		{
			valuetype d = p.GetDistanceTo(c.p());
			return (d <= c.r());
		}

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
			// Convert the circle-circle raycast to a ray-circle raycast
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
			// Convert the circle-circle raycast to a ray-circle raycast
			vector2D<valuetype> start(c1.p());
			vector2D<valuetype> end(c1.p() + motion_c1);
			ray2D<valuetype> r(start, end);
			circle<valuetype> c(c2.p(), c1.r() + c2.r());
			return IsIntersecting(r, c, out_Enter, out_Exit);
		}

		///////////////////////////////////////////////////////// AABBs

		// Tests whether a point overlaps with an AABB
		template<typename valuetype>
		static bool IsIntersecting(const vector2D<valuetype>& p, const interval2D<valuetype>& r)
		{
			return (p >= r.p1() && p <= r.p2());
		}

		// Tests whether two AABBs intersect
		template<typename valuetype>
		static bool IsIntersecting(const interval2D<valuetype>& r1, const interval2D<valuetype>& r2)
		{
			return (r1.p1() <= r2.p2() && r2.p1() <= r1.p2());
		}

		// Tests whether a ray intersects with an AABB
		template<typename valuetype>
		static bool IsIntersecting(const ray2D<valuetype>& r, const interval2D<valuetype>& rect)
		{
			// Ray in local coordinates of the circle
			ray2D<valuetype> l_ray(r - rect.center());
			vector2D<valuetype> l_slope(r.slope());
			vector2D<valuetype> l_ext(rect.extent());
			pointOutcode p1_pc = rect.outcode(r.p1());
			pointOutcode p2_pc = rect.outcode(r.p2());

			// Ray lies completely to one side of the rectangle
			pointOutcode test = p1_pc & p2_pc;
			if ((p1_pc & p2_pc) != 0) {
				return false;
			}

			// The ray might intersect the rectangle
			valuetype lambdaEnter = 0;
			valuetype lambdaExit = 1;
			unsigned char bit = 0x01; // Mask for checking individual bits (shifts at the end of each iteration)

			// For all interval boundaries (2 per dimension), check intersection points
			for (int i = 0; i < 2; i++)
			{
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
			}

			// The ray intersects the box 
			if (lambdaEnter <= lambdaExit)
			{
				return true;
			}

			return false;
		}

		// Finds the points where a ray enters and exits an AABB
		template<typename valuetype>
		static bool IsIntersecting(const ray2D<valuetype>& r, const interval2D<valuetype>& rect, vector2D<valuetype>& out_Enter, vector2D<valuetype>& out_Exit)
		{
			// Ray in local coordinates of the rectangle
			ray2D<valuetype> l_ray(r - rect.center());
			vector2D<valuetype> l_slope(r.slope());
			vector2D<valuetype> l_ext(rect.extent());
			pointOutcode p1_pc = rect.outcode(r.p1());
			pointOutcode p2_pc = rect.outcode(r.p2());

			// Ray lies completely to one side of the rectangle
			pointOutcode test = p1_pc & p2_pc;
			if ((p1_pc & p2_pc) != 0) {
				return false; 
			}

			// The ray might intersect the rectangle
			valuetype lambdaEnter = 0;
			valuetype lambdaExit = 1;
			unsigned char bit = 0x01; // Mask for checking individual bits (shifts at the end of each iteration)

			// For all interval boundaries (2 per dimension), check intersection points
			for (int i = 0; i < 2; i++)
			{
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
			}

			// The ray intersects the box 
			if (lambdaEnter <= lambdaExit) 
			{ 
				out_Enter = r.p1() + (l_slope * lambdaEnter);
				out_Exit = r.p1() + (l_slope * lambdaExit);
				return true; 
			}

			return false;
		}

		// Tests whether a moving AABB intersects with another AABB
		template<typename valuetype>
		static bool IsIntersecting(const interval2D<valuetype>& r1, const interval2D<valuetype>& r2, const vector2D<valuetype>& motion_r1)
		{
			// Convert the aabb-aabb raycast to a ray-aabb raycast
			vector2D<valuetype> l_start(r1.center());
			vector2D<valuetype> l_end(l_start + motion_r1);
			ray2D<valuetype> l_ray(l_start, l_end);
			vector2D<valuetype> l_combinedExtent(r1.extent() + r2.extent());
			interval2D<valuetype> l_rect(r2.center() - l_combinedExtent, r2.center() + l_combinedExtent);
			return IsIntersecting(l_ray, l_rect);
		}

		// Finds the points where a moving AABB enters and exits another AABB
		template<typename valuetype>
		static bool IsIntersecting(const interval2D<valuetype>& r1, const interval2D<valuetype>& r2, const vector2D<valuetype>& motion_r1, vector2D<valuetype>& out_Enter, vector2D<valuetype>& out_Exit)
		{
			// Convert the aabb-aabb raycast to a ray-aabb raycast
			vector2D<valuetype> l_start(r1.center());
			vector2D<valuetype> l_end(l_start + motion_r1);
			ray2D<valuetype> l_ray(l_start, l_end);
			vector2D<valuetype> l_combinedExtent(r1.extent() + r2.extent());
			interval2D<valuetype> l_rect(r2.center() - l_combinedExtent, r2.center() + l_combinedExtent);
			return IsIntersecting(l_ray, l_rect, out_Enter, out_Exit);
		}

		////////////////////////////////////////////////// Circle - AABB

		// Tests whether a circle intersects an AABB
		template<typename valuetype>
		static bool IsIntersecting(const circle<valuetype>& c, const interval2D<valuetype>& r)
		{
			// Express the problem in local coordinates to r
			vector2D<valuetype> l_ext(r.extent());
			circle<valuetype> l_c(c - r.center());

			// Calculate the point on the aabb, closest to the circle
			vector2D<valuetype> l_closestPoint(
				fmin(fmax(l_c.x(), -l_ext.x()), l_ext.x()), 
				fmin(fmax(l_c.y(), -l_ext.y()), l_ext.y())
				);

			// Check whether this point lies within the circle
			vector2D<valuetype> d(l_c.p() - l_closestPoint);
			return ((d * d) <= pow(c.r(), 2));
		}

		// Tests whether a circle intersects an AABB
		template<typename valuetype>
		inline static bool IsIntersecting(const interval2D<valuetype>& r, const circle<valuetype>& c)
		{
			return IsIntersecting<valuetype>(c, r);
		}

		////////////////////////////////////////////////////////////////
		// 3D intersection testing                                    //
		////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////// Spheres

		// Tests whether a point overlaps with a sphere
		template<typename valuetype>
		static bool IsIntersecting(const vector3D<valuetype>& p, const sphere<valuetype>& s)
		{
			valuetype d = p.GetDistanceTo(c.p());
			return (d <= s.r());
		}

		// Tests whether two spheres intersect
		template<typename valuetype>
		static bool IsIntersecting(const sphere<valuetype>& s1, const sphere<valuetype>& s2)
		{
			vector2D<valuetype> d(s.p() - s.p());
			return (d * d) <= pow(s.r() + s.r(), 2);
		}

		// Calculates the distance between two spheres
		template<typename valuetype>
		static double GetDistance(const sphere<valuetype>& s1, const sphere<valuetype>& s2)
		{
			vector3D<valuetype> d(s1.p() - s2.p());
			return fmax(d.Length() - (s1.r() + s2.r()), 0);
		}

		// Calculates the penetration of two spheres
		template<typename valuetype>
		static double GetPenetration(const sphere<valuetype>& s1, const sphere<valuetype>& s2)
		{
			vector3D<valuetype> d(s1.p() - s2.p());
			return fmax((s1.r() + s2.r()) - d.Length(), 0);
		}

		// Tests whether a ray intersects with a sphere
		template<typename valuetype>
		static bool IsIntersecting(const ray3D<valuetype>& r, const sphere<valuetype>& s)
		{
			// Ray in local coordinates of the sphere
			ray3D<valuetype> ray(r - s.p());
			vector3D<valuetype> slope(ray.slope());
			valuetype delta = -(ray.p1() * slope);

			// The start of the ray is the nearest point to the sphere
			if (delta <= 0) { vector3D<valuetype> nP = r.p1(); return (nP * nP) <= pow(s.r(), 2); }

			// The end of the ray is the nearest point to the sphere
			if (delta >= (slope * slope)) { vector3D<valuetype> nP = r.p2(); return (nP * nP) <= pow(s.r(), 2); }

			// A non-end point of the ray is the nearest point to the sphere
			valuetype lambda = delta / (slope * slope);
			vector2D<valuetype> nP = ray.p1() + slope * lambda;
			return (nP * nP) <= pow(s.r(), 2);
		}

		// Finds the points where a ray enters and exits a sphere
		template<typename valuetype>
		static bool IsIntersecting(const ray3D<valuetype>& r, const sphere<valuetype>& s, vector3D<valuetype>& out_Enter, vector3D<valuetype>& out_Exit)
		{
			// Ray in local coordinates of the sphere
			ray3D<valuetype> ray(r - s.p());
			vector3D<valuetype> slope(ray.slope());
			valuetype sigma = pow(ray.p1() * slope, 2) - (slope * slope) * ((ray.p1() * ray.p1()) - pow(s.r(), 2));

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

		// Tests whether a moving sphere intersects with another sphere
		template<typename valuetype>
		static bool IsIntersecting(const sphere<valuetype>& s1, const sphere<valuetype>& s2, const vector3D<valuetype>& motion_s1)
		{
			// Convert the sphere-sphere raycast to a ray-sphere raycast
			vector3D<valuetype> start(s1.p());
			vector3D<valuetype> end(s1.p() + motion_s1);
			ray3D<valuetype> r(start, end);
			sphere<valuetype> s(s2.p(), s1.r() + s2.r());
			return IsIntersecting(r, s);
		}

		// Finds the points where a moving sphere enters and exits another sphere
		template<typename valuetype>
		static bool IsIntersecting(const sphere<valuetype>& s1, const sphere<valuetype>& s2, const vector3D<valuetype>& motion_s1, vector3D<valuetype>& out_Enter, vector3D<valuetype>& out_Exit)
		{
			// Convert the sphere-sphere raycast to a ray-sphere raycast
			vector3D<valuetype> start(s1.p());
			vector3D<valuetype> end(s1.p() + motion_s1);
			ray3D<valuetype> r(start, end);
			sphere<valuetype> s(s2.p(), s1.r() + s2.r());
			return IsIntersecting(r, s, out_Enter, out_Exit);
		}

		///////////////////////////////////////////////////////// AABBs

		// Tests whether a point overlaps with an AABB
		template<typename valuetype>
		static bool IsIntersecting(const vector3D<valuetype>& p, const aabb3D<valuetype>& aabb)
		{
			return (p >= aabb.p1() && p <= aabb.p2());
		}

		// Tests whether two AABBs intersect
		template<typename valuetype>
		static bool IsIntersecting(const aabb3D<valuetype>& aabb1, const aabb3D<valuetype>& aabb2)
		{
			return (aabb1.p1() <= aabb2.p2() && aabb2.p1() <= aabb1.p2());
		}

		// Tests whether a ray intersects with an AABB
		template<typename valuetype>
		static bool IsIntersecting(const ray3D<valuetype>& r, const aabb3D<valuetype>& aabb)
		{
			// Ray in local coordinates of the aabb
			ray3D<valuetype> l_ray(r - aabb.center());
			vector3D<valuetype> l_slope(r.slope());
			vector3D<valuetype> l_ext(aabb.extent());
			pointOutcode p1_pc = aabb.outcode(r.p1());
			pointOutcode p2_pc = aabb.outcode(r.p2());

			// Ray lies completely to one side of the AABB
			pointOutcode test = p1_pc & p2_pc;
			if ((p1_pc & p2_pc) != 0) {
				return false;
			}

			// The ray might intersect the AABB
			valuetype lambdaEnter = 0;
			valuetype lambdaExit = 1;
			unsigned char bit = 0x01; // Mask for checking individual bits (shifts at the end of each iteration)

			// For all AABB boundaries (2 per dimension), check intersection points
			for (int i = 0; i < 3; i++)
			{
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
			}

			// The ray intersects the box 
			if (lambdaEnter <= lambdaExit)
			{
				return true;
			}

			return false;
		}

		// Finds the points where a ray enters and exits an AABB
		template<typename valuetype>
		static bool IsIntersecting(const ray3D<valuetype>& r, const aabb3D<valuetype>& aabb, vector3D<valuetype>& out_Enter, vector3D<valuetype>& out_Exit)
		{
			// Ray in local coordinates of the AABB
			ray3D<valuetype> l_ray(r - aabb.center());
			vector3D<valuetype> l_slope(r.slope());
			vector3D<valuetype> l_ext(aabb.extent());
			pointOutcode p1_pc = aabb.outcode(r.p1());
			pointOutcode p2_pc = aabb.outcode(r.p2());

			// Ray lies completely to one side of the AABB
			pointOutcode test = p1_pc & p2_pc;
			if ((p1_pc & p2_pc) != 0) {
				return false;
			}

			// The ray might intersect the AABB
			valuetype lambdaEnter = 0;
			valuetype lambdaExit = 1;
			unsigned char bit = 0x01; // Mask for checking individual bits (shifts at the end of each iteration)

			// For all AABB boundaries (2 per dimension), check intersection points
			for (int i = 0; i < 3; i++)
			{
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] - l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
				if ((p1_pc & bit) != 0) { lambdaEnter = fmax(lambdaEnter, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				else if ((p2_pc & bit) != 0) { lambdaExit = fmin(lambdaExit, (-l_ray.p1()[i] + l_ext[i]) / (l_ray.p2()[i] - l_ray.p1()[i])); }
				bit <<= 1;
			}

			// The ray intersects the AABB 
			if (lambdaEnter <= lambdaExit)
			{
				out_Enter = r.p1() + (l_slope * lambdaEnter);
				out_Exit = r.p1() + (l_slope * lambdaExit);
				return true;
			}

			return false;
		}

		// Tests whether a moving AABB intersects with another AABB
		template<typename valuetype>
		static bool IsIntersecting(const aabb3D<valuetype>& aabb1, const aabb3D<valuetype>& aabb2, const vector3D<valuetype>& motion_aabb1)
		{
			// Convert the aabb-aabb raycast to a ray-aabb raycast
			vector3D<valuetype> l_start(aabb1.center());
			vector3D<valuetype> l_end(l_start + motion_aabb1);
			ray3D<valuetype> l_ray(l_start, l_end);
			vector3D<valuetype> l_combinedExtent(aabb1.extent() + aabb2.extent());
			aabb3D<valuetype> l_aabb(aabb2.center() - l_combinedExtent, aabb2.center() + l_combinedExtent);
			return IsIntersecting(l_ray, l_aabb);
		}

		// Finds the points where a moving AABB enters and exits another AABB
		template<typename valuetype>
		static bool IsIntersecting(const aabb3D<valuetype>& aabb1, const aabb3D<valuetype>& aabb2, const vector3D<valuetype>& motion_aabb1, vector3D<valuetype>& out_Enter, vector3D<valuetype>& out_Exit)
		{
			// Convert the aabb-aabb raycast to a ray-aabb raycast
			vector3D<valuetype> l_start(aabb1.center());
			vector3D<valuetype> l_end(l_start + motion_aabb1);
			ray3D<valuetype> l_ray(l_start, l_end);
			vector3D<valuetype> l_combinedExtent(aabb1.extent() + aabb2.extent());
			aabb3D<valuetype> l_aabb(aabb2.center() - l_combinedExtent, aabb2.center() + l_combinedExtent);
			return IsIntersecting(l_ray, l_aabb, out_Enter, out_Exit);
		}

		////////////////////////////////////////////////// Sphere - AABB

		// Tests whether a sphere intersects an AABB
		template<typename valuetype>
		static bool IsIntersecting(const sphere<valuetype>& s, const aabb3D<valuetype>& aabb)
		{
			// Express the problem in local coordinates to AABB
			vector3D<valuetype> l_ext(aabb.extent());
			sphere<valuetype> l_s(s - aabb.center());

			// Calculate the point on the aabb, closest to the sphere
			vector3D<valuetype> l_closestPoint(
				fmin(fmax(l_s.x(), -l_ext.x()), l_ext.x()),
				fmin(fmax(l_s.y(), -l_ext.y()), l_ext.y())
				);

			// Check whether this point lies within the sphere
			return IsIntersecting(l_closestPoint, l_s);
		}

		// Tests whether a sphere intersects an AABB
		template<typename valuetype>
		inline static bool IsIntersecting(const aabb3D<valuetype>& aabb, const sphere<valuetype>& s)
		{
			return IsIntersecting<valuetype>(s, aabb);
		}

	};
}

#endif