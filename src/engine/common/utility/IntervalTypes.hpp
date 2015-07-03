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

		basetype m_P1, m_P2;

	public:

		// Constructors
		interval1D() : m_P1(0), m_P2(0) { }
		interval1D(basetype x1, basetype x2) : m_P1(x1), m_P2(x2) { }

		// Getters
		inline basetype& x1() { return m_P1; }
		inline basetype& x2() { return m_P2; }
		inline basetype& x() { return m_P1; }
		inline basetype& w() { return m_P2 - m_P1; }
		inline const basetype& x1() const { return m_P1; }
		inline const basetype& x2() const { return m_P2; }
		inline const basetype& x() const { return m_P1; }
		inline const basetype& w() const { return m_P2 - m_P1; }

		// Setters
		inline interval1D& x1(basetype x1) { m_P1 = x1; return *this; }
		inline interval1D& x2(basetype x2) { m_P2 = x2; return *this; }
		inline interval1D& x(basetype x) { m_P1 = x; return *this; }
		inline interval1D& w(basetype w) { m_P2 = m_P1 + w; return *this; }

		// Operators
		inline bool operator== (const interval1D& other) const { return (m_P1 == other.m_P1 && m_P2 == other.m_P2); }
		inline bool operator!= (const interval1D& other) const { return !(*this == other); }
		inline interval1D operator+ (const basetype& other) const { return interval1D(m_P1 + other.m_P1, m_P2 + other.m_P2); }
		inline interval1D operator- (const basetype& other) const { return interval1D(m_P1 - other.m_P1, m_P2 - other.m_P2); }
		inline interval1D operator* (basetype scalar) const { return interval1D(m_P1 * scalar, m_P2 * scalar); }
		inline interval1D operator/ (basetype scalar) const { return interval1D(m_P1 / scalar, m_P2 / scalar); }

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval1D GetTransformed(transform1D t1D) const { return interval1D(m_P1 * t1D.s() + t1D.t(), m_P2 * t1D.s() + t1D.t()); }

		// Calculates the AABB that contains the sweeped version of the interval
		inline interval1D GetSweeped(basetype velocity) const
		{  
			return interval1D(
				(velocity.x() < 0) ? m_P1 + velocity.x() : m_P1,
				(velocity.x() > 0) ? m_P2 + velocity.x() : m_P2
				);
		}

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x) const { return (x >= m_P1 && x <= m_P2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x) const { return (x > m_P1 && x < m_P2); }

		// Checks whether the specified interval overlaps with this interval (boundaries included)
		inline bool Overlaps(const interval1D& other) const { return ((other.m_P2 >= m_P1) && (other.m_P1 <= m_P2)); }

		// Checks whether the specified interval overlaps with this interval (boundaries not included)
		inline bool OverlapsStrict(const interval1D& other) const { return ((other.m_P2 > m_P1) && (other.m_P1 < m_P2)); }
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

		vector2D<basetype> m_P1, m_P2;

	public:

		// Constructors
		interval2D() { }
		interval2D(basetype x1, basetype x2, basetype y1, basetype y2) : m_P1(x1, y1), m_P2(x2, y2) { }
		interval2D(vector2D<basetype> p1, vector2D<basetype> p2) : m_P1(p1), m_P2(p2) { }

		// Casts
		inline operator interval1D<basetype>() const { return interval1D<basetype>(m_P1.x(), m_P2.x()); }

		// Getters
		inline vector2D<basetype>& p1() { return m_P1; }
		inline vector2D<basetype>& p2() { return m_P2; }
		inline basetype& x1() { return m_P1.x(); }
		inline basetype& x2() { return m_P2.x(); }
		inline basetype& y1() { return m_P1.y(); }
		inline basetype& y2() { return m_P2.y(); }
		inline basetype& x() { return m_P1.x(); }
		inline basetype& w() { return m_P2.x() - m_P1.x(); }
		inline basetype& y() { return m_P1.y(); }
		inline basetype& h() { return m_P2.y() - m_P1.y(); }

		inline const vector2D<basetype>& p1() const { return m_P1; }
		inline const vector2D<basetype>& p2() const { return m_P2; }
		inline const basetype& x1() const { return m_P1.x(); }
		inline const basetype& x2() const { return m_P2.x(); }
		inline const basetype& y1() const { return m_P1.y(); }
		inline const basetype& y2() const { return m_P2.y(); }
		inline const basetype& x() const { return m_P1.x(); }
		inline const basetype w() const { return m_P2.x() - m_P1.x(); }
		inline const basetype& y() const { return m_P1.y(); }
		inline const basetype h() const { return m_P2.y() - m_P1.y(); }

		// Setters
		inline interval2D& p1(vector2D<basetype> p1) { m_P1 = p1; return *this; }
		inline interval2D& p2(vector2D<basetype> p2) { m_P2 = p2; return *this; }
		inline interval2D& x1(basetype x1) { m_P1.x(x1); return *this; }
		inline interval2D& x2(basetype x2) { m_P2.x(x2); return *this; }
		inline interval2D& y1(basetype y1) { m_P1.y(y1); return *this; }
		inline interval2D& y2(basetype y2) { m_P2.y(y2); return *this; }
		inline interval2D& x(basetype x) { m_P1.x(x); return *this; }
		inline interval2D& w(basetype w) { m_P2.x(m_P1.x() + w); return *this; }
		inline interval2D& y(basetype y) { m_P1.y(y); return *this; }
		inline interval2D& h(basetype h) { m_P2.y(m_P1.y() + h); return *this; }

		// Operators
		inline bool operator== (const interval2D& other) const { return (m_P1 == other.m_P1 && m_P2 == other.m_P2); }
		inline bool operator!= (const interval2D& other) const { return !(*this == other); }
		inline interval2D operator+ (const interval2D& other) const { return interval2D(m_P1 + other.m_P1, m_P2 + other.m_P2); }
		inline interval2D operator- (const interval2D& other) const { return interval2D(m_P1 - other.m_P1, m_P2 - other.m_P2); }
		inline interval2D operator+ (const vector2D<basetype>& other) const { return interval2D(m_P1 + other, m_P2 + other); }
		inline interval2D operator- (const vector2D<basetype>& other) const { return interval2D(m_P1 - other, m_P2 - other); }
		inline interval2D operator* (const basetype& scalar) const { return interval2D(m_P1 * scalar, m_P2 * scalar); }
		inline interval2D operator/ (const basetype& scalar) const { return interval2D(m_P1 / scalar, m_P2 / scalar); }
		inline interval2D operator* (const vector2D<basetype>& scale) const { return interval2D(m_P1.x() * scale.x(), m_P2.x() * scale.x(), m_P1.y() * scale.y(), m_P2.y() * scale.y()); }
		inline interval2D operator/ (const vector2D<basetype>& scale) const { return interval2D(m_P1.x() / scale.x(), m_P2.x() / scale.x(), m_P1.y() / scale.y(), m_P2.y() / scale.y()); }

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval2D GetTransformed(transform2D t2D) const { return ((*this) * t2D.s()) + t2D.t(); }

		// Calculates the AABB that contains the sweeped version of the interval
		inline interval2D GetSweeped(vector2D<basetype> velocity) const
		{
			return interval2D(
				(velocity.x() < 0) ? m_P1.x() + velocity.x() : m_P1.x(),
				(velocity.x() > 0) ? m_P2.x() + velocity.x() : m_P2.x(),
				(velocity.y() < 0) ? m_P1.y() + velocity.y() : m_P1.y(),
				(velocity.y() > 0) ? m_P2.y() + velocity.y() : m_P2.y()
				);
		}

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x, basetype y) const { return (x >= m_P1.x() && x <= m_P2.x() && y >= m_P1.y() && y <= m_P2.y()); }
		inline bool Contains(vector2D<basetype> p) const { return (p.x() >= m_P1.x() && p.x() <= m_P2.x() && p.y() >= m_P1.y() && p.y() <= m_P2.y()); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x, basetype y) const { return (x > m_P1.x() && x < m_P2.x() && y > m_P1.y() && y < m_P2.y()); }
		inline bool ContainsStrict(vector2D<basetype> p) const { return (p.x() > m_P1.x() && p.x() < m_P2.x() && p.y() > m_P1.y() && p.y() < m_P2.y()); }

		// Checks whether the specified interval overlaps with this interval (boundaries included)
		inline bool Overlaps(const interval2D& other) const { 
			return ((other.m_P2.x() >= m_P1.x()) && (other.m_P1.x() <= m_P2.x())
				&& (other.m_P2.y() >= m_P1.y()) && (other.m_P1.y() <= m_P2.y())); 
		}

		// Checks whether the specified interval overlaps with this interval (boundaries not included)
		inline bool OverlapsStrict(const interval2D& other) const {
			return ((other.m_P2.x() > m_P1.x()) && (other.m_P1.x() < m_P2.x())
				&& (other.m_P2.y() > m_P1.y()) && (other.m_P1.y() < m_P2.y()));
		}
	};

	typedef interval2D<int> interval2Di, aabb2Di;
	typedef interval2D<float> interval2Df, aabb2Df;
	typedef interval2D<double> interval2Dd, aabb2Dd;
	template<typename valuetype> using rectangle = interval2D < valuetype >;
	typedef rectangle<int> rectanglei;
	typedef rectangle<float> rectanglef;
	typedef rectangle<double> rectangled;

	////////////////////////////////////////////////////////////////
	// 3D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename basetype>
	struct interval3D
	{

	private:

		vector3D<basetype> m_P1, m_P2;

	public:

		// Constructors
		interval3D() { }
		interval3D(basetype x1, basetype x2, basetype y1, basetype y2, basetype z1, basetype z2) : m_P1(x1, y1, z1), m_P2(x2, y2, z2) { }
		interval3D(vector3D<basetype> p1, vector3D<basetype> p2) : m_P1(p1), m_P2(p2) { }

		// Casts
		inline operator interval2D<basetype>() const { return interval2D<basetype>(m_P1.xy(), m_P2.xy()); }
		inline operator interval1D<basetype>() const { return interval1D<basetype>(m_P1.x(), m_P2.x()); }

		// Getters
		inline vector3D<basetype>& p1() { return m_P1; }
		inline vector3D<basetype>& p2() { return m_P2; }
		inline basetype& x1() { return m_P1.x(); }
		inline basetype& x2() { return m_P2.x(); }
		inline basetype& y1() { return m_P1.y(); }
		inline basetype& y2() { return m_P2.y(); }
		inline basetype& z1() { return m_P1.z(); }
		inline basetype& z2() { return m_P2.z(); }
		inline basetype& x() { return m_P1.x(); }
		inline basetype& w() { return m_P2.x() - m_P1.x(); }
		inline basetype& y() { return m_P1.y(); }
		inline basetype& h() { return m_P2.y() - m_P1.y(); }
		inline basetype& z() { return m_P1.z(); }
		inline basetype& d() { return m_P2.z() - m_P1.z(); }
		inline const vector3D<basetype>& p1() const { return m_P1; }
		inline const vector3D<basetype>& p2() const { return m_P2; }
		inline const basetype& x1() const { return m_P1.x(); }
		inline const basetype& x2() const { return m_P2.x(); }
		inline const basetype& y1() const { return m_P1.y(); }
		inline const basetype& y2() const { return m_P2.y(); }
		inline const basetype& z1() const { return m_P1.z(); }
		inline const basetype& z2() const { return m_P2.z(); }
		inline const basetype& x() const { return m_P1.x(); }
		inline const basetype& w() const { return m_P2.x() - m_P1.x(); }
		inline const basetype& y() const { return m_P1.y(); }
		inline const basetype h() const { return m_P2.y() - m_P1.y(); }
		inline const basetype& z() const { return m_P1.z(); }
		inline const basetype d() const { return m_P2.z() - m_P1.z(); }

		// Setters
		inline interval3D& p1(vector3D<basetype> p1) { m_P1 = p1; return *this; }
		inline interval3D& p2(vector3D<basetype> p2) { m_P2 = p2; return *this; }
		inline interval3D& x1(basetype x1) { m_P1.x(x1); return *this; }
		inline interval3D& x2(basetype x2) { m_P2.x(x2); return *this; }
		inline interval3D& y1(basetype y1) { m_P1.y(y1); return *this; }
		inline interval3D& y2(basetype y2) { m_P2.y(y2); return *this; }
		inline interval3D& z1(basetype z1) { m_P1.z(z1); return *this; }
		inline interval3D& z2(basetype z2) { m_P2.z(z2); return *this; }
		inline interval3D& x(basetype x) { m_P1.x(x); return *this; }
		inline interval3D& w(basetype w) { m_P2.x(m_P1.x() + w); return *this; }
		inline interval3D& y(basetype y) { m_P1.y(y); return *this; }
		inline interval3D& h(basetype h) { m_P2.y(m_P1.y() + h); return *this; }
		inline interval3D& z(basetype z) { m_P1.z(z); return *this; }
		inline interval3D& d(basetype d) { m_P2.z(m_P1.z() + d); return *this; }

		// Operators
		inline bool operator== (const interval3D& other) const { return (m_P1 == other.m_P1 && m_P2 == other.m_P2); }
		inline bool operator!= (const interval3D& other) const { return !(*this == other); }
		inline interval3D operator+ (const interval3D& other) const { return interval3D(m_P1 + other.m_P1, m_P2 + other.m_P2); }
		inline interval3D operator- (const interval3D& other) const { return interval3D(m_P1 - other.m_P1, m_P2 - other.m_P2); }
		inline interval3D operator+ (const vector3D<basetype>& other) const { return interval3D(m_P1 + other, m_P2 + other); }
		inline interval3D operator- (const vector3D<basetype>& other) const { return interval3D(m_P1 - other, m_P2 - other); }
		inline interval3D operator* (basetype& scalar) const { return interval3D(m_P1 * scalar, m_P2 * scalar); }
		inline interval3D operator/ (basetype& scalar) const { return interval3D(m_P1 / scalar, m_P2 / scalar); }
		inline interval3D operator* (vector3D<basetype>& scale) const { return interval3D(m_P1.x() * scale.x(), m_P2.x() * scale.x(), m_P1.y() * scale.y(), m_P2.y() * scale.y(), m_P1.z() * scale.z(), m_P2.z() * scale.z()); }
		inline interval3D operator/ (vector3D<basetype>& scale) const { return interval3D(m_P1.x() / scale.x(), m_P2.x() / scale.x(), m_P1.y() / scale.y(), m_P2.y() / scale.y(), m_P1.z() / scale.z(), m_P2.z() / scale.z()); }

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval3D GetTransformed(transform3D t3D) const { return ((*this) * t3D.s()) + t3D.t(); }

		// Calculates the AABB that contains the sweeped version of the interval
		inline interval3D GetSweeped(vector3D<basetype> velocity) const
		{
			return interval3D(
				(velocity.x() < 0) ? m_P1.x() + velocity.x() : m_P1.x(),
				(velocity.x() > 0) ? m_P2.x() + velocity.x() : m_P2.x(),
				(velocity.y() < 0) ? m_P1.y() + velocity.y() : m_P1.y(),
				(velocity.y() > 0) ? m_P2.y() + velocity.y() : m_P2.y(),
				(velocity.z() < 0) ? m_P1.z() + velocity.z() : m_P1.z(),
				(velocity.z() > 0) ? m_P2.z() + velocity.z() : m_P2.z()
				);
		}

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x, basetype y, basetype z) const { return (x >= m_P1.x() && x <= m_P2.x() && y >= m_P1.y() && y <= m_P2.y() && z >= m_P1.z() && z <= m_P2.z()); }
		inline bool Contains(vector3D<basetype> p) const { return (p.x() >= m_P1.x() && p.x() <= m_P2.x() && p.y() >= m_P1.y() && p.y() <= m_P2.y() && p.z() >= m_P1.z() && p.z() <= m_P2.z()); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x, basetype y, basetype z) const { return (x > m_P1.x() && x < m_P2.x() && y > m_P1.y() && y < m_P2.y() && z > m_P1.z() && z < m_P2.z()); }
		inline bool ContainsStrict(vector3D<basetype> p) const { return (p.x() > m_P1.x() && p.x() < m_P2.x() && p.y() > m_P1.y() && p.y() < m_P2.y() && p.z() > m_P1.z() && p.z() < m_P2.z()); }

		// Checks whether the specified interval overlaps with this interval (boundaries included)
		inline bool Overlaps(const interval3D& other) const {
			return ((other.m_P2.x() >= m_P1.x()) && (other.m_P1.x() <= m_P2.x())
				&& (other.m_P2.y() >= m_P1.y()) && (other.m_P1.y() <= m_P2.y())
				&& (other.m_P2.z() >= m_P1.z()) && (other.m_P1.z() <= m_P2.z()));
		}

		// Checks whether the specified interval overlaps with this interval (boundaries not included)
		inline bool OverlapsStrict(const interval3D& other) const {
			return ((other.m_P2.x() > m_P1.x()) && (other.m_P1.x() < m_P2.x())
				&& (other.m_P2.y() > m_P1.y()) && (other.m_P1.y() < m_P2.y())
				&& (other.m_P2.z() > m_P1.z()) && (other.m_P1.z() < m_P2.z()));
		}
	};

	typedef interval3D<int> interval3Di, aabb3Di;
	typedef interval3D<float> interval3Df, aabb3Df;
	typedef interval3D<double> interval3Dd, aabb3Dd;
	template<typename valuetype> using box = interval3D < valuetype >;
	typedef box<int> boxi;
	typedef box<float> boxf;
	typedef box<double> boxd;
}

#endif
