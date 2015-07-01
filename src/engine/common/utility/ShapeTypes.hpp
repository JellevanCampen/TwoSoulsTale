#ifndef ENGINE_COMMON_UTILITY_SHAPETYPES_H
#define ENGINE_COMMON_UTILITY_SHAPETYPES_H

#include "VectorTypes.hpp" // For representing positions
#include "IntervalTypes.hpp" // For representing rectangles

namespace Engine{

	////////////////////////////////////////////////////////////////
	// Rectangle                                                  //
	////////////////////////////////////////////////////////////////

	// Engine::rectanglef (IntervalTypes) 
	// Engine::rectangled (IntervalTypes)

	////////////////////////////////////////////////////////////////
	// Circle                                                     //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct circle
	{

	private:

		vector2D<valuetype> m_P;
		valuetype m_R;

	public:

		// Constructors
		circle() : m_P(0.0, 0.0), m_R(0.0) { }
		circle(vector2D<valuetype> p, valuetype r) : m_P(p), m_R(r) { }
		circle(valuetype x, valuetype y, valuetype r) : m_P(x, y), m_R(r) { }

		// Getters
		inline vector2D<valuetype>& p() { return m_P; }
		inline valuetype& x() { return m_P.x(); }
		inline valuetype& y() { return m_P.y(); }
		inline valuetype& r() { return m_R; }
		inline const vector2D<valuetype>& p() const { return m_P; }
		inline const valuetype& x() const { return m_P.x(); }
		inline const valuetype& y() const { return m_P.y(); }
		inline const valuetype& r() const { return m_R; }

		// Setters
		inline circle& p(vector2D<valuetype> p) { m_P = p; return *this; }
		inline circle& x(valuetype x) { m_P.x(x); return *this; }
		inline circle& y(valuetype y) { m_P.y(y); return *this; }
		inline circle& r(valuetype r) { m_R = r; return *this; }

		// Operators
		inline circle operator+ (const vector2D<valuetype>& v) const { return circle(m_P + v, m_R); }
		inline circle operator- (const vector2D<valuetype>& v) const { return circle(m_P - v, m_R); }
	};

	typedef circle<float> circlef;
	typedef circle<double> circled;

	////////////////////////////////////////////////////////////////
	// Sphere                                                     //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct sphere
	{

	private:

		vector3D<valuetype> m_P;
		valuetype m_R;

	public:

		// Constructors
		sphere() : p(0.0, 0.0, 0.0), r(0.0) { }
		sphere(vector3D<valuetype> p, valuetype r) : m_P(p), m_R(r) { }
		sphere(valuetype x, valuetype y, valuetype z, valuetype r) : m_P(x, y, z), m_R(r) { }

		// Getters
		inline vector3D<valuetype>& p() { return m_P; }
		inline valuetype& x() { return m_P.x(); }
		inline valuetype& y() { return m_P.y(); }
		inline valuetype& z() { return m_P.z(); }
		inline valuetype& r() { return m_R; }
		inline const vector3D<valuetype>& p() const { return m_P; }
		inline const valuetype& x() const { return m_P.x(); }
		inline const valuetype& y() const { return m_P.y(); }
		inline const valuetype& z() const { return m_P.z(); }
		inline const valuetype& r() const { return m_R; }

		// Setters
		inline circle& p(vector3D<valuetype> p) { m_P = p; return *this; }
		inline circle& x(valuetype x) { m_P.x(x); return *this; }
		inline circle& y(valuetype y) { m_P.y(y); return *this; }
		inline circle& z(valuetype z) { m_P.z(z); return *this; }
		inline circle& r(valuetype r) { m_R = r; return *this; }

		// Operators
		inline circle operator+ (const vector3D<valuetype>& v) const { return circle(m_P + v, m_R); }
		inline circle operator- (const vector3D<valuetype>& v) const { return circle(m_P - v, m_R); }
	};

	typedef sphere<float> spheref;
	typedef sphere<double> sphered;

	////////////////////////////////////////////////////////////////
	// Ray2D                                                      //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct ray2D
	{

	private:

		vector2D<valuetype> m_P1, m_P2;

	public:

		// Constructors
		ray2D() : m_P1(0.0, 0.0), m_P2(0.0, 0.0) { }
		ray2D(vector2D<valuetype> p1, vector2D<valuetype> p2) : m_P1(p1), m_P2(p2) { }
		ray2D(valuetype x1, valuetype x2, valuetype y1, valuetype y2) : m_P1(x1, y1), m_P2(x2, y2) { }

		// Getters
		inline vector2D<valuetype>& p1() { return m_P1; }
		inline vector2D<valuetype>& p2() { return m_P2; }
		inline valuetype& x1() { return m_P1.x(); }
		inline valuetype& x2() { return m_P2.x(); }
		inline valuetype& y1() { return m_P1.y(); }
		inline valuetype& y2() { return m_P2.y(); }
		inline const vector2D<valuetype>& p1() const { return m_P1; }
		inline const vector2D<valuetype>& p2() const { return m_P2; }
		inline const valuetype& x1() const { return m_P1.x(); }
		inline const valuetype& x2() const { return m_P2.x(); }
		inline const valuetype& y1() const { return m_P1.y(); }
		inline const valuetype& y2() const { return m_P2.y(); }

		// Setters
		inline ray2D& p1(vector2D<valuetype> p1) { m_P1 = p1; return *this; }
		inline ray2D& p2(vector2D<valuetype> p2) { m_P2 = p2; return *this; }
		inline ray2D& x1(valuetype x1) { m_P1.x(x1); return *this; }
		inline ray2D& x2(valuetype x2) { m_P2.x(x2); return *this; }
		inline ray2D& y1(valuetype y1) { m_P1.y(y1); return *this; }
		inline ray2D& y2(valuetype y2) { m_P2.y(y2); return *this; }

		// Operators
		inline ray2D operator+ (const vector2D<valuetype>& v) const { return ray2D(m_P1 + v, m_P2 + v); }
		inline ray2D operator- (const vector2D<valuetype>& v) const { return ray2D(m_P1 - v, m_P2 - v); }

		// Calculates the slope of the ray
		inline vector2D<valuetype> slope() const { return (m_P2 - m_P1); }
	};

	typedef ray2D<float> ray2Df;
	typedef ray2D<double> ray2Dd;

	////////////////////////////////////////////////////////////////
	// Ray3D                                                      //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct ray3D
	{

	private:

		vector3D<valuetype> m_P1, m_P2;

	public:

		// Constructors
		ray3D() : m_P1(0.0, 0.0, 0.0), m_P2(0.0, 0.0, 0.0) { }
		ray3D(vector3D<valuetype> p1, vector3D<valuetype> p2) : m_P1(p1), m_P2(p2) { }
		ray3D(valuetype x1, valuetype x2, valuetype y1, valuetype y2, valuetype z1, valuetype z2) : m_P1(x1, y1, z1), m_P2(x2, y2, z2) { }

		// Getters
		inline vector3D<valuetype>& p1() { return m_P1; }
		inline vector3D<valuetype>& p2() { return m_P2; }
		inline valuetype& x1() { return m_P1.x(); }
		inline valuetype& x2() { return m_P2.x(); }
		inline valuetype& y1() { return m_P1.y(); }
		inline valuetype& y2() { return m_P2.y(); }
		inline valuetype& z1() { return m_P1.z(); }
		inline valuetype& z2() { return m_P2.z(); }
		inline const vector3D<valuetype>& p1() const { return m_P1; }
		inline const vector3D<valuetype>& p2() const { return m_P2; }
		inline const valuetype& x1() const { return m_P1.x(); }
		inline const valuetype& x2() const { return m_P2.x(); }
		inline const valuetype& y1() const { return m_P1.y(); }
		inline const valuetype& y2() const { return m_P2.y(); }
		inline const valuetype& z1() const { return m_P1.z(); }
		inline const valuetype& z2() const { return m_P2.z(); }

		// Setters
		inline ray3D& p1(vector3D<valuetype> p1) { m_P1 = p1; return *this; }
		inline ray3D& p2(vector3D<valuetype> p2) { m_P2 = p2; return *this; }
		inline ray3D& x1(valuetype x1) { m_P1.x(x1); return *this; }
		inline ray3D& x2(valuetype x2) { m_P2.x(x2); return *this; }
		inline ray3D& y1(valuetype y1) { m_P1.y(y1); return *this; }
		inline ray3D& y2(valuetype y2) { m_P2.y(y2); return *this; }
		inline ray3D& z1(valuetype z1) { m_P1.z(z1); return *this; }
		inline ray3D& z2(valuetype z2) { m_P2.z(z2); return *this; }

		// Operators
		inline ray3D operator+ (const vector3D<valuetype>& v) const { return ray3D(m_P1 + v, m_P2 + v); }
		inline ray3D operator- (const vector3D<valuetype>& v) const { return ray3D(m_P1 - v, m_P2 - v); }

		// Calculates the slope of the ray
		inline vector3D<valuetype> slope() const { return (m_P2 - m_P1); }
	};

	typedef ray3D<float> ray3Df;
	typedef ray3D<double> ray3Dd;
}

#endif
