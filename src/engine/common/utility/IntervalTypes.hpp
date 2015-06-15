#ifndef ENGINE_COMMON_UTILITY_INTERVALTYPES_H
#define ENGINE_COMMON_UTILITY_INTERVALTYPES_H

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
		interval1D(basetype x1, basetype x2) : m_X1(x1), m_X2(x2) { };
		interval1D() : interval1D(0, 0) { };

		// Getters
		inline basetype x1() const { return m_X1; };
		inline basetype x2() const { return m_X2; };

		inline basetype x() const { return m_X1; };
		inline basetype w() const { return m_X2 - m_X1; };

		// Setters
		inline void x1(basetype x1) const { m_X1 = x1; };
		inline void x2(basetype x2) const { m_X2 = x2; };

		inline void x(basetype x) const { m_X1 = x; };
		inline void w(basetype w) const { m_X2 = m_X1 + w; };

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x) const { return (x >= m_X1 && x <= m_X2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x) const { return (x > m_X1 && x < m_X2); }
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
		interval2D(basetype x1, basetype x2, basetype y1, basetype y2) : m_X1(x1), m_X2(x2), m_Y1(y1), m_Y2(y2) { };
		interval2D() : interval2D(0, 0, 0, 0) { };

		// Getters
		inline basetype x1() const { return m_X1; };
		inline basetype x2() const { return m_X2; };
		inline basetype y1() const { return m_Y1; };
		inline basetype y2() const { return m_Y2; };

		inline basetype x() const { return m_X1; };
		inline basetype w() const { return m_X2 - m_X1; };
		inline basetype y() const { return m_Y1; };
		inline basetype h() const { return m_Y2 - m_Y1; };

		// Setters
		inline void x1(basetype x1) const { m_X1 = x1; };
		inline void x2(basetype x2) const { m_X2 = x2; };
		inline void y1(basetype y1) const { m_Y1 = y1; };
		inline void y2(basetype y2) const { m_Y2 = y2; };

		inline void x(basetype x) const { m_X1 = x; };
		inline void w(basetype w) const { m_X2 = m_X1 + w; };
		inline void y(basetype y) const { m_Y1 = y; };
		inline void h(basetype h) const { m_Y2 = m_Y1 + h; };

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x, basetype y) const { return (x >= m_X1 && x <= m_X2 && y >= m_Y1 && y <= m_Y2); }
		inline bool Contains(f2 p) const { return (p.x() >= m_X1 && p.x() <= m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2); }
		inline bool Contains(i2 p) const { return (p.x() >= m_X1 && p.x() <= m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x, basetype y) const { return (x > m_X1 && x < m_X2 && y >= m_Y1 && y <= m_Y2); }
		inline bool ContainsStrict(f2 p) const { return (p.x() > m_X1 && p.x() < m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2); }
		inline bool ContainsStrict(i2 p) const { return (p.x() > m_X1 && p.x() < m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2); }
	};

	typedef interval2D<int> interval2Di, aabb2Di, rectanglei;
	typedef interval2D<float> interval2Df, aabb2Df, rectanglef;

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
		interval3D(basetype x1, basetype x2, basetype y1, basetype y2, basetype z1, basetype z2) : m_X1(x1), m_X2(x2), m_Y1(y1), m_Y2(y2), m_Z1(z1), m_Z2(z2) { };
		interval3D() : interval3D(0, 0, 0, 0, 0, 0) { };

		// Getters
		inline basetype x1() const { return m_X1; };
		inline basetype x2() const { return m_X2; };
		inline basetype y1() const { return m_Y1; };
		inline basetype y2() const { return m_Y2; };
		inline basetype z1() const { return m_Z1; };
		inline basetype z2() const { return m_Z2; };

		inline basetype x() const { return m_X1; };
		inline basetype w() const { return m_X2 - m_X1; };
		inline basetype y() const { return m_Y1; };
		inline basetype h() const { return m_Y2 - m_Y1; };
		inline basetype z() const { return m_Z1; };
		inline basetype d() const { return m_Z2 - m_Z1; };

		// Setters
		inline void x1(basetype x1) const { m_X1 = x1; };
		inline void x2(basetype x2) const { m_X2 = x2; };
		inline void y1(basetype y1) const { m_Y1 = y1; };
		inline void y2(basetype y2) const { m_Y2 = y2; };
		inline void z1(basetype z1) const { m_Z1 = z1; };
		inline void z2(basetype z2) const { m_Z2 = z2; };

		inline void x(basetype x) const { m_X1 = x; };
		inline void w(basetype w) const { m_X2 = m_X1 + w; };
		inline void y(basetype y) const { m_Y1 = y; };
		inline void h(basetype h) const { m_Y2 = m_Y1 + h; };
		inline void z(basetype z) const { m_Z1 = z; };
		inline void d(basetype d) const { m_Z2 = m_Z1 + d; };

		// Checks whether the specified point is contained in the interval (boundaries included)
		inline bool Contains(basetype x, basetype y, basetype z) const { return (x >= m_X1 && x <= m_X2 && y >= m_Y1 && y <= m_Y2 && z >= m_Z1 && z <= m_Z2); }
		inline bool Contains(f3 p) const { return (p.x() >= m_X1 && p.x() <= m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2 && p.z() >= m_Z1 && p.z() <= m_Z2); }
		inline bool Contains(i3 p) const { return (p.x() >= m_X1 && p.x() <= m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2 && p.z() >= m_Z1 && p.z() <= m_Z2); }

		// Checks whether the specified point is strictly contained in the interval (boundaries not included)
		inline bool ContainsStrict(basetype x, basetype y, basetype z) const { return (x > m_X1 && x < m_X2 && y >= m_Y1 && y <= m_Y2 && z >= m_Z1 && z <= m_Z2); }
		inline bool ContainsStrict(f3 p) const { return (p.x() > m_X1 && p.x() < m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2 && p.z() >= m_Z1 && p.z() <= m_Z2); }
		inline bool ContainsStrict(i3 p) const { return (p.x() > m_X1 && p.x() < m_X2 && p.y() >= m_Y1 && p.y() <= m_Y2 && p.z() >= m_Z1 && p.z() <= m_Z2); }
	};

	typedef interval3D<int> interval3Di, aabb3Di, boxi;
	typedef interval3D<float> interval3Df, aabb3Df, boxf;
}

#endif
