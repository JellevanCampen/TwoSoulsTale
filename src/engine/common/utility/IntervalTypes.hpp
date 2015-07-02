#ifndef ENGINE_COMMON_UTILITY_INTERVALTYPES_H
#define ENGINE_COMMON_UTILITY_INTERVALTYPES_H

#include "VectorTypes.hpp" // For representing vectors
#include "TransformTypes.hpp" // For representing transforms

namespace Engine
{
	////////////////////////////////////////////////////////////////
	// 1D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename basetype>
	struct interval1D
	{

	private:

		basetype m_X1, m_X2;

	public:

		// Constructors
		interval1D(basetype x1, basetype x2) : m_X1(x1), m_X2(x2) { }
		interval1D() : interval1D(0, 0) { }

		// Getters
		inline basetype& x1() { return m_X1; }
		inline basetype& x2() { return m_X2; }
		inline basetype& x() { return m_X1; }
		inline basetype& w() { return m_X2 - m_X1; }
		inline const basetype& x1() const { return m_X1; }
		inline const basetype& x2() const { return m_X2; }
		inline const basetype& x() const { return m_X1; }
		inline const basetype& w() const { return m_X2 - m_X1; }

		// Setters
		inline interval1D& x1(basetype x1) { m_X1 = x1; return *this; }
		inline interval1D& x2(basetype x2) { m_X2 = x2; return *this; }
		inline interval1D& x(basetype x) { m_X1 = x; return *this; }
		inline interval1D& w(basetype w) { m_X2 = m_X1 + w; return *this; }

		// Operators
		inline bool operator== (const interval1D& other) const { return (m_X1 == other.m_X1 && m_X2 == other.m_X2); }
		inline bool operator!= (const interval1D& other) const { return !(*this == other); }
		inline interval1D operator+ (const basetype& other) const { return interval1D(m_X1 + other.m_X1, m_X2 + other.m_X2); }
		inline interval1D operator- (const basetype& other) const { return interval1D(m_X1 - other.m_X1, m_X2 - other.m_X2); }
		inline interval1D operator* (basetype scalar) const { return interval1D(m_X1 * scalar, m_X2 * scalar); }
		inline interval1D operator/ (basetype scalar) const { return interval1D(m_X1 / scalar, m_X2 / scalar); }

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval1D GetTransformed(transform1D t1D) const { return interval1D(m_X1 * t1D.s() + t1D.t(), m_X2 * t1D.s() + t1D.t()); }

		// Calculates the AABB that contains the sweeped version of the interval
		inline interval1D GetSweeped(basetype velocity) const
		{  
			return interval1D(
				(velocity.x() < 0) ? m_X1 + velocity.x() : m_X1,
				(velocity.x() > 0) ? m_X2 + velocity.x() : m_X2
				);
		}

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x) const { return (x >= m_X1 && x <= m_X2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x) const { return (x > m_X1 && x < m_X2); }

		// Checks whether the specified interval overlaps with this interval (boundaries included)
		inline bool Overlaps(const interval1D& other) const { return ((other.m_X2 >= m_X1) && (other.m_X1 <= m_X2)); }

		// Checks whether the specified interval overlaps with this interval (boundaries not included)
		inline bool OverlapsStrict(const interval1D& other) const { return ((other.m_X2 > m_X1) && (other.m_X1 < m_X2)); }
	};

	typedef interval1D<int> interval1Di, aabb1Di, linesegmenti;
	typedef interval1D<float> interval1Df, aabb1Df, linesegmentf;

	////////////////////////////////////////////////////////////////
	// 2D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename basetype>
	struct interval2D
	{

	private:

		basetype m_X1, m_X2;
		basetype m_Y1, m_Y2;

	public:

		// Constructors
		interval2D(basetype x1, basetype x2, basetype y1, basetype y2) : m_X1(x1), m_X2(x2), m_Y1(y1), m_Y2(y2) { }
		interval2D(vector2D<basetype> p1, vector2D<basetype> p2) : m_X1(p1.x()), m_X2(p2.x()), m_Y1(p1.y()), m_Y2(p2.y()) { }
		interval2D() : interval2D(0, 0, 0, 0) { }

		// Casts
		inline operator interval1D<basetype>() const { return interval1D<basetype>(m_X1, m_X2); }

		// Getters
		inline basetype& x1() { return m_X1; }
		inline basetype& x2() { return m_X2; }
		inline basetype& y1() { return m_Y1; }
		inline basetype& y2() { return m_Y2; }
		inline basetype& x() { return m_X1; }
		inline basetype& w() { return m_X2 - m_X1; }
		inline basetype& y() { return m_Y1; }
		inline basetype& h() { return m_Y2 - m_Y1; }
		inline const basetype& x1() const { return m_X1; }
		inline const basetype& x2() const { return m_X2; }
		inline const basetype& y1() const { return m_Y1; }
		inline const basetype& y2() const { return m_Y2; }
		inline const basetype& x() const { return m_X1; }
		inline const basetype& w() const { return m_X2 - m_X1; }
		inline const basetype& y() const { return m_Y1; }
		inline const basetype& h() const { return m_Y2 - m_Y1; }

		// Setters
		inline interval2D& x1(basetype x1) { m_X1 = x1; return *this; }
		inline interval2D& x2(basetype x2) { m_X2 = x2; return *this; }
		inline interval2D& y1(basetype y1) { m_Y1 = y1; return *this; }
		inline interval2D& y2(basetype y2) { m_Y2 = y2; return *this; }
		inline interval2D& x(basetype x) { m_X1 = x; return *this; }
		inline interval2D& w(basetype w) { m_X2 = m_X1 + w; return *this; }
		inline interval2D& y(basetype y) { m_Y1 = y; return *this; }
		inline interval2D& h(basetype h) { m_Y2 = m_Y1 + h; return *this; }

		// Operators
		inline bool operator== (const interval2D& other) const { return (m_X1 == other.m_X1 && m_X2 == other.m_X2 && m_Y1 == other.m_Y1 && m_Y2 == other.m_Y2); }
		inline bool operator!= (const interval2D& other) const { return !(*this == other); }
		inline interval2D operator+ (const basetype& other) const { return interval2D(m_X1 + other.m_X1, m_X2 + other.m_X2, m_Y1 + other.m_Y1, m_Y2 + other.m_Y2); }
		inline interval2D operator- (const basetype& other) const { return interval2D(m_X1 - other.m_X1, m_X2 - other.m_X2, m_Y1 - other.m_Y1, m_Y2 - other.m_Y2); }
		inline interval2D operator* (basetype scalar) const { return interval2D(m_X1 * scalar, m_X2 * scalar, m_Y1 * scalar, m_Y2 * scalar); }
		inline interval2D operator/ (basetype scalar) const { return interval2D(m_X1 / scalar, m_X2 / scalar, m_Y1 / scalar, m_Y2 / scalar); }

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval2D GetTransformed(transform2D t2D) const { return interval2D(m_X1 * t2D.s().x() + t2D.t().x(), m_X2 * t2D.s().x() + t2D.t().x(), m_Y1 * t2D.s().y() + t2D.t().y(), m_Y2 * t2D.s().y() + t2D.t().y()); }

		// Calculates the AABB that contains the sweeped version of the interval
		inline interval2D GetSweeped(vector2D<basetype> velocity) const
		{
			return interval2D(
				(velocity.x() < 0) ? m_X1 + velocity.x() : m_X1,
				(velocity.x() > 0) ? m_X2 + velocity.x() : m_X2,
				(velocity.y() < 0) ? m_Y1 + velocity.y() : m_Y1,
				(velocity.y() > 0) ? m_Y2 + velocity.y() : m_Y2
				);
		}

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x, basetype y) const { return (x >= m_X1 && x <= m_X2 && y >= m_Y1 && y <= m_Y2); }
		inline bool Contains(vector2D<basetype> p) const { return (p.x() >= m_X1 && p.x() <= m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x, basetype y) const { return (x > m_X1 && x < m_X2 && y >= m_Y1 && y <= m_Y2); }
		inline bool ContainsStrict(vector2D<basetype> p) const { return (p.x() > m_X1 && p.x() < m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2); }

		// Checks whether the specified interval overlaps with this interval (boundaries included)
		inline bool Overlaps(const interval2D& other) const { 
			return ((other.m_X2 >= m_X1) && (other.m_X1 <= m_X2)
			&& (other.m_Y2 >= m_Y1) && (other.m_Y1 <= m_Y2)); 
		}

		// Checks whether the specified interval overlaps with this interval (boundaries not included)
		inline bool OverlapsStrict(const interval2D& other) const {
			return ((other.m_X2 > m_X1) && (other.m_X1 < m_X2)
				&& (other.m_Y2 > m_Y1) && (other.m_Y1 < m_Y2)); 
		}
	};

	typedef interval2D<int> interval2Di, aabb2Di, rectanglei;
	typedef interval2D<float> interval2Df, aabb2Df, rectanglef;
	typedef interval2D<double> interval2Dd, aabb2Dd, rectangled;

	////////////////////////////////////////////////////////////////
	// 3D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename basetype>
	struct interval3D
	{

	private:

		basetype m_X1, m_X2;
		basetype m_Y1, m_Y2;
		basetype m_Z1, m_Z2;

	public:

		// Constructors
		interval3D(basetype x1, basetype x2, basetype y1, basetype y2, basetype z1, basetype z2) : m_X1(x1), m_X2(x2), m_Y1(y1), m_Y2(y2), m_Z1(z1), m_Z2(z2) { }
		interval3D(vector3D<basetype> p1, vector3D<basetype> p2) : m_X1(p1.x()), m_X2(p2.x()) m_Y1(p1.y()), m_Y2(p2.y()), m_Z1(p1.z()), m_Z2(p2.z()) { }
		interval3D() : interval3D(0, 0, 0, 0, 0, 0) { }

		// Casts
		inline operator interval2D<basetype>() const { return interval2D<basetype>(m_X1, m_X2, m_Y1, m_Y2); }
		inline operator interval1D<basetype>() const { return interval1D<basetype>(m_X1, m_X2); }

		// Getters
		inline basetype& x1() { return m_X1; }
		inline basetype& x2() { return m_X2; }
		inline basetype& y1() { return m_Y1; }
		inline basetype& y2() { return m_Y2; }
		inline basetype& z1() { return m_Z1; }
		inline basetype& z2() { return m_Z2; }
		inline basetype& x() { return m_X1; }
		inline basetype& w() { return m_X2 - m_X1; }
		inline basetype& y() { return m_Y1; }
		inline basetype& h() { return m_Y2 - m_Y1; }
		inline basetype& z() { return m_Z1; }
		inline basetype& d() { return m_Z2 - m_Z1; }
		inline const basetype& x1() const { return m_X1; }
		inline const basetype& x2() const { return m_X2; }
		inline const basetype& y1() const { return m_Y1; }
		inline const basetype& y2() const { return m_Y2; }
		inline const basetype& z1() const { return m_Z1; }
		inline const basetype& z2() const { return m_Z2; }
		inline const basetype& x() const { return m_X1; }
		inline const basetype& w() const { return m_X2 - m_X1; }
		inline const basetype& y() const { return m_Y1; }
		inline const basetype& h() const { return m_Y2 - m_Y1; }
		inline const basetype& z() const { return m_Z1; }
		inline const basetype& d() const { return m_Z2 - m_Z1; }

		// Setters
		inline interval3D& x1(basetype x1) { m_X1 = x1; return *this; }
		inline interval3D& x2(basetype x2) { m_X2 = x2; return *this; }
		inline interval3D& y1(basetype y1) { m_Y1 = y1; return *this; }
		inline interval3D& y2(basetype y2) { m_Y2 = y2; return *this; }
		inline interval3D& z1(basetype z1) { m_Z1 = z1; return *this; }
		inline interval3D& z2(basetype z2) { m_Z2 = z2; return *this; }
		inline interval3D& x(basetype x) { m_X1 = x; return *this; }
		inline interval3D& w(basetype w) { m_X2 = m_X1 + w; return *this; }
		inline interval3D& y(basetype y) { m_Y1 = y; return *this; }
		inline interval3D& h(basetype h) { m_Y2 = m_Y1 + h; return *this; }
		inline interval3D& z(basetype z) { m_Z1 = z; return *this; }
		inline interval3D& d(basetype d) { m_Z2 = m_Z1 + d; return *this; }

		// Operators
		inline bool operator== (const interval3D& other) const { return (m_X1 == other.m_X1 && m_X2 == other.m_X2 && m_Y1 == other.m_Y1 && m_Y2 == other.m_Y2 && m_Z1 == other.m_Z1 && m_Z2 == other.m_Z2); }
		inline bool operator!= (const interval3D& other) const { return !(*this == other); }
		inline interval3D operator+ (const basetype& other) const { return interval3D(m_X1 + other.m_X1, m_X2 + other.m_X2, m_Y1 + other.m_Y1, m_Y2 + other.m_Y2, m_Z1 + other.m_Z1, m_Z2 + other.m_Z2); }
		inline interval3D operator- (const basetype& other) const { return interval3D(m_X1 - other.m_X1, m_X2 - other.m_X2, m_Y1 - other.m_Y1, m_Y2 - other.m_Y2, m_Z1 - other.m_Z1, m_Z2 - other.m_Z2); }
		inline interval3D operator* (basetype scalar) const { return interval3D(m_X1 * scalar, m_X2 * scalar, m_Y1 * scalar, m_Y2 * scalar, m_Z1 * scalar, m_Z2 * scalar); }
		inline interval3D operator/ (basetype scalar) const { return interval3D(m_X1 / scalar, m_X2 / scalar, m_Y1 / scalar, m_Y2 / scalar, m_Z1 / scalar, m_Z2 / scalar); }

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval3D GetTransformed(transform3D t3D) const { return interval3D(m_X1 * t3D.s().x() + t3D.t().x(), m_X2 * t3D.s().x() + t3D.t().x(), m_Y1 * t3D.s().y() + t3D.t().y(), m_Y2 * t3D.s().y() + t3D.t().y(), m_Z1 * t3D.s().z() + t3D.t().z(), m_Z2 * t3D.s().z() + t3D.t().z()); }

		// Calculates the AABB that contains the sweeped version of the interval
		inline interval3D GetSweeped(vector3D<basetype> velocity) const
		{
			return interval3D(
				(velocity.x() < 0) ? m_X1 + velocity.x() : m_X1,
				(velocity.x() > 0) ? m_X2 + velocity.x() : m_X2,
				(velocity.y() < 0) ? m_Y1 + velocity.y() : m_Y1,
				(velocity.y() > 0) ? m_Y2 + velocity.y() : m_Y2,
				(velocity.z() < 0) ? m_Z1 + velocity.z() : m_Z1,
				(velocity.z() > 0) ? m_Z2 + velocity.z() : m_Z2
				);
		}

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x, basetype y, basetype z) const { return (x >= m_X1 && x <= m_X2 && y >= m_Y1 && y <= m_Y2 && z >= m_Z1 && z <= m_Z2); }
		inline bool Contains(vector3D<basetype> p) const { return (p.x() >= m_X1 && p.x() <= m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2 && p.z() >= m_Z1 && p.z() <= m_Z2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x, basetype y, basetype z) const { return (x > m_X1 && x < m_X2 && y >= m_Y1 && y <= m_Y2 && z >= m_Z1 && z <= m_Z2); }
		inline bool ContainsStrict(vector3D<basetype> p) const { return (p.x() > m_X1 && p.x() < m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2 && p.z() >= m_Z1 && p.z() <= m_Z2); }

		// Checks whether the specified interval overlaps with this interval (boundaries included)
		inline bool Overlaps(const interval3D& other) const {
			return ((other.m_X2 >= m_X1) && (other.m_X1 <= m_X2)
				&& (other.m_Y2 >= m_Y1) && (other.m_Y1 <= m_Y2)
				&& (other.m_Z2 >= m_Z1) && (other.m_Z1 <= m_Z2));
		}

		// Checks whether the specified interval overlaps with this interval (boundaries not included)
		inline bool OverlapsStrict(const interval3D& other) const {
			return ((other.m_X2 > m_X1) && (other.m_X1 < m_X2)
				&& (other.m_Y2 > m_Y1) && (other.m_Y1 < m_Y2)
				&& (other.m_Z2 > m_Z1) && (other.m_Z1 < m_Z2));
		}
	};

	typedef interval3D<int> interval3Di, aabb3Di, boxi;
	typedef interval3D<float> interval3Df, aabb3Df, boxf;
}

#endif
