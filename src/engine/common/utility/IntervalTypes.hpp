#ifndef ENGINE_COMMON_UTILITY_INTERVALTYPES_H
#define ENGINE_COMMON_UTILITY_INTERVALTYPES_H

#include "VectorTypes.hpp" // For representing vectors
#include "TransformTypes.hpp" // For representing transforms

namespace Engine
{
	// Typdef for representing outcodes of points for intervals
	typedef unsigned char pointOutcode;

	////////////////////////////////////////////////////////////////
	// 1D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct interval1D
	{

	private:

		valuetype m_P1, m_P2;

	public:

		// Constructors
		interval1D() : m_P1(0), m_P2(0) { }
		interval1D(valuetype x1, valuetype x2) : m_P1(x1), m_P2(x2) { }

		// Getters
		inline valuetype& p1() { return m_P1; }
		inline valuetype& p2() { return m_P2; }
		inline valuetype& x1() { return m_P1; }
		inline valuetype& x2() { return m_P2; }
		inline valuetype& x() { return m_P1; }
		inline valuetype& w() { return m_P2 - m_P1; }
		inline const valuetype& p1() const { return m_P1; }
		inline const valuetype& p2() const { return m_P2; }
		inline const valuetype& x1() const { return m_P1; }
		inline const valuetype& x2() const { return m_P2; }
		inline const valuetype& x() const { return m_P1; }
		inline const valuetype& w() const { return m_P2 - m_P1; }

		// Setters
		inline interval1D& p1(valuetype p1) { m_P1 = p1; return *this; }
		inline interval1D& p2(valuetype p2) { m_P2 = p2; return *this; }
		inline interval1D& x1(valuetype x1) { m_P1 = x1; return *this; }
		inline interval1D& x2(valuetype x2) { m_P2 = x2; return *this; }
		inline interval1D& x(valuetype x) { m_P1 = x; return *this; }
		inline interval1D& w(valuetype w) { m_P2 = m_P1 + w; return *this; }

		// Operators
		inline bool operator== (const interval1D& other) const { return (m_P1 == other.m_P1 && m_P2 == other.m_P2); }
		inline bool operator!= (const interval1D& other) const { return !(*this == other); }
		inline interval1D operator+ (valuetype other) const { return interval1D(m_P1 + other.m_P1, m_P2 + other.m_P2); }
		inline interval1D operator- (valuetype other) const { return interval1D(m_P1 - other.m_P1, m_P2 - other.m_P2); }
		inline interval1D operator* (valuetype scalar) const { return interval1D(m_P1 * scalar, m_P2 * scalar); }
		inline interval1D operator/ (valuetype scalar) const { return interval1D(m_P1 / scalar, m_P2 / scalar); }

		// Calculates the center of the interval
		inline valuetype center() const { return (m_P1 + m_P2) / 2; }

		// Calculates the extent of the interval
		inline valuetype extent() const { return (m_P2 - m_P1) / 2; }

		// Moves the interval to be centered around a point
		inline interval1D& center(valuetype center) { valuetype e = extent(); m_P1 = center - e; m_P2 = center + e; return *this; }

		// Resizes the interval to have a specified extent
		inline interval1D& extent(valuetype extent) { valuetype c = center(); m_P1 = c - extent; m_P2 = c + extent; return *this; }

		// Calculates the outcode of a point for the interval
		inline pointOutcode outcode(valuetype p) const
		{ 
			pointOutcode c = 0;
			if (p <= m_P1) { c |= 0x01; }
			if (p >= m_P2) { c |= 0x02; }
			return c;
		}

		// Calculates the interval that contains the sweeped version of the interval
		inline interval1D sweep(valuetype motion) const
		{
			return interval1D(
				(motion.x() < 0) ? m_P1 + motion.x() : m_P1,
				(motion.x() > 0) ? m_P2 + motion.x() : m_P2
				);
		}

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval1D GetTransformed(const transform1D& t1D) const { return interval1D(m_P1 * t1D.s() + t1D.t(), m_P2 * t1D.s() + t1D.t()); }
	};

	typedef interval1D<int> interval1Di;
	typedef interval1D<float> interval1Df;

	////////////////////////////////////////////////////////////////
	// 2D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct interval2D
	{

	private:

		vector2D<valuetype> m_P1, m_P2;

	public:

		// Constructors
		interval2D() { }
		interval2D(valuetype x1, valuetype x2, valuetype y1, valuetype y2) : m_P1(x1, y1), m_P2(x2, y2) { }
		interval2D(const vector2D<valuetype>& p1, const vector2D<valuetype>& p2) : m_P1(p1), m_P2(p2) { }
		interval2D(const interval1D<valuetype>& i) : m_P1(i.p1()), m_P2(i.p2()) { }

		// Casts
		inline operator interval1D<valuetype>() const { return interval1D<valuetype>(m_P1.x(), m_P2.x()); }

		// Getters
		inline vector2D<valuetype>& p1() { return m_P1; }
		inline vector2D<valuetype>& p2() { return m_P2; }
		inline valuetype& x1() { return m_P1.x(); }
		inline valuetype& x2() { return m_P2.x(); }
		inline valuetype& y1() { return m_P1.y(); }
		inline valuetype& y2() { return m_P2.y(); }
		inline valuetype& x() { return m_P1.x(); }
		inline valuetype& w() { return m_P2.x() - m_P1.x(); }
		inline valuetype& y() { return m_P1.y(); }
		inline valuetype& h() { return m_P2.y() - m_P1.y(); }

		inline const vector2D<valuetype>& p1() const { return m_P1; }
		inline const vector2D<valuetype>& p2() const { return m_P2; }
		inline const valuetype& x1() const { return m_P1.x(); }
		inline const valuetype& x2() const { return m_P2.x(); }
		inline const valuetype& y1() const { return m_P1.y(); }
		inline const valuetype& y2() const { return m_P2.y(); }
		inline const valuetype& x() const { return m_P1.x(); }
		inline const valuetype w() const { return m_P2.x() - m_P1.x(); }
		inline const valuetype& y() const { return m_P1.y(); }
		inline const valuetype h() const { return m_P2.y() - m_P1.y(); }

		// Setters
		inline interval2D& p1(const vector2D<valuetype>& p1) { m_P1 = p1; return *this; }
		inline interval2D& p2(const vector2D<valuetype>& p2) { m_P2 = p2; return *this; }
		inline interval2D& x1(valuetype x1) { m_P1.x(x1); return *this; }
		inline interval2D& x2(valuetype x2) { m_P2.x(x2); return *this; }
		inline interval2D& y1(valuetype y1) { m_P1.y(y1); return *this; }
		inline interval2D& y2(valuetype y2) { m_P2.y(y2); return *this; }
		inline interval2D& x(valuetype x) { m_P1.x(x); return *this; }
		inline interval2D& w(valuetype w) { m_P2.x(m_P1.x() + w); return *this; }
		inline interval2D& y(valuetype y) { m_P1.y(y); return *this; }
		inline interval2D& h(valuetype h) { m_P2.y(m_P1.y() + h); return *this; }

		// Operators
		inline bool operator== (const interval2D& other) const { return (m_P1 == other.m_P1 && m_P2 == other.m_P2); }
		inline bool operator!= (const interval2D& other) const { return !(*this == other); }
		inline interval2D operator+ (const interval2D& other) const { return interval2D(m_P1 + other.m_P1, m_P2 + other.m_P2); }
		inline interval2D operator- (const interval2D& other) const { return interval2D(m_P1 - other.m_P1, m_P2 - other.m_P2); }
		inline interval2D operator+ (const vector2D<valuetype>& other) const { return interval2D(m_P1 + other, m_P2 + other); }
		inline interval2D operator- (const vector2D<valuetype>& other) const { return interval2D(m_P1 - other, m_P2 - other); }
		inline interval2D operator* (valuetype scalar) const { return interval2D(m_P1 * scalar, m_P2 * scalar); }
		inline interval2D operator/ (valuetype scalar) const { return interval2D(m_P1 / scalar, m_P2 / scalar); }
		inline interval2D operator* (const vector2D<valuetype>& scale) const { return interval2D(m_P1.x() * scale.x(), m_P2.x() * scale.x(), m_P1.y() * scale.y(), m_P2.y() * scale.y()); }
		inline interval2D operator/ (const vector2D<valuetype>& scale) const { return interval2D(m_P1.x() / scale.x(), m_P2.x() / scale.x(), m_P1.y() / scale.y(), m_P2.y() / scale.y()); }

		// Calculates the center of the interval
		inline vector2D<valuetype> center() const { return (m_P1 + m_P2) / 2; }

		// Calculates the extent of the interval
		inline vector2D<valuetype> extent() const { return (m_P2 - m_P1) / 2; }

		// Moves the interval to be centered around a point
		inline interval2D& center(const vector2D<valuetype>& center) { vector2D<valuetype> e = extent(); m_P1 = center - e; m_P2 = center + e; return *this; }

		// Resizes the interval to have a specified extent
		inline interval2D& extent(const vector2D<valuetype>& extent) { vector2D<valuetype> c = center(); m_P1 = c - extent; m_P2 = c + extent; return *this; }

		// Calculates the outcode of a point for the interval
		inline pointOutcode outcode(const vector2D<valuetype>& p) const
		{
			pointOutcode c = 0;
			if (p.x() <= m_P1.x()) { c |= 0x01; }
			if (p.x() >= m_P2.x()) { c |= 0x02; }
			if (p.y() <= m_P1.y()) { c |= 0x04; }
			if (p.y() >= m_P2.y()) { c |= 0x08; }
			return c;
		}

		// Calculates the interval that contains the sweeped version of the interval
		inline interval2D sweep(const vector2D<valuetype>& motion) const
		{
			return interval2D(
				(motion.x() < 0) ? m_P1.x() + motion.x() : m_P1.x(),
				(motion.x() > 0) ? m_P2.x() + motion.x() : m_P2.x(),
				(motion.y() < 0) ? m_P1.y() + motion.y() : m_P1.y(),
				(motion.y() > 0) ? m_P2.y() + motion.y() : m_P2.y()
				);
		}

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval2D GetTransformed(const transform2D& t2D) const { return ((*this) * t2D.s()) + t2D.t(); }
	};

	typedef interval2D<int> interval2Di;
	typedef interval2D<float> interval2Df;

	////////////////////////////////////////////////////////////////
	// 3D intervals                                               //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct interval3D
	{

	private:

		vector3D<valuetype> m_P1, m_P2;

	public:

		// Constructors
		interval3D() { }
		interval3D(valuetype x1, valuetype x2, valuetype y1, valuetype y2, valuetype z1, valuetype z2) : m_P1(x1, y1, z1), m_P2(x2, y2, z2) { }
		interval3D(const vector3D<valuetype>& p1, const vector3D<valuetype>& p2) : m_P1(p1), m_P2(p2) { }
		interval3D(const interval1D<valuetype>& i) : m_P1(i.p1()), m_P2(i.p2()) { }
		interval3D(const interval2D<valuetype>& i) : m_P1(i.p1()), m_P2(i.p2()) { }

		// Casts
		inline operator interval2D<valuetype>() const { return interval2D<valuetype>(m_P1.xy(), m_P2.xy()); }
		inline operator interval1D<valuetype>() const { return interval1D<valuetype>(m_P1.x(), m_P2.x()); }

		// Getters
		inline vector3D<valuetype>& p1() { return m_P1; }
		inline vector3D<valuetype>& p2() { return m_P2; }
		inline valuetype& x1() { return m_P1.x(); }
		inline valuetype& x2() { return m_P2.x(); }
		inline valuetype& y1() { return m_P1.y(); }
		inline valuetype& y2() { return m_P2.y(); }
		inline valuetype& z1() { return m_P1.z(); }
		inline valuetype& z2() { return m_P2.z(); }
		inline valuetype& x() { return m_P1.x(); }
		inline valuetype& w() { return m_P2.x() - m_P1.x(); }
		inline valuetype& y() { return m_P1.y(); }
		inline valuetype& h() { return m_P2.y() - m_P1.y(); }
		inline valuetype& z() { return m_P1.z(); }
		inline valuetype& d() { return m_P2.z() - m_P1.z(); }
		inline const vector3D<valuetype>& p1() const { return m_P1; }
		inline const vector3D<valuetype>& p2() const { return m_P2; }
		inline const valuetype& x1() const { return m_P1.x(); }
		inline const valuetype& x2() const { return m_P2.x(); }
		inline const valuetype& y1() const { return m_P1.y(); }
		inline const valuetype& y2() const { return m_P2.y(); }
		inline const valuetype& z1() const { return m_P1.z(); }
		inline const valuetype& z2() const { return m_P2.z(); }
		inline const valuetype& x() const { return m_P1.x(); }
		inline const valuetype& w() const { return m_P2.x() - m_P1.x(); }
		inline const valuetype& y() const { return m_P1.y(); }
		inline const valuetype h() const { return m_P2.y() - m_P1.y(); }
		inline const valuetype& z() const { return m_P1.z(); }
		inline const valuetype d() const { return m_P2.z() - m_P1.z(); }

		// Setters
		inline interval3D& p1(const vector3D<valuetype>& p1) { m_P1 = p1; return *this; }
		inline interval3D& p2(const vector3D<valuetype>& p2) { m_P2 = p2; return *this; }
		inline interval3D& x1(valuetype x1) { m_P1.x(x1); return *this; }
		inline interval3D& x2(valuetype x2) { m_P2.x(x2); return *this; }
		inline interval3D& y1(valuetype y1) { m_P1.y(y1); return *this; }
		inline interval3D& y2(valuetype y2) { m_P2.y(y2); return *this; }
		inline interval3D& z1(valuetype z1) { m_P1.z(z1); return *this; }
		inline interval3D& z2(valuetype z2) { m_P2.z(z2); return *this; }
		inline interval3D& x(valuetype x) { m_P1.x(x); return *this; }
		inline interval3D& w(valuetype w) { m_P2.x(m_P1.x() + w); return *this; }
		inline interval3D& y(valuetype y) { m_P1.y(y); return *this; }
		inline interval3D& h(valuetype h) { m_P2.y(m_P1.y() + h); return *this; }
		inline interval3D& z(valuetype z) { m_P1.z(z); return *this; }
		inline interval3D& d(valuetype d) { m_P2.z(m_P1.z() + d); return *this; }

		// Operators
		inline bool operator== (const interval3D& other) const { return (m_P1 == other.m_P1 && m_P2 == other.m_P2); }
		inline bool operator!= (const interval3D& other) const { return !(*this == other); }
		inline interval3D operator+ (const interval3D& other) const { return interval3D(m_P1 + other.m_P1, m_P2 + other.m_P2); }
		inline interval3D operator- (const interval3D& other) const { return interval3D(m_P1 - other.m_P1, m_P2 - other.m_P2); }
		inline interval3D operator+ (const vector3D<valuetype>& other) const { return interval3D(m_P1 + other, m_P2 + other); }
		inline interval3D operator- (const vector3D<valuetype>& other) const { return interval3D(m_P1 - other, m_P2 - other); }
		inline interval3D operator* (valuetype scalar) const { return interval3D(m_P1 * scalar, m_P2 * scalar); }
		inline interval3D operator/ (valuetype scalar) const { return interval3D(m_P1 / scalar, m_P2 / scalar); }
		inline interval3D operator* (const vector3D<valuetype>& scale) const { return interval3D(m_P1.x() * scale.x(), m_P2.x() * scale.x(), m_P1.y() * scale.y(), m_P2.y() * scale.y(), m_P1.z() * scale.z(), m_P2.z() * scale.z()); }
		inline interval3D operator/ (const vector3D<valuetype>& scale) const { return interval3D(m_P1.x() / scale.x(), m_P2.x() / scale.x(), m_P1.y() / scale.y(), m_P2.y() / scale.y(), m_P1.z() / scale.z(), m_P2.z() / scale.z()); }

		// Calculates the center of the interval
		inline vector3D<valuetype> center() const { return (m_P1 + m_P2) / 2; }

		// Calculates the extent of the interval
		inline vector3D<valuetype> extent() const { return (m_P2 - m_P1) / 2; }

		// Moves the interval to be centered around a point
		inline interval3D& center(const vector3D<valuetype>& center) { vector3D<valuetype> e = extent(); m_P1 = center - e; m_P2 = center + e; return *this; }

		// Resizes the interval to have a specified extent
		inline interval3D& extent(const vector3D<valuetype>& extent) { vector3D<valuetype> c = center(); m_P1 = c - extent; m_P2 = c + extent; return *this; }

		// Calculates the outcode of a point for the interval
		inline pointOutcode outcode(const vector2D<valuetype>& p) const
		{
			pointOutcode c = 0;
			if (p.x() <= m_P1.x()) { c |= 0x01; }
			if (p.x() >= m_P2.x()) { c |= 0x02; }
			if (p.y() <= m_P1.y()) { c |= 0x04; }
			if (p.y() >= m_P2.y()) { c |= 0x08; }
			if (p.z() <= m_P1.z()) { c |= 0x10; }
			if (p.z() >= m_P2.z()) { c |= 0x20; }
			return c;
		}

		// Calculates the interval that contains the sweeped version of the interval
		inline interval3D sweep(const vector3D<valuetype>& motion) const
		{
			return interval3D(
				(motion.x() < 0) ? m_P1.x() + motion.x() : m_P1.x(),
				(motion.x() > 0) ? m_P2.x() + motion.x() : m_P2.x(),
				(motion.y() < 0) ? m_P1.y() + motion.y() : m_P1.y(),
				(motion.y() > 0) ? m_P2.y() + motion.y() : m_P2.y(),
				(motion.z() < 0) ? m_P1.z() + motion.z() : m_P1.z(),
				(motion.z() > 0) ? m_P2.z() + motion.z() : m_P2.z()
				);
		}

		// Calculates a transformed version of the interval (translation and scaling only, no rotation)
		inline interval3D GetTransformed(const transform3D& t3D) const { return ((*this) * t3D.s()) + t3D.t(); }
	};

	typedef interval3D<int> interval3Di;
	typedef interval3D<float> interval3Df;
}

#endif
