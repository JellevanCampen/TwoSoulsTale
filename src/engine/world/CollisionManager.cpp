#include "CollisionManager.hpp"

// Initializes the collision manager
void Engine::CollisionManager::Initialize()
{

}

// Destroys the collision manager
void Engine::CollisionManager::Terminate()
{

}

////////////////////////////////////////////////////////////////
// 2D intersection testing                                    //
////////////////////////////////////////////////////////////////

// Tests whether two circles intersect
bool Engine::CollisionManager::IsIntersecting(const circled& c1, const circled& c2)
{
	d2 d(c1.p() - c2.p());
	return (d * d) <= pow(c1.r() + c2.r(), 2);
}

// Calculates the distance between two circles
double Engine::CollisionManager::GetDistance(const circled& c1, const circled& c2)
{
	d2 d(c1.p() - c2.p());
	return fmax(d.Length() - (c1.r() + c2.r()), 0);
}

// Calculates the penetration of two circles
double Engine::CollisionManager::GetPenetration(const circled& c1, const circled& c2)
{
	d2 d(c1.p() - c2.p());
	return fmax((c1.r() + c2.r()) - d.Length(), 0);
}

// Tests whether a ray intersects with a circle
bool Engine::CollisionManager::IsIntersecting(const ray2Dd& r, const circled& c)
{
	// Ray in local coordinates of the circle
	ray2Dd ray(r.p1() - c.p(), r.p2() - c.p());
	d2 slope(ray.slope());
	double sigma = pow(ray.p1() * slope, 2) - (slope * slope) * ((ray.p1() * ray.p1()) - pow(c.r(), 2));

	// The infinite extension of the ray intersects the sphere
	if (sigma >= 0)
	{
		double lambda1 = (-(ray.p1() * slope) - sqrt(sigma)) / (slope * slope);
		double lambda2 = (-(ray.p1() * slope) + sqrt(sigma)) / (slope * slope);

		// The ray intersects the sphere
		if (lambda1 <= 1 && lambda2 >= 0) 
		{
			return true;
		}
	}

	return false;
}

// Finds the points where a ray enters and exits a circle
bool Engine::CollisionManager::IsIntersecting(const ray2Dd& r, const circled& c, d2& out_Enter, d2& out_Exit)
{
	// Ray in local coordinates of the circle
	ray2Dd ray(r.p1() - c.p(), r.p2() - c.p());
	d2 slope(ray.slope());
	double sigma = pow(ray.p1() * slope, 2) - (slope * slope) * ((ray.p1() * ray.p1()) - pow(c.r(), 2));

	// The infinite extension of the ray intersects the sphere
	if (sigma >= 0)
	{
		double lambda1 = (-(ray.p1() * slope) - sqrt(sigma)) / (slope * slope);
		double lambda2 = (-(ray.p1() * slope) + sqrt(sigma)) / (slope * slope);

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
bool Engine::CollisionManager::IsIntersecting(const circled& c1, const circled& c2, const d2& motion_c1)
{
	d2 start(c1.p());
	d2 end(c1.p() + motion_c1);
	ray2Dd r(start, end);
	circled c(c2.p(), c1.r() + c2.r());
	d2 enter, exit;
	return IsIntersecting(r, c);
}

// Finds the points where a moving circle enters and exits another circle
bool Engine::CollisionManager::IsIntersecting(const circled& c1, const circled& c2, const d2& motion_c1, d2& out_Enter, d2& out_Exit)
{
	d2 start(c1.p());
	d2 end(c1.p() + motion_c1);
	ray2Dd r(start, end);
	circled c(c2.p(), c1.r() + c2.r());
	d2 enter, exit;
	return IsIntersecting(r, c, out_Enter, out_Exit);
}

////////////////////////////////////////////////////////////////
// 3D intersection testing                                    //
////////////////////////////////////////////////////////////////

// TODO