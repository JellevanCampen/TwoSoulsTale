#ifndef ENGINE_COMMON_UTILITY_VECTORTYPES_H
#define ENGINE_COMMON_UTILITY_VECTORTYPES_H

#include "glm.hpp" // As base type for representing vectors

namespace Engine
{
	////////////////////////////////////////////////////////////////
	// 2D vectors                                                 //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct vector2D
	{

	private:

		valuetype m_X, m_Y;

	public:

		// Constructors
		vector2D() : m_X(0), m_Y(0) { }
		vector2D(valuetype v) : m_X(v), m_Y(v) { }
		vector2D(valuetype x, valuetype y) : m_X(x), m_Y(y) { }
		vector2D(const glm::vec2& v) : m_X(v.x), m_Y(v.y) { }

		// Casts
		inline operator glm::vec2 const&() { return glm::vec2(m_X, m_Y); }

		// Getters
		inline valuetype x() const { return m_X; }
		inline valuetype y() const { return m_Y; }

		// Setters
		inline void x(valuetype x) { m_X = x; };
		inline void y(valuetype y) { m_Y = y; };

		// Operators
		inline bool operator== (const vector2D& other) const { return (m_X == other.m_X && m_Y == other.m_Y); }
		inline bool operator!= (const vector2D& other) const { return !(*this == other); }
		inline vector2D operator+ (const vector2D& other) const { return vector2D(m_X + other.m_X, m_Y + other.m_Y); }
		inline vector2D operator- (const vector2D& other) const { return vector2D(m_X - other.m_X, m_Y - other.m_Y); }
		inline vector2D operator* (float scalar) const { return vector2D(m_X * scalar, m_Y * scalar); }
		inline vector2D operator/ (float scalar) const { return vector2D(m_X / scalar, m_Y / scalar); }
		inline valuetype& operator[] (size_t index)
		{
			switch (index)
			{
			case 0: return m_X;
			case 1: return m_Y;
			default: return 0;
			}
		}
		inline const valuetype& operator[] (size_t index) const
		{
			switch (index)
			{
			case 0: return m_X;
			case 1: return m_Y;
			default: return 0;
			}
		}
		
		// Swizzle operators
		inline vector2D xy() const { return vector2D(m_X, m_Y); }
		inline vector2D yx() const { return vector2D(m_Y, m_X); }

		// Makes all vector components zero
		inline void Zero() { m_X = 0; m_Y = 0; }									

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline float Length() const { return sqrtf((m_X * m_X) + (m_Y * m_Y)); }

		// Normalizes the vector (to have Euclidean unit length)
		inline vector2D& Normalize() { float l = Length(); m_X /= l; m_Y /= l; return *this; }

		// Calculates the Euclidean distance between this vector and another vector
		inline float GetDistanceTo(vector2D point) const { return (*this - point).Length(); }
	};

	typedef vector2D<int> vector2Di, int2, i2;
	typedef vector2D<float> vector2Df, float2, f2;

	////////////////////////////////////////////////////////////////
	// 3D vectors                                                 //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct vector3D
	{

	private:

		valuetype m_X, m_Y, m_Z;

	public:

		// Constructors
		vector3D() : m_X(0), m_Y(0), m_Z(0) { }
		vector3D(valuetype v) : m_X(v), m_Y(v), m_Z(v) { }
		vector3D(vector2D<valuetype> v, valuetype z) : m_X(v.x()), m_Y(v.y()), m_Z(z) { }
		vector3D(valuetype x, valuetype y, valuetype z) : m_X(x), m_Y(y), m_Z(z) { }
		vector3D(const glm::vec3& v) : m_X(v.x), m_Y(v.y), m_Z(v.z) { }
		
		// Casts
		inline operator glm::vec3 const&() { return glm::vec3(m_X, m_Y, m_Z); }

		// Getters
		inline valuetype x() const { return m_X; }
		inline valuetype y() const { return m_Y; }
		inline valuetype z() const { return m_Z; }

		// Setters
		inline void x(valuetype x) { m_X = x; };
		inline void y(valuetype y) { m_Y = y; };
		inline void z(valuetype z) { m_Z = z; };
		
		// Operators
		inline bool operator== (const vector3D& other) const { return (m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z); }
		inline bool operator!= (const vector3D& other) const { return !(*this == other); }
		inline vector3D operator+ (const vector3D& other) const { return vector3D(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z); }
		inline vector3D operator- (const vector3D& other) const { return vector3D(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z); }
		inline vector3D operator* (float scalar) const { return vector3D(m_X * scalar, m_Y * scalar, m_Z * scalar); }
		inline vector3D operator/ (float scalar) const { return vector3D(m_X / scalar, m_Y / scalar, m_Z / scalar); }
		inline valuetype& operator[] (size_t index)
		{
			switch (index)
			{
			case 0: return m_X;
			case 1: return m_Y;
			case 2:	return m_Z;
			default: return 0;
			}
		}
		inline const valuetype& operator[] (size_t index) const
		{
			switch (index)
			{
			case 0: return m_X;
			case 1: return m_Y;
			case 2:	return m_Z;
			default: return 0;
			}
		}
		
		// Swizzle operators
		inline vector2D<valuetype> xy() const { return vector2D<valuetype>(m_X, m_Y); }
		inline vector2D<valuetype> xz() const { return vector2D<valuetype>(m_X, m_Z); }
		inline vector2D<valuetype> yz() const { return vector2D<valuetype>(m_Y, m_Z); }
		inline vector2D<valuetype> yx() const { return vector2D<valuetype>(m_Y, m_X); }
		inline vector2D<valuetype> zx() const { return vector2D<valuetype>(m_Z, m_X); }
		inline vector2D<valuetype> zy() const { return vector2D<valuetype>(m_Z, m_Y); }

		inline vector3D xyz() const { return vector3D(m_X, m_Y, m_Z); }
		inline vector3D xzy() const { return vector3D(m_X, m_Z, m_Y); }
		inline vector3D yxz() const { return vector3D(m_Y, m_X, m_Z); }
		inline vector3D yzx() const { return vector3D(m_Y, m_Z, m_X); }
		inline vector3D zxy() const { return vector3D(m_Z, m_X, m_Y); }
		inline vector3D zyx() const { return vector3D(m_Z, m_Y, m_X); }

		// Makes all vector components zero
		inline void Zero() { m_X = 0; m_Y = 0; m_Z = 0; }								

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline float Length() const { return sqrtf((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z)); }

		// Normalizes the vector (to have Euclidean unit length)
		inline vector3D& Normalize() { float l = Length(); m_X /= l; m_Y /= l; m_Z /= l; return *this; }

		// Calculates the Euclidean distance between this vector and another vector
		inline float GetDistanceTo(vector3D point) const { return (*this - point).Length(); }

		// Calculates the cross product of this vector with another vector
		inline vector3D CrossProduct(const vector3D& other) const { return vector3D(m_Y * other.m_Z - m_Z * other.m_Y, m_Z * other.m_X - m_X * other.m_Z, m_X * other.m_Y - m_Y * other.m_X); }
	};

	typedef vector3D<int> vector3Di, int3, i3;
	typedef vector3D<float> vector3Df, float3, f3;

	////////////////////////////////////////////////////////////////
	// 4D vectors                                                 //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct vector4D
	{

	private:

		valuetype m_X, m_Y, m_Z, m_W;

	public:

		// Constructors
		vector4D() : m_X(0), m_Y(0), m_Z(0), m_W(0) { }
		vector4D(valuetype v) : m_X(v), m_Y(v), m_Z(v), m_W(v) { }
		vector4D(vector3D<valuetype> v, valuetype w) : m_X(v.x()), m_Y(v.y()), m_Z(v.z), m_W(w) { }
		vector4D(valuetype x, valuetype y, valuetype z, valuetype w) : m_X(x), m_Y(y), m_Z(z), m_W(w) { }
		vector4D(const glm::vec4& v) : m_X(v.x), m_Y(v.y), m_Z(v.z), m_W(v.w) { }
		
		// Casts
		inline operator glm::vec4 const&() { return glm::vec4(m_X, m_Y, m_Z, m_W); }

		// Getters
		inline valuetype x() const { return m_X; }
		inline valuetype y() const { return m_Y; }
		inline valuetype z() const { return m_Z; }
		inline valuetype w() const { return m_W; }

		// Setters
		inline void x(valuetype x) { m_X = x; };
		inline void y(valuetype y) { m_Y = y; };
		inline void z(valuetype z) { m_Z = z; };
		inline void w(valuetype w) { m_W = w; };
		
		// Operators
		inline bool operator== (const vector4D& other) const { return (m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z && m_W == other.m_W); }
		inline bool operator!= (const vector4D& other) const { return !(*this == other); }
		inline vector4D operator+ (const vector4D& other) const { return vector4D(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z, m_W + other.m_W); }
		inline vector4D operator- (const vector4D& other) const { return vector4D(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z, m_W - other.m_W); }
		inline vector4D operator* (float scalar) const { return vector4D(m_X * scalar, m_Y * scalar, m_Z * scalar, m_W * scalar); }
		inline vector4D operator/ (float scalar) const { return vector4D(m_X / scalar, m_Y / scalar, m_Z / scalar, m_W * scalar); }
		inline valuetype& operator[] (size_t index)
		{
			switch (index)
			{
			case 0:	return m_X;
			case 1:	return m_Y;
			case 2:	return m_Z;
			case 3:	return m_W;
			default: return m_W;
			}
		}
		inline const valuetype& operator[] (size_t index) const
		{
			switch (index)
			{
			case 0:	return m_X;
			case 1:	return m_Y;
			case 2:	return m_Z;
			case 3:	return m_W;
			default: return m_W;
			}
		}

		// Swizzle operators
		inline vector2D<valuetype> xy() const { return vector2D<valuetype>(m_X, m_Y); }
		inline vector2D<valuetype> xz() const { return vector2D<valuetype>(m_X, m_Z); }
		inline vector2D<valuetype> xw() const { return vector2D<valuetype>(m_X, m_W); }
		inline vector2D<valuetype> yx() const { return vector2D<valuetype>(m_Y, m_X); }
		inline vector2D<valuetype> yz() const { return vector2D<valuetype>(m_Y, m_Z); }
		inline vector2D<valuetype> yw() const { return vector2D<valuetype>(m_Y, m_W); }
		inline vector2D<valuetype> zx() const { return vector2D<valuetype>(m_Z, m_X); }
		inline vector2D<valuetype> zy() const { return vector2D<valuetype>(m_Z, m_Y); }
		inline vector2D<valuetype> zw() const { return vector2D<valuetype>(m_Z, m_W); }
		inline vector2D<valuetype> wx() const { return vector2D<valuetype>(m_W, m_X); }
		inline vector2D<valuetype> wy() const { return vector2D<valuetype>(m_W, m_Y); }
		inline vector2D<valuetype> wz() const { return vector2D<valuetype>(m_W, m_Z); }

		inline vector3D<valuetype> xyz() const { return vector3D<valuetype>(m_X, m_Y, m_Z); }
		inline vector3D<valuetype> xyw() const { return vector3D<valuetype>(m_X, m_Y, m_W); }
		inline vector3D<valuetype> xzy() const { return vector3D<valuetype>(m_X, m_Z, m_Y); }
		inline vector3D<valuetype> xzw() const { return vector3D<valuetype>(m_X, m_Z, m_W); }
		inline vector3D<valuetype> xwy() const { return vector3D<valuetype>(m_X, m_W, m_Y); }
		inline vector3D<valuetype> xwz() const { return vector3D<valuetype>(m_X, m_W, m_Z); }

		inline vector3D<valuetype> yxz() const { return vector3D<valuetype>(m_Y, m_X, m_Z); }
		inline vector3D<valuetype> yxw() const { return vector3D<valuetype>(m_Y, m_X, m_W); }
		inline vector3D<valuetype> yzx() const { return vector3D<valuetype>(m_Y, m_Z, m_X); }
		inline vector3D<valuetype> yzw() const { return vector3D<valuetype>(m_Y, m_Z, m_W); }
		inline vector3D<valuetype> ywx() const { return vector3D<valuetype>(m_Y, m_W, m_X); }
		inline vector3D<valuetype> ywz() const { return vector3D<valuetype>(m_Y, m_W, m_Z); }

		inline vector3D<valuetype> zxy() const { return vector3D<valuetype>(m_Z, m_X, m_Y); }
		inline vector3D<valuetype> zxw() const { return vector3D<valuetype>(m_Z, m_X, m_W); }
		inline vector3D<valuetype> zyx() const { return vector3D<valuetype>(m_Z, m_Y, m_X); }
		inline vector3D<valuetype> zyw() const { return vector3D<valuetype>(m_Z, m_Y, m_W); }
		inline vector3D<valuetype> zwx() const { return vector3D<valuetype>(m_Z, m_W, m_X); }
		inline vector3D<valuetype> zwy() const { return vector3D<valuetype>(m_Z, m_W, m_Y); }

		inline vector3D<valuetype> wxy() const { return vector3D<valuetype>(m_W, m_X, m_Y); }
		inline vector3D<valuetype> wxz() const { return vector3D<valuetype>(m_W, m_X, m_Z); }
		inline vector3D<valuetype> wyx() const { return vector3D<valuetype>(m_W, m_Y, m_X); }
		inline vector3D<valuetype> wyz() const { return vector3D<valuetype>(m_W, m_Y, m_Z); }
		inline vector3D<valuetype> wzx() const { return vector3D<valuetype>(m_W, m_Z, m_X); }
		inline vector3D<valuetype> wzy() const { return vector3D<valuetype>(m_W, m_Z, m_Y); }

		inline vector4D xyzw() const { return vector4D(m_X, m_Y, m_Z, m_W); }
		inline vector4D xywz() const { return vector4D(m_X, m_Y, m_W, m_Z); }
		inline vector4D xzyw() const { return vector4D(m_X, m_Z, m_Y, m_W); }
		inline vector4D xzwy() const { return vector4D(m_X, m_Z, m_W, m_Y); }
		inline vector4D xwyz() const { return vector4D(m_X, m_W, m_Y, m_Z); }
		inline vector4D xwzy() const { return vector4D(m_X, m_W, m_Z, m_Y); }

		inline vector4D yxzw() const { return vector4D(m_Y, m_X, m_Z, m_W); }
		inline vector4D yxwz() const { return vector4D(m_Y, m_X, m_W, m_Z); }
		inline vector4D yzxw() const { return vector4D(m_Y, m_Z, m_X, m_W); }
		inline vector4D yzwx() const { return vector4D(m_Y, m_Z, m_W, m_X); }
		inline vector4D ywxz() const { return vector4D(m_Y, m_W, m_X, m_Z); }
		inline vector4D ywzx() const { return vector4D(m_Y, m_W, m_Z, m_X); }

		inline vector4D zxyw() const { return vector4D(m_Z, m_X, m_Y, m_W); }
		inline vector4D zxwy() const { return vector4D(m_Z, m_X, m_W, m_Y); }
		inline vector4D zyxw() const { return vector4D(m_Z, m_Y, m_X, m_W); }
		inline vector4D zywx() const { return vector4D(m_Z, m_Y, m_W, m_X); }
		inline vector4D zwxy() const { return vector4D(m_Z, m_W, m_X, m_Y); }
		inline vector4D zwyx() const { return vector4D(m_Z, m_W, m_Y, m_X); }

		inline vector4D wxyz() const { return vector4D(m_W, m_X, m_Y, m_Z); }
		inline vector4D wxzy() const { return vector4D(m_W, m_X, m_Z, m_Y); }
		inline vector4D wyxz() const { return vector4D(m_W, m_Y, m_X, m_Z); }
		inline vector4D wyzx() const { return vector4D(m_W, m_Y, m_Z, m_X); }
		inline vector4D wzxy() const { return vector4D(m_W, m_Z, m_X, m_Y); }
		inline vector4D wzyx() const { return vector4D(m_W, m_Z, m_Y, m_X); }

		// Makes all vector components zero
		inline void Zero() { m_X = 0; m_Y = 0; m_Z = 0; m_W = 0; }

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline float Length() const { return sqrtf((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z) + (m_W * m_W)); }

		// Normalizes the vector (to have Euclidean unit length)
		inline vector4D& Normalize() { float l = Length(); m_X /= l; m_Y /= l; m_Z /= l; m_W /= l; }

		// Calculates the Euclidean distance between this vector and another vector
		inline float GetDistanceTo(vector4D point) const { return (*this - point).Length(); }





		//// Operators (homogeneous versions)
		//inline f4 AddHomogeneous(const f4& other) const
		//{ 
		//	if ((w == 0 && other.w != 0) || (w != 0 && other.w == 0)) { return f4(0.0f, 0.0f, 0.0f, 0.0f); } // Point + direction (undefined)
		//	if (w == 0 && other.w == 0) { return f4(x + other.x, y + other.y, z + other.z, 0.0f); } // Direction + direction
		//	return f4((x / w) + (other.x / other.w), (y / w) + (other.y / other.w), (z / w) + (other.z / other.w), 1); // Point + point
		//}
		//inline f4 SubtractHomogeneous(const f4& other) const { return AddHomogeneous(other.MultiplyHomogeneous(-1.0f)); }
		//inline f4 MultiplyHomogeneous (float scalar) const { return f4(x * scalar, y * scalar, z * scalar, w); }
		//inline f4 DivideHomogeneous(float scalar) const { return f4(x / scalar, y / scalar, z / scalar, w); }

		//// Gets the length of the vector (as the Euclidean distance to the origin)
		//inline float LengthHomogeneous() const { return sqrtf((x * x) + (y * y) + (z * z)) / w; }
		//
		//// Normalizes the vector (to have Euclidean unit length)
		//inline f4& NormalizeHomogeneous() { float l = LengthHomogeneous(); x /= l; y /= l; z /= l); }

		//// Calculates the Euclidean distance between this vector and another vector
		//// TODO: fix for w=0 vectors
		//inline float GetDistanceToHomogeneous(f4 point) const { return (*this - point).Length(); }

		
	};

	typedef vector4D<int> vector4Di, int4, i4;
	typedef vector4D<float> vector4Df, float4, f4;
}

#endif
