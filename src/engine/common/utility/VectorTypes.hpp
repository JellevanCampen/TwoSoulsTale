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

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline basetype Length() const { const glm::vec2& v = *this; return glm::length<basetype>(v); }

		// Normalizes the vector (to have Euclidean unit length)
		inline f2 Normalize()
		{
			*this = glm::normalize(operator glm::vec2 const&());
			return *this;
		}
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

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline basetype Length() const { const glm::vec3& v = *this; return glm::length<basetype>(v); }

		// Calculates the cross product of this vector with another vector
		inline f3 Cross(const f3& other) const { return glm::cross(*this, other); }

		// Normalizes the vector (to have Euclidean unit length)
		inline f3 Normalize()
		{
			*this = glm::normalize(operator glm::vec3 const&());
			return *this;
		}
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

		inline i3 xyz() const { return i3(this->x, this->y, this->z); }			// Gets the first three components of the vector
		inline i3 xy() const { return i3(this->x, this->y, this->z); }			// Gets the first two components of the vector
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

		// Gets the length of the vector (as the Euclidean distance to the origin)
		inline basetype Length() const { const glm::vec4& v = *this; return glm::length<basetype>(v); }
		
		// Normalizes the vector (to have Euclidean unit length)
		inline f4 Normalize()
		{
			*this = glm::normalize(operator glm::vec4 const&());
			return *this;
		}

		inline f3 xyz() const { return f3(this->x, this->y, this->z); }			// Gets the first three components of the vector
		inline f3 xy() const { return f3(this->x, this->y, this->z); }			// Gets the first two components of the vector
	};
}

#endif
