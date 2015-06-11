#ifndef ENGINE_COMMON_UTILITY_MATRIXTYPES_H
#define ENGINE_COMMON_UTILITY_MATRIXTYPES_H

#include "glm.hpp" // As base type for representing matrices
#include "VectorTypes.hpp" // For representing vectors

namespace Engine
{
	// 2 x 2 matrix of floats
	struct f2x2 : public glm::mat2
	{
		f2x2(){}														// Constructor (default, empty)
		f2x2(glm::tmat2x2<glm::lowp_float>& m) : glm::mat2(m) {}		// Constructor (copy from glm matrix, low precision)
		f2x2(glm::tmat2x2<glm::highp_float>& m) : glm::mat2(m) {}	// Constructor (copy from glm matrix, high precision) 
		inline operator glm::mat2 const&() { return *this; }			// Get const reference to glm matrix (enables glm functions)

		// Gets a const reference to the element at the specified index
		inline const float& operator[](size_t index) const { return glm::mat2::operator[](index / 2)[index % 2]; }

		// Gets a reference to the element at the specified index
		inline float& operator[](size_t index) { return glm::mat2::operator[](index / 2)[index % 2]; }

		// Sets the diagonal elements of the matrix to the values of the given vector
		inline void Diagonal(const f2& diagonal){ (*this)[0] = diagonal.x; (*this)[3] = diagonal.y; }

		// Sets the diagonal elements of the matrix to the given value
		inline void Diagonal(const float diagonal){ (*this)[0] = diagonal; (*this)[3] = diagonal; }

		// Make all matrix components zero
		inline const f2x2& Zero(){
			for (size_t i = 0; i < 4; i++) { (*this)[i] = 0; }
			return *this;
		}

		// Make the matrix an identity matrix
		inline const f2x2& Identity()
		{
			for (size_t i = 0; i < 2; i++) { 
				for (size_t j = 0; j < 2; j++) {
					(*this)[(2 * j) + i] = (i == j)?1:0;
				}
			}
			return *this;
		}

		// Multiplies the matrix by another matrix (mat * mat = mat)
		inline const f2x2& Mul(const f2x2& m)
		{
			glm::tmat2x2<float> result = (*this) * m;
			operator=(f2x2(result));
			return *this;
		}

		// Multiplies the matrix by a vector (mat * vec = vec)
		inline const f2 Mul(const f2& vector) const
		{
			return f2((*this) * vector);
		}

		// Multiplies the matrix by another matrix or a vector
		inline const f2x2& operator *= (const f2x2& other)
		{
			return Mul(other);
		}

		// Calculates the inverse of the matrix
		inline f2x2 Inverse() {
			glm::tmat2x2<float> result = this->Inverse();
			operator=(f2x2(result));
			return *this;
		}
	};
	typedef f2x2 float2x2, mat2f, matrix2f;

	// 3 x 3 matrix of floats
	struct f3x3 : public glm::mat3
	{
		f3x3(){}														// Constructor (default, empty)
		f3x3(glm::tmat3x3<glm::lowp_float>& m) : glm::mat3(m) {}		// Constructor (copy from glm matrix, low precision)
		f3x3(glm::tmat3x3<glm::highp_float>& m) : glm::mat3(m) {}	// Constructor (copy from glm matrix, high precision) 
		inline operator glm::mat3 const&() { return *this; }			// Get const reference to glm matrix (enables glm functions)

		// Gets a const reference to the element at the specified index
		inline const float& operator[](size_t index) const { return glm::mat3::operator[](index / 3)[index % 3]; }

		// Gets a reference to the element at the specified index
		inline float& operator[](size_t index) { return glm::mat3::operator[](index / 3)[index % 3]; }

		// Sets the diagonal elements of the matrix to the values of the given vector
		inline void Diagonal(const f3& diagonal){ (*this)[0] = diagonal.x; (*this)[4] = diagonal.y; (*this)[8] = diagonal.z; }

		// Sets the diagonal elements of the matrix to the given value
		inline void Diagonal(const float diagonal){ (*this)[0] = diagonal; (*this)[4] = diagonal; (*this)[8] = diagonal; }

		// Make all matrix components zero
		inline const f3x3& Zero(){
			for (size_t i = 0; i < 9; i++) { (*this)[i] = 0; }
			return *this;
		}

		// Make the matrix an identity matrix
		inline const f3x3& Identity()
		{
			for (size_t i = 0; i < 3; i++) {
				for (size_t j = 0; j < 3; j++) {
					(*this)[(3 * j) + i] = (i == j) ? 1 : 0;
				}
			}
			return *this;
		}

		// Multiplies the matrix by another matrix (mat * mat = mat)
		inline const f3x3& Mul(const f3x3& m)
		{
			glm::tmat3x3<float> result = (*this) * m;
			operator=(f3x3(result));
			return *this;
		}
		
		// Multiplies the matrix by a vector (mat * vec = vec)
		inline const f3 Mul(const f3& vector) const
		{
			return f3((*this) * vector);
		}

		// Multiplies the matrix by another matrix or a vector
		inline const f3x3& operator *= (const f3x3& other)
		{
			return Mul(other);
		}

		// Calculates the inverse of the matrix
		inline f3x3 Inverse()
		{
			glm::tmat3x3<float> result = this->Inverse();
			operator=(f3x3(result));
			return *this;
		}
	};
	typedef f3x3 float3x3, mat3f, matrix3f;

	// 4 x 4 matrix of floats
	struct f4x4 : public glm::mat4
	{
		f4x4(){}														// Constructor (default, empty)
		f4x4(glm::tmat4x4<glm::lowp_float>& m) : glm::mat4(m) {}		// Constructor (copy from glm matrix, low precision)
		f4x4(glm::tmat4x4<glm::highp_float>& m) : glm::mat4(m) {}		// Constructor (copy from glm matrix, high precision) 
		inline operator glm::mat4 const&() { return *this; }			// Get const reference to glm matrix (enables glm functions)

		// Gets a const reference to the element at the specified index
		inline const float& operator[](size_t index) const { return glm::mat4::operator[](index / 4)[index % 4]; }

		// Gets a reference to the element at the specified index
		inline float& operator[](size_t index) { return glm::mat4::operator[](index / 4)[index % 4]; }

		// Sets the diagonal elements of the matrix to the values of the given vector
		inline void Diagonal(const f4& diagonal){ (*this)[0] = diagonal.x; (*this)[5] = diagonal.y; (*this)[10] = diagonal.z; (*this)[15] = diagonal.w; }

		// Sets the diagonal elements of the matrix to the given value
		inline void Diagonal(const float diagonal){ (*this)[0] = diagonal; (*this)[5] = diagonal; (*this)[10] = diagonal; (*this)[15] = 1.0f; }

		// Make all matrix components zero
		inline const f4x4& Zero(){
			for (size_t i = 0; i < 16; i++) { (*this)[i] = 0; }
			return *this;
		}

		// Make the matrix an identity matrix
		inline const f4x4& Identity()
		{
			for (size_t i = 0; i < 4; i++) {
				for (size_t j = 0; j < 4; j++) {
					(*this)[(4 * j) + i] = (i == j) ? 1 : 0;
				}
			}
			return *this;
		}

		// Multiplies the matrix by another matrix (mat * mat = mat)
		inline const f4x4& Mul(const f4x4& m)
		{
			glm::tmat4x4<glm::lowp_float> result = (*this) * m;
			operator=(f4x4(result));
			return *this;
		}

		// Multiplies the matrix by a vector (mat * vec = vec)
		inline const f4 Mul(const f4& vector) const
		{
			return f4((*this) * vector);
		}

		// Multiplies the matrix by another matrix or a vector
		inline const f4x4& operator *= (const f4x4& other)
		{
			return Mul(other);
		}

		// Sets the values of one row in the matrix to the given vector
		inline void SetRow(const f4& col, int row)
		{
			operator[](row * 4 + 0) = col.x;
			operator[](row * 4 + 1) = col.y;
			operator[](row * 4 + 2) = col.z;
			operator[](row * 4 + 3) = col.w;
		}

		// Sets the values of one column in the matrix to the given vector
		inline void SetColumn(const f4& col, int column)
		{
			operator[](column + 4 * 0) = col.x;
			operator[](column + 4 * 1) = col.y;
			operator[](column + 4 * 2) = col.z;
			operator[](column + 4 * 3) = col.w;
		}

		// Calculates the inverse of the matrix
		inline f4x4 Inverse() {
			glm::tmat4x4<float> result = this->Inverse();
			operator=(f4x4(result));
			return *this;
		}
	};
	typedef f4x4 float4x4, mat4f, matrix4f;
}

#endif
