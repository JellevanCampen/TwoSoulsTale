#ifndef ENGINE_COMMON_UTILITY_TRANSFORMTYPES_H
#define ENGINE_COMMON_UTILITY_TRANSFORMTYPES_H

#include "glm.hpp" // As base type for representing matrices
#include "glm\gtc\matrix_transform.hpp" // For calculating the transformation matrix

#include "VectorTypes.hpp" // For representing vectors
#include "MatrixTypes.hpp" // For representing the transformation matrix

#include "Box2D.h" // For constructing transforms from Box2D transforms

namespace Engine
{
	////////////////////////////////////////////////////////////////
	// 1D transforms                                              //
	////////////////////////////////////////////////////////////////

	struct transform1D
	{

	private:

		float m_T;
		float m_S;

		mat4f m_Matrix;
		bool m_Dirty;

	public:

		// Constructors
		transform1D(float t = 0.0f, float s = 1.0f) : m_T(t), m_S(s), m_Dirty(true) { }

		// Getters
		inline float& t() { m_Dirty = true; return m_T; }
		inline float& s() { m_Dirty = true; return m_S; }
		inline const float& t() const { return m_T; }
		inline const float& s() const { return m_S; }

		// Setters
		inline transform1D& t(float t) { m_T = t; m_Dirty = true; return *this; }
		inline transform1D& s(float s) { m_S = s; m_Dirty = true; return *this; }

		// Gets the transformation matrix for this transform
		const mat4f& GetTransformationMatrix()
		{
			if (!m_Dirty) { return m_Matrix; }

			m_Matrix.SetIdentity();
			if (m_T != 0.0f) { m_Matrix = glm::translate<float, glm::precision::defaultp>(m_Matrix, f3(m_T, 0.0f, 0.0f)); }
			if (m_S != 1.0f) { m_Matrix = glm::scale<float, glm::precision::defaultp>(m_Matrix, f3(m_S, 1.0f, 1.0f)); }

			return m_Matrix;
		}
	};

	typedef transform1D tf1D;

	////////////////////////////////////////////////////////////////
	// 2D transforms                                              //
	////////////////////////////////////////////////////////////////

	struct transform2D
	{

	private:

		f2 m_T;
		float m_R;
		f2 m_S;

		mat4f m_Matrix;
		bool m_Dirty;

	public:

		// Constructors
		transform2D(f2 t = f2(0.0f, 0.0f), float r = 0.0f, f2 s = f2(1.0f, 1.0f)) : m_T(t), m_R(r), m_S(s), m_Dirty(true) { }
		transform2D(float tX, float tY, float r = 0.0f, float sX = 1.0f, float sY = 1.0f) : m_T(tX, tY), m_R(r), m_S(sX, sY), m_Dirty(true) { }
		transform2D(const transform1D& t1D) : m_T(f2(t1D.t(), 0.0f)), m_R(0.0f), m_S(f2(t1D.s(), 1.0f)), m_Dirty(true) { }
		transform2D(const b2Transform& tf) : m_T(f2(tf.p.x, tf.p.y)), m_R(tf.q.GetAngle()), m_S(f2(1.0f, 1.0f)) { }

		// Casts
		inline operator transform1D() const { transform1D t1D; t1D.t(m_T.x()); t1D.s(m_S.x()); return t1D; }

		// Getters
		inline f2& t() { m_Dirty = true; return m_T; }
		inline float& r() { m_Dirty = true; return m_R; }
		inline f2& s() { m_Dirty = true; return m_S; }
		inline const f2& t() const { return m_T; }
		inline const float& r() const { return m_R; }
		inline const f2& s() const { return m_S; }

		// Setters
		inline transform2D& t(f2 t) { m_T = t; m_Dirty = true; return *this; }
		inline transform2D& t(float tX, float tY) { m_T.x(tX); m_T.y(tY); m_Dirty = true; return *this; }
		inline transform2D& r(float r) { m_R = r; m_Dirty = true; return *this; }
		inline transform2D& s(f2 s) { m_S = s; m_Dirty = true; return *this; }
		inline transform2D& s(float sX, float sY) { m_S.x(sX); m_S.y(sY); m_Dirty = true; return *this; }
		
		// Gets the transformation matrix for this transform
		const mat4f& GetTransformationMatrix()
		{
			if (!m_Dirty) { return m_Matrix; }

			m_Matrix.SetIdentity();
			if (m_T != f2(0.0f, 0.0f)) { m_Matrix = glm::translate<float, glm::precision::defaultp>(m_Matrix, f3(m_T, 0.0f)); }
			if (m_R != 0.0f) { m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R, glm::vec3(0.0f, 0.0f, 1.0f));	}
			if (m_S != f2(1.0f, 1.0f)) { m_Matrix = glm::scale<float, glm::precision::defaultp>(m_Matrix, f3(m_S, 1.0f)); }

			return m_Matrix;
		}
	};

	typedef transform2D tf2D;

	////////////////////////////////////////////////////////////////
	// 3D transforms                                              //
	////////////////////////////////////////////////////////////////

	struct transform3D
	{

	private:

		f3 m_T;
		f3 m_R;
		f3 m_S;

		// Struct for representing the order of rotations
		enum class RotationOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX };
		RotationOrder m_RotationOrder;

		mat4f m_Matrix;
		bool m_Dirty;

	public:

		// Constructors
		transform3D(f3 t = f3(0.0f, 0.0f, 0.0f), f3 r = f3(0.0f, 0.0f, 0.0f), f3 s = f3(1.0f, 1.0f, 1.0f), RotationOrder rotationOrder = RotationOrder::ZXY) : m_T(t), m_R(r), m_S(s), m_RotationOrder(rotationOrder), m_Dirty(true) { }
		transform3D(
			float tX, float tY, float tZ, 
			float rX = 0.0f, float rY = 0.0f, float rZ = 0.0f, 
			float sX = 1.0f, float sY = 1.0f, float sZ = 1.0f,
			RotationOrder rotationOrder = RotationOrder::ZXY)
			: m_T(tX, tY, tZ), m_R(rX, rY, rZ), m_S(sX, sY, sZ)
			, m_RotationOrder(rotationOrder), m_Dirty(true) { }
		transform3D(const transform2D& t2D) : m_T(f3(t2D.t(), 0.0f)), m_R(f3(0.0f, 0.0f, t2D.r())), m_S(f3(t2D.s(), 1.0f)), m_RotationOrder(RotationOrder::ZXY), m_Dirty(true) { }

		// Casts
		inline operator transform2D() const { transform2D t2D; t2D.t(m_T.xy()); t2D.r(m_R.z()); t2D.s(m_S.xy()); return t2D; }
		inline operator transform1D() const { transform1D t1D; t1D.t(m_T.x()); t1D.s(m_S.x()); return t1D; }

		// Getters
		inline f3& t() { m_Dirty = true; return m_T; }
		inline f3& r() { m_Dirty = true; return m_R; }
		inline f3& s() { m_Dirty = true; return m_S; }
		inline const f3& t() const { return m_T; }
		inline const f3& r() const { return m_R; }
		inline const f3& s() const { return m_S; }

		// Setters
		inline transform3D& t(f3 t) { m_T = t; m_Dirty = true; return *this; }
		inline transform3D& t(float tX, float tY, float tZ) { m_T.x(tX); m_T.y(tY); m_T.z(tZ); m_Dirty = true; return *this; }
		inline transform3D& r(f3 r) { m_R = r; m_Dirty = true; return *this; }
		inline transform3D& r(float rX, float rY, float rZ) { m_R.x(rX); m_R.y(rY); m_R.z(rZ); m_Dirty = true; return *this; }
		inline transform3D& s(f3 s) { m_S = s; m_Dirty = true; return *this; }
		inline transform3D& s(float sX, float sY, float sZ) { m_S.x(sX); m_S.y(sY); m_S.z(sZ); m_Dirty = true; return *this; }

		// Gets the transformation matrix for this transform
		const mat4f& GetTransformationMatrix()
		{
			if (!m_Dirty) {	return m_Matrix; }

			m_Matrix.SetIdentity();
			if (m_T != f3(0.0f, 0.0f, 0.0f)) { m_Matrix = glm::translate<float, glm::precision::defaultp>(m_Matrix, m_T); }
			if (m_R != f3(0.0f, 0.0f, 0.0f))
			{
				switch (m_RotationOrder)
				{
				case RotationOrder::XYZ:
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.z(), glm::vec3(0.0f, 0.0f, 1.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.y(), glm::vec3(0.0f, 1.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.x(), glm::vec3(1.0f, 0.0f, 0.0f));
					break;
				case RotationOrder::XZY:
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.y(), glm::vec3(0.0f, 1.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.z(), glm::vec3(0.0f, 0.0f, 1.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.x(), glm::vec3(1.0f, 0.0f, 0.0f));
					break;
				case RotationOrder::YXZ:
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.z(), glm::vec3(0.0f, 0.0f, 1.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.x(), glm::vec3(1.0f, 0.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.y(), glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				case RotationOrder::YZX:
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.x(), glm::vec3(1.0f, 0.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.z(), glm::vec3(0.0f, 0.0f, 1.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.y(), glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				case RotationOrder::ZXY:
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.y(), glm::vec3(0.0f, 1.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.x(), glm::vec3(1.0f, 0.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.z(), glm::vec3(0.0f, 0.0f, 1.0f));
					break;
				case RotationOrder::ZYX:
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.x(), glm::vec3(1.0f, 0.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.y(), glm::vec3(0.0f, 1.0f, 0.0f));
					m_Matrix = glm::rotate<float, glm::precision::defaultp>(m_Matrix, m_R.z(), glm::vec3(0.0f, 0.0f, 1.0f));
					break;
				}
			}
			if (m_S != f3(1.0f, 1.0f, 1.0f)) { m_Matrix = glm::scale<float, glm::precision::defaultp>(m_Matrix, m_S); }

			return m_Matrix;
		}
	};

	typedef transform3D tf3D;
}

#endif
