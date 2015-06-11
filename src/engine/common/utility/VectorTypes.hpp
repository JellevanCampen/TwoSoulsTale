#ifndef ENGINE_COMMON_UTILITY_VECTORTYPES_H
#define ENGINE_COMMON_UTILITY_VECTORTYPES_H

#include "glm.hpp" // As base type for representing vectors

namespace Engine
{
	// 2D integer vector
	struct i2 : public glm::ivec2
	{
		typedef glm::ivec2::value_type basetype;

		i2(const glm::ivec2& i) : glm::ivec2(i.x, i.y) {}						// Constructor (copy from glm vector)
		i2() : glm::ivec2() {}													// Constructor (default, empty)
		i2(basetype i) : glm::ivec2(i, i) {}									// Constructor (single value)
		i2(basetype _x, basetype _y) : glm::ivec2(_x, _y) {}					// Constructor (two values)

		inline operator glm::ivec2 const&() { return *this; }					// Get const reference to glm vector (enables glm functions)
		inline void Zero() { x = 0; y = 0; }									// Make all vector components zero

		// Swizzle operators
		inline i2 xy() const { return i2(x, y); }
		inline i2 yx() const { return i2(y, x); }
	};
	typedef i2 int2;

	// 2D float vector
	struct  f2 : public glm::vec2
	{
		typedef glm::vec2::value_type basetype;

		f2(const glm::vec2& f) : glm::vec2(f.x, f.y) {}							// Constructor (copy from glm vector)
		f2() : glm::vec2() {}													// Constructor (default, empty)
		f2(basetype f) : glm::vec2(f, f) {}										// Constructor (single value)
		f2(basetype _x, basetype _y) : glm::vec2(_x, _y) {}						// Constructor (two values)

		inline operator glm::vec2 const&() { return *this; }					// Get const reference to glm vector (enables glm functions)
		inline void Zero() { x = 0; y = 0; }									// Make all vector components zero

		// Operators
		inline f2 f2::operator+ (const f2& other) const { return f2(x + other.x, y + other.y); }
		inline f2 f2::operator- (const f2& other) const { return f2(x - other.x, y - other.y); }
		inline f2 f2::operator* (float scalar) const { return f2(x * scalar, y * scalar); }
		inline f2 f2::operator/ (float scalar) const { return f2(x / scalar, y / scalar); }

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline float Length() const { return sqrtf((x * x) + (y * y)); }

		// Normalizes the vector (to have Euclidean unit length)
		inline f2& Normalize() { float l = Length(); x = (x / l); y = (y / l); return *this; }

		// Calculates the Euclidean distance between this vector and another vector
		inline float GetDistanceTo(f2 point) const { return (*this - point).Length(); }

		// Swizzle operators
		inline f2 xy() const { return f2(x, y); }
		inline f2 yx() const { return f2(y, x); }
	};

	// 3D integer vector
	struct i3 : public glm::ivec3
	{
		typedef glm::ivec3::value_type basetype;

		i3(const glm::ivec3& i) : glm::ivec3(i.x, i.y, i.z) {}					// Constructor (copy from glm vector)
		i3() : glm::ivec3() {}													// Constructor (default, empty)
		i3(basetype i) : glm::ivec3(i, i, i) {}									// Constructor (single value)
		i3(i2 i, basetype _z) : glm::ivec3(i.x, i.y, _z) {}					    // Constructor (2D vector + z)
		i3(basetype _x, basetype _y, basetype _z) : glm::ivec3(_x, _y, _z) {}	// Constructor (three values)

		inline operator glm::ivec3 const&() { return *this; }					// Get const reference to glm vector (enables glm functions)
		inline void Zero() { x = 0; y = 0; z = 0; }								// Make all vector components zero

		// Swizzle operators
		inline i2 xy() const { return i2(x, y); }
		inline i2 xz() const { return i2(x, z); }
		inline i2 yz() const { return i2(y, z); }
		inline i2 yx() const { return i2(y, x); }
		inline i2 zx() const { return i2(z, x); }
		inline i2 zy() const { return i2(z, y); }

		inline i3 xyz() const { return i3(x, y, z); }
		inline i3 xzy() const { return i3(x, z, y); }
		inline i3 yxz() const { return i3(y, x, z); }
		inline i3 yzx() const { return i3(y, z, x); }
		inline i3 zxy() const { return i3(z, x, y); }
		inline i3 zyx() const { return i3(z, y, x); }
	};
	typedef i3 int3;

	// 3D float vector
	struct f3 : public glm::vec3
	{
		typedef glm::vec3::value_type basetype;

		f3(const glm::vec3& f) : glm::vec3(f.x, f.y, f.z) {}					// Constructor (copy from glm vector)
		f3() : glm::vec3() {}													// Constructor (default, empty)
		f3(basetype f) : glm::vec3(f, f, f) {}									// Constructor (single value)
		f3(f2 f, basetype _z) : glm::vec3(f.x, f.y, _z) {}						// Constructor (2D vector + z)
		f3(basetype _x, basetype _y, basetype _z) : glm::vec3(_x, _y, _z) {}	// Constructor (three values)

		inline operator glm::vec3 const&()	{ return *this; }					// Get const reference to glm vector (enables glm functions)
		inline void Zero() { x = 0; y = 0; z = 0; }								// Make all vector components zero

		// Operators
		inline f3 f3::operator+ (const f3& other) const { return f3(x + other.x, y + other.y, z + other.z); }
		inline f3 f3::operator- (const f3& other) const { return f3(x - other.x, y - other.y, z - other.z); }
		inline f3 f3::operator* (float scalar) const { return f3(x * scalar, y * scalar, z * scalar); }
		inline f3 f3::operator/ (float scalar) const { return f3(x / scalar, y / scalar, z / scalar); }

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline float Length() const { return sqrtf((x * x) + (y * y) + (z * z)); }

		// Normalizes the vector (to have Euclidean unit length)
		inline f3& Normalize() { float l = Length(); x = (x / l); y = (y / l); z = (z / l); return *this; }

		// Calculates the Euclidean distance between this vector and another vector
		inline float GetDistanceTo(f3 point) const { return (*this - point).Length(); }

		// Calculates the cross product of this vector with another vector
		inline f3 Cross(const f3& other) const { return f3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

		// Swizzle operators
		inline f2 xy() const { return f2(x, y); }
		inline f2 xz() const { return f2(x, z); }
		inline f2 yz() const { return f2(y, z); }
		inline f2 yx() const { return f2(y, x); }
		inline f2 zx() const { return f2(z, x); }
		inline f2 zy() const { return f2(z, y); }

		inline f3 xyz() const { return f3(x, y, z); }
		inline f3 xzy() const { return f3(x, z, y); }
		inline f3 yxz() const { return f3(y, x, z); }
		inline f3 yzx() const { return f3(y, z, x); }
		inline f3 zxy() const { return f3(z, x, y); }
		inline f3 zyx() const { return f3(z, y, x); }
	};

	// 4D integer vector
	struct i4 : public glm::ivec4
	{
	public:
		typedef glm::ivec4::value_type basetype;

		i4(const glm::ivec4& i) : glm::ivec4(i.x, i.y, i.z, i.w) {}				// Constructor (copy from glm vector)
		i4() : glm::ivec4() {}													// Constructor (default, empty)
		i4(basetype i) : glm::ivec4(i, i, i, i) {}								// Constructor (single value)
		i4(i3 i, basetype _w) : glm::ivec4(i.x, i.y, i.z, _w) {}				// Constructor (3D vector + w)
		i4(basetype _x, basetype _y, basetype _z, basetype _w) : glm::ivec4(_x, _y, _z, _w) {} // Constructor (four values)

		inline operator glm::ivec4 const&() { return *this; }					// Get const reference to glm vector (enables glm functions)
		inline void Zero() { x = 0; y = 0; z = 0; w = 0; }						// Make all vector components zero

		// Swizzle operators
		inline i2 xy() const { return i2(x, y); }
		inline i2 xz() const { return i2(x, z); }
		inline i2 xw() const { return i2(x, w); }
		inline i2 yx() const { return i2(y, x); }
		inline i2 yz() const { return i2(y, z); }
		inline i2 yw() const { return i2(y, w); }
		inline i2 zx() const { return i2(z, x); }
		inline i2 zy() const { return i2(z, y); }
		inline i2 zw() const { return i2(z, w); }
		inline i2 wx() const { return i2(w, x); }
		inline i2 wy() const { return i2(w, y); }
		inline i2 wz() const { return i2(w, z); }

		inline i3 xyz() const { return i3(x, y, z); }
		inline i3 xyw() const { return i3(x, y, w); }
		inline i3 xzy() const { return i3(x, z, y); }
		inline i3 xzw() const { return i3(x, z, w); }
		inline i3 xwy() const { return i3(x, w, y); }
		inline i3 xwz() const { return i3(x, w, z); }

		inline i3 yxz() const { return i3(y, x, z); }
		inline i3 yxw() const { return i3(y, x, w); }
		inline i3 yzx() const { return i3(y, z, x); }
		inline i3 yzw() const { return i3(y, z, w); }
		inline i3 ywx() const { return i3(y, w, x); }
		inline i3 ywz() const { return i3(y, w, z); }

		inline i3 zxy() const { return i3(z, x, y); }
		inline i3 zxw() const { return i3(z, x, w); }
		inline i3 zyx() const { return i3(z, y, x); }
		inline i3 zyw() const { return i3(z, y, w); }
		inline i3 zwx() const { return i3(z, w, x); }
		inline i3 zwy() const { return i3(z, w, y); }

		inline i3 wxy() const { return i3(w, x, y); }
		inline i3 wxz() const { return i3(w, x, z); }
		inline i3 wyx() const { return i3(w, y, x); }
		inline i3 wyz() const { return i3(w, y, z); }
		inline i3 wzx() const { return i3(w, z, x); }
		inline i3 wzy() const { return i3(w, z, y); }

		inline i4 xyzw() const { return i4(x, y, z, w); }
		inline i4 xywz() const { return i4(x, y, w, z); }
		inline i4 xzyw() const { return i4(x, z, y, w); }
		inline i4 xzwy() const { return i4(x, z, w, y); }
		inline i4 xwyz() const { return i4(x, w, y, z); }
		inline i4 xwzy() const { return i4(x, w, z, y); }
												  
		inline i4 yxzw() const { return i4(y, x, z, w); }
		inline i4 yxwz() const { return i4(y, x, w, z); }
		inline i4 yzxw() const { return i4(y, z, x, w); }
		inline i4 yzwx() const { return i4(y, z, w, x); }
		inline i4 ywxz() const { return i4(y, w, x, z); }
		inline i4 ywzx() const { return i4(y, w, z, x); }
												  
		inline i4 zxyw() const { return i4(z, x, y, w); }
		inline i4 zxwy() const { return i4(z, x, w, y); }
		inline i4 zyxw() const { return i4(z, y, x, w); }
		inline i4 zywx() const { return i4(z, y, w, x); }
		inline i4 zwxy() const { return i4(z, w, x, y); }
		inline i4 zwyx() const { return i4(z, w, y, x); }
												  
		inline i4 wxyz() const { return i4(w, x, y, z); }
		inline i4 wxzy() const { return i4(w, x, z, y); }
		inline i4 wyxz() const { return i4(w, y, x, z); }
		inline i4 wyzx() const { return i4(w, y, z, x); }
		inline i4 wzxy() const { return i4(w, z, x, y); }
		inline i4 wzyx() const { return i4(w, z, y, x); }
	};
	typedef i4 int4;

	// 4D float vector
	struct f4 : public glm::vec4
	{
	public:
		typedef glm::vec4::value_type basetype;

		f4(const glm::vec4& f) : glm::vec4(f.x, f.y, f.z, f.w) {}				// Constructor (copy from glm vector)
		f4() : glm::vec4() {}													// Constructor (default, empty)
		f4(basetype f) : glm::vec4(f, f, f, f) {}								// Constructor (single value)
		f4(f3 f, basetype _w) : glm::vec4(f.x, f.y, f.z, _w) {}					// Constructor (3D vector + w)
		f4(basetype _x, basetype _y, basetype _z, basetype _w) : glm::vec4(_x, _y, _z, _w) {} // Constructor (four values)

		inline operator glm::vec4 const&() { return *this; }					// Get const reference to glm vector (enables glm functions)
		inline void Zero() { x = 0; y = 0; z = 0; w = 0; }						// Make all vector components zero

		// Operators
		inline f4 f4::operator+ (const f4& other) const { return f4(x + other.x, y + other.y, z + other.z, w + other.w); }
		inline f4 f4::operator- (const f4& other) const { return f4(x - other.x, y - other.y, z - other.z, w - other.w); }
		inline f4 f4::operator* (float scalar) const { return f4(x * scalar, y * scalar, z * scalar, w * scalar); }
		inline f4 f4::operator/ (float scalar) const { return f4(x / scalar, y / scalar, z / scalar, w * scalar); }

		// Operators (homogeneous versions)
		inline f4 AddHomogeneous(const f4& other) const
		{ 
			if ((w == 0 && other.w != 0) || (w != 0 && other.w == 0)) { return f4(0.0f, 0.0f, 0.0f, 0.0f); } // Point + direction (undefined)
			if (w == 0 && other.w == 0) { return f4(x + other.x, y + other.y, z + other.z, 0.0f); } // Direction + direction
			return f4((x / w) + (other.x / other.w), (y / w) + (other.y / other.w), (z / w) + (other.z / other.w), 1); // Point + point
		}
		inline f4 SubtractHomogeneous(const f4& other) const { return AddHomogeneous(other.MultiplyHomogeneous(-1.0f)); }
		inline f4 MultiplyHomogeneous (float scalar) const { return f4(x * scalar, y * scalar, z * scalar, w); }
		inline f4 DivideHomogeneous(float scalar) const { return f4(x / scalar, y / scalar, z / scalar, w); }

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline float Length() const { return sqrtf((x * x) + (y * y) + (z * z) + (w * w)); }
		inline float LengthHomogeneous() const { return sqrtf((x * x) + (y * y) + (z * z)) / w; }
		
		// Normalizes the vector (to have Euclidean unit length)
		inline f4& Normalize() { float l = Length(); x = (x / l); y = (y / l); z = (z / l); w = (w / l); }
		inline f4& NormalizeHomogeneous() { float l = LengthHomogeneous(); x = (x / l); y = (y / l); z = (z / l); }

		// Calculates the Euclidean distance between this vector and another vector
		// TODO: fix for w=0 vectors
		inline float GetDistanceTo(f4 point) const { return (*this - point).Length(); }
		inline float GetDistanceToHomogeneous(f4 point) const { return (*this - point).Length(); }

		// Swizzle operators
		inline i2 xy() const { return i2(x, y); }
		inline i2 xz() const { return i2(x, z); }
		inline i2 xw() const { return i2(x, w); }
		inline i2 yx() const { return i2(y, x); }
		inline i2 yz() const { return i2(y, z); }
		inline i2 yw() const { return i2(y, w); }
		inline i2 zx() const { return i2(z, x); }
		inline i2 zy() const { return i2(z, y); }
		inline i2 zw() const { return i2(z, w); }
		inline i2 wx() const { return i2(w, x); }
		inline i2 wy() const { return i2(w, y); }
		inline i2 wz() const { return i2(w, z); }

		inline i3 xyz() const { return i3(x, y, z); }
		inline i3 xyw() const { return i3(x, y, w); }
		inline i3 xzy() const { return i3(x, z, y); }
		inline i3 xzw() const { return i3(x, z, w); }
		inline i3 xwy() const { return i3(x, w, y); }
		inline i3 xwz() const { return i3(x, w, z); }

		inline i3 yxz() const { return i3(y, x, z); }
		inline i3 yxw() const { return i3(y, x, w); }
		inline i3 yzx() const { return i3(y, z, x); }
		inline i3 yzw() const { return i3(y, z, w); }
		inline i3 ywx() const { return i3(y, w, x); }
		inline i3 ywz() const { return i3(y, w, z); }

		inline i3 zxy() const { return i3(z, x, y); }
		inline i3 zxw() const { return i3(z, x, w); }
		inline i3 zyx() const { return i3(z, y, x); }
		inline i3 zyw() const { return i3(z, y, w); }
		inline i3 zwx() const { return i3(z, w, x); }
		inline i3 zwy() const { return i3(z, w, y); }

		inline i3 wxy() const { return i3(w, x, y); }
		inline i3 wxz() const { return i3(w, x, z); }
		inline i3 wyx() const { return i3(w, y, x); }
		inline i3 wyz() const { return i3(w, y, z); }
		inline i3 wzx() const { return i3(w, z, x); }
		inline i3 wzy() const { return i3(w, z, y); }

		inline f4 xyzw() const { return f4(x, y, z, w); }
		inline f4 xywz() const { return f4(x, y, w, z); }
		inline f4 xzyw() const { return f4(x, z, y, w); }
		inline f4 xzwy() const { return f4(x, z, w, y); }
		inline f4 xwyz() const { return f4(x, w, y, z); }
		inline f4 xwzy() const { return f4(x, w, z, y); }

		inline f4 yxzw() const { return f4(y, x, z, w); }
		inline f4 yxwz() const { return f4(y, x, w, z); }
		inline f4 yzxw() const { return f4(y, z, x, w); }
		inline f4 yzwx() const { return f4(y, z, w, x); }
		inline f4 ywxz() const { return f4(y, w, x, z); }
		inline f4 ywzx() const { return f4(y, w, z, x); }

		inline f4 zxyw() const { return f4(z, x, y, w); }
		inline f4 zxwy() const { return f4(z, x, w, y); }
		inline f4 zyxw() const { return f4(z, y, x, w); }
		inline f4 zywx() const { return f4(z, y, w, x); }
		inline f4 zwxy() const { return f4(z, w, x, y); }
		inline f4 zwyx() const { return f4(z, w, y, x); }

		inline f4 wxyz() const { return f4(w, x, y, z); }
		inline f4 wxzy() const { return f4(w, x, z, y); }
		inline f4 wyxz() const { return f4(w, y, x, z); }
		inline f4 wyzx() const { return f4(w, y, z, x); }
		inline f4 wzxy() const { return f4(w, z, x, y); }
		inline f4 wzyx() const { return f4(w, z, y, x); }
	};
}

#endif
