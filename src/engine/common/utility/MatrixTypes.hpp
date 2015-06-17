#ifndef ENGINE_COMMON_UTILITY_MATRIXTYPES_H
#define ENGINE_COMMON_UTILITY_MATRIXTYPES_H

#include "glm.hpp" // As base type for representing matrices
#include "VectorTypes.hpp" // For representing vectors

namespace Engine
{
	////////////////////////////////////////////////////////////////
	// 2x2 matrices                                               //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct matrix2x2
	{

	private:

		valuetype m_V[4];

	public:

		// Enum describing the ways in which a matrix can be initialized
		enum class InitializationType
		{
			e_NoInitialization, 
			e_Zeros, 
			e_Identity
		};

		// Constructors
		matrix2x2(InitializationType initialization = InitializationType::e_Zeros) 
		{ 
			switch (initialization)
			{
			case InitializationType::e_Zeros: SetZeros(); break;
			case InitializationType::e_Identity: SetIdentity(); break;
			}
		}
		matrix2x2(valuetype v) { for (size_t i = 0; i < 4; i++) { m_V[i] = (i % 2 == i / 2)?v:0; } }
		matrix2x2(vector2D<valuetype> v) { for (size_t i = 0; i < 4; i++) { m_V[i] = (i % 2 == i / 2) ? v : 0; } }
		matrix2x2(valuetype v[4]) { for (size_t i = 0; i < 4; i++) { m_V[i] = v[i]; } }
		matrix2x2(const glm::tmat2x2<glm::lowp_float>& m) { for (size_t i = 0; i < 4; i++) { m_V[i] = m[i / 2][i % 2]; } }	
		matrix2x2(const glm::tmat2x2<glm::highp_float>& m) { for (size_t i = 0; i < 4; i++) { m_V[i] = m[i / 2][i % 2]; } }

		// Casts
		// TODO: check if the element order is correct (GLM = row major?)
		inline operator glm::mat2&() const { return glm::mat2(m_V[0], m_V[1], m_V[2], m_V[3]); }

		// Getters
		inline valuetype& Get(size_t element) { return m_V[element]; }
		inline valuetype& Get(size_t row, size_t column) { return m_V[row * 2 + column]; }
		inline const valuetype& Get(size_t element) const { return m_V[element]; }
		inline const valuetype& Get(size_t row, size_t column ) const { return m_V[row * 2 + column]; }

		// Setters
		inline matrix2x2& Set(size_t element, valuetype value) { m_V[element] = value; return *this; }
		inline matrix2x2& Set(size_t row, size_t column, valuetype value) { m_V[row * 2 + column] = value; return *this; }

		// Operators
		inline matrix2x2 operator+ (const matrix2x2& other) const { matrix2x2 m; for (size_t i = 0; i < 4; i++) { m.Set(i, m_V[i] + other.Get(i)); } return m; }
		inline matrix2x2 operator- (const matrix2x2& other) const { matrix2x2 m; for (size_t i = 0; i < 4; i++) { m.Set(i, m_V[i] - other.Get(i)); } return m; }
		inline matrix2x2 operator* (float scalar) const { matrix2x2 m; for (size_t i = 0; i < 4; i++) { m.Set(i, m_V[i] * scalar); } return m; }
		inline vector2D<valuetype> operator* (const vector2D<valuetype>& other) const { Multiply(other); }
		inline matrix2x2 operator* (const matrix2x2& other) const { Multiply(other); }
		inline matrix2x2 operator/ (float scalar) const { matrix2x2 m; for (size_t i = 0; i < 4; i++) { m.Set(i, m_V[i] / scalar); } return m; }
		inline valuetype& operator[] (size_t index) { return m_V[i]; }
		template<typename valuetype> inline const valuetype& operator[] (size_t index) const { return m_V[i]; }

		// Gets the diagonal elements of the matrix
		inline vector2D<valuetype> GetDiagonal() const { return vector2D<valuetype>(m_V[0], m_V[3]); }

		// Sets the diagonal elements of the matrix to the values of the given vector
		inline matrix2x2& SetDiagonal(const vector2D<valuetype>& diagonal) { for (size_t i = 0; i < 2; i++) { m_V[i * 2 + i] = diagonal[i]; } return *this; }

		// Sets the diagonal elements of the matrix to the given value
		inline matrix2x2& SetDiagonal(const float diagonal) { for (size_t i = 0; i < 2; i++) { m_V[i * 2 + i] = diagonal; } return *this; }

		// Set the matrix to have all zero components
		inline matrix2x2& SetZeros() { for (size_t i = 0; i < 4; i++) { m_V[i] = 0; } return *this; }

		// Set the matrix to be an identity matrix
		inline matrix2x2& SetIdentity() { for (size_t i = 0; i < 4; i++) { m_V[i] = (i % 2 == i / 2) ? 1 : 0; }	return *this; }

		// Transposes the matrix
		inline matrix2x2& Transpose() 
		{ 
			valuetype temp;
			for (int i = 1; i < 2; i++)
			{
				for (int j = 0; j < i; j++)
				{
					temp = m_V[i * 2 + j];
					m_V[i * 2 + j] = m_V[j * 2 + i];
					m_V[j * 2 + i] = temp;
				}
			}
		}

		// Calculates the inverse matrix
		inline matrix2x2 GetInverse() const
		{
			glm::mat2 m = *this;
			return glm::inverse(m);
		}

		// Multiplies the matrix by another matrix (mat * mat = mat)
		// TODO: check if the result is correct
		inline matrix2x2 Multiply(const matrix2x2& other) const
		{
			matrix2x2 m(InitializationType::e_Zeros);
			for (int i = 0; i < 2; i++)
				for (int k = 0; k < 2; k++)
					for (int j = 0; j < 2; j++)
						m[i * 2 + j] += Get(i, k) * other.Get(k, j);
			return m;
		}

		// Multiplies the matrix by a vector (mat * vec = vec)
		// TODO: check if the result is correct
		inline vector2D<valuetype> Multiply(const vector2D<valuetype>& other) const
		{
			vector2D<valuetype> v();
			for (int i = 0; i < 2; i++)
				for (int k = 0; k < 2; k++)
					v[i] += Get(i, k) * other[i];
			return v;
		}

	};

	typedef matrix2x2<int> matrix2x2i, mat2i, int2x2, i2x2;
	typedef matrix2x2<float> matrix2x2f, mat2f, float2x2, f2x2;

	////////////////////////////////////////////////////////////////
	// 3x3 matrices                                               //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct matrix3x3
	{

	private:

		valuetype m_V[9];

	public:

		// Enum describing the ways in which a matrix can be initialized
		enum class InitializationType
		{
			e_NoInitialization,
			e_Zeros,
			e_Identity
		};

		// Constructors
		matrix3x3(InitializationType initialization = InitializationType::e_Zeros)
		{
			switch (initialization)
			{
			case InitializationType::e_Zeros: SetZeros(); break;
			case InitializationType::e_Identity: SetIdentity(); break;
			}
		}
		matrix3x3(valuetype v) { for (size_t i = 0; i < 9; i++) { m_V[i] = (i % 3 == i / 3) ? v : 0; } }
		matrix3x3(vector2D<valuetype> v) { for (size_t i = 0; i < 9; i++) { m_V[i] = (i % 3 == i / 3) ? v : 0; } }
		matrix3x3(valuetype v[9]) { for (size_t i = 0; i < 9; i++) { m_V[i] = v[i]; } }
		matrix3x3(const glm::tmat3x3<glm::lowp_float>& m) { for (size_t i = 0; i < 9; i++) { m_V[i] = m[i / 3][i % 3]; } } // TODO: correct order?
		matrix3x3(const glm::tmat3x3<glm::highp_float>& m) { for (size_t i = 0; i < 9; i++) { m_V[i] = m[i / 3][i % 3]; } } // TODO: correct order?

		// Casts
		// TODO: check if the element order is correct (GLM = row major?)
		inline operator glm::mat3&() const { glm::mat3 m; for (int i = 0; i < 9; i++) { m[i / 3][i % 3] = m_V[i]; } return m; }

		// Getters
		inline valuetype& Get(size_t element) { return m_V[element]; }
		inline valuetype& Get(size_t row, size_t column) { return m_V[row * 3 + column]; }
		inline const valuetype& Get(size_t element) const { return m_V[element]; }
		inline const valuetype& Get(size_t row, size_t column) const { return m_V[row * 3 + column]; }

		// Setters
		inline matrix3x3& Set(size_t element, valuetype value) { m_V[element] = value; return *this; }
		inline matrix3x3& Set(size_t row, size_t column, valuetype value) { m_V[row * 3 + column] = value; return *this; }

		// Operators
		inline matrix3x3 operator+ (const matrix3x3& other) const { matrix3x3 m; for (size_t i = 0; i < 9; i++) { m.Set(i, m_V[i] + other.Get(i)); } return m; }
		inline matrix3x3 operator- (const matrix3x3& other) const { matrix3x3 m; for (size_t i = 0; i < 9; i++) { m.Set(i, m_V[i] - other.Get(i)); } return m; }
		inline matrix3x3 operator* (float scalar) const { matrix3x3 m; for (size_t i = 0; i < 9; i++) { m.Set(i, m_V[i] * scalar); } return m; }
		inline vector3D<valuetype> operator* (const vector3D<valuetype>& other) const { Multiply(other); }
		inline matrix3x3 operator* (const matrix3x3& other) const { Multiply(other); }
		inline matrix3x3 operator/ (float scalar) const { matrix3x3 m; for (size_t i = 0; i < 9; i++) { m.Set(i, m_V[i] / scalar); } return m; }
		inline valuetype& operator[] (size_t index) { return m_V[i]; }
		template<typename valuetype> inline const valuetype& operator[] (size_t index) const { return m_V[i]; }

		// Gets the diagonal elements of the matrix
		inline vector2D<valuetype> GetDiagonal() const { return vector3D<valuetype>(m_V[0], m_V[4], m_V[8]); }

		// Sets the diagonal elements of the matrix to the values of the given vector
		inline matrix3x3& SetDiagonal(const vector3D<valuetype>& diagonal) { for (size_t i = 0; i < 3; i++) { m_V[i * 3 + i] = diagonal[i]; } return *this; }

		// Sets the diagonal elements of the matrix to the given value
		inline matrix3x3& SetDiagonal(const float diagonal) { for (size_t i = 0; i < 3; i++) { m_V[i * 3 + i] = diagonal; } return *this; }

		// Set the matrix to have all zero components
		inline matrix3x3& SetZeros() { for (size_t i = 0; i < 9; i++) { m_V[i] = 0; } return *this; }

		// Set the matrix to be an identity matrix
		inline matrix3x3& SetIdentity() { for (size_t i = 0; i < 9; i++) { m_V[i] = (i % 3 == i / 3) ? 1 : 0; }	return *this; }

		// Transposes the matrix
		inline matrix3x3& Transpose()
		{
			valuetype temp;
			for (int i = 1; i < 3; i++)
			{
				for (int j = 0; j < i; j++)
				{
					temp = m_V[i * 3 + j];
					m_V[i * 3 + j] = m_V[j * 3 + i];
					m_V[j * 3 + i] = temp;
				}
			}
		}

		// Calculates the inverse matrix
		inline matrix3x3 GetInverse() const
		{
			glm::mat3 m = *this;
			return glm::inverse(m);
		}

		// Multiplies the matrix by another matrix (mat * mat = mat)
		// TODO: check if the result is correct
		inline matrix3x3 Multiply(const matrix3x3& other) const
		{
			matrix3x3 m(InitializationType::e_Zeros);
			for (int i = 0; i < 3; i++)
				for (int k = 0; k < 3; k++)
					for (int j = 0; j < 3; j++)
						m[i * 3 + j] += Get(i, k) * other.Get(k, j);
			return m;
		}

		// Multiplies the matrix by a vector (mat * vec = vec)
		// TODO: check if the result is correct
		inline vector2D<valuetype> Multiply(const vector2D<valuetype>& other) const
		{
			vector2D<valuetype> v();
			for (int i = 0; i < 3; i++)
				for (int k = 0; k < 3; k++)
					v[i] += Get(i, k) * other[i];
			return v;
		}

	};

	typedef matrix3x3<int> matrix3x3i, mat3i, int3x3, i3x3;
	typedef matrix3x3<float> matrix3x3f, mat3f, float3x3, f3x3;

	////////////////////////////////////////////////////////////////
	// 4x4 matrices                                               //
	////////////////////////////////////////////////////////////////

	template <typename valuetype>
	struct matrix4x4
	{

	private:

		valuetype m_V[16];

	public:

		// Enum describing the ways in which a matrix can be initialized
		enum class InitializationType
		{
			e_NoInitialization,
			e_Zeros,
			e_Identity
		};

		// Constructors
		matrix4x4(InitializationType initialization = InitializationType::e_Zeros)
		{
			switch (initialization)
			{
			case InitializationType::e_Zeros: SetZeros(); break;
			case InitializationType::e_Identity: SetIdentity(); break;
			}
		}
		matrix4x4(valuetype v) { for (size_t i = 0; i < 16; i++) { m_V[i] = (i % 4 == i / 4) ? v : 0; } }
		matrix4x4(vector4D<valuetype> v) { for (size_t i = 0; i < 16; i++) { m_V[i] = (i % 4 == i / 4) ? v : 0; } }
		matrix4x4(valuetype v[16]) { for (size_t i = 0; i < 16; i++) { m_V[i] = v[i]; } }
		matrix4x4(const glm::tmat4x4<glm::lowp_float>& m) { for (size_t i = 0; i < 16; i++) { m_V[i] = m[i / 4][i % 4]; } } // TODO: correct order?
		matrix4x4(const glm::tmat4x4<glm::highp_float>& m) { for (size_t i = 0; i < 16; i++) { m_V[i] = m[i / 4][i % 4]; } } // TODO: correct order?

		// Casts
		// TODO: check if the element order is correct (GLM = row major?)
		inline operator glm::mat4&() const { glm::mat4 m; for (int i = 0; i < 16; i++) { m[i / 4][i % 4] = m_V[i]; } return m; }

		// Getters
		inline valuetype& Get(size_t element) { return m_V[element]; }
		inline valuetype& Get(size_t row, size_t column) { return m_V[row * 4 + column]; }
		inline const valuetype& Get(size_t element) const { return m_V[element]; }
		inline const valuetype& Get(size_t row, size_t column) const { return m_V[row * 4 + column]; }

		// Setters
		inline matrix4x4& Set(size_t element, valuetype value) { m_V[element] = value; return *this; }
		inline matrix4x4& Set(size_t row, size_t column, valuetype value) { m_V[row * 4 + column] = value; return *this; }

		// Operators
		inline matrix4x4 operator+ (const matrix4x4& other) const { matrix4x4 m; for (size_t i = 0; i < 16; i++) { m.Set(i, m_V[i] + other.Get(i)); } return m; }
		inline matrix4x4 operator- (const matrix4x4& other) const { matrix4x4 m; for (size_t i = 0; i < 16; i++) { m.Set(i, m_V[i] - other.Get(i)); } return m; }
		inline matrix4x4 operator* (float scalar) const { matrix4x4 m; for (size_t i = 0; i < 16; i++) { m.Set(i, m_V[i] * scalar); } return m; }
		inline vector4D<valuetype> operator* (const vector4D<valuetype>& other) const { Multiply(other); }
		inline matrix4x4 operator* (const matrix4x4& other) const { Multiply(other); }
		inline matrix4x4 operator/ (float scalar) const { matrix4x4 m; for (size_t i = 0; i < 16; i++) { m.Set(i, m_V[i] / scalar); } return m; }
		inline valuetype& operator[] (size_t index) { return m_V[i]; }
		template<typename valuetype> inline const valuetype& operator[] (size_t index) const { return m_V[i]; }

		// Gets the diagonal elements of the matrix
		inline vector2D<valuetype> GetDiagonal() const { return vector4D<valuetype>(m_V[0], m_V[5], m_V[10], m_V[15]); }

		// Sets the diagonal elements of the matrix to the values of the given vector
		inline matrix4x4& SetDiagonal(const vector4D<valuetype>& diagonal) { for (size_t i = 0; i < 4; i++) { m_V[i * 4 + i] = diagonal[i]; } return *this; }

		// Sets the diagonal elements of the matrix to the given value
		inline matrix4x4& SetDiagonal(const float diagonal) { for (size_t i = 0; i < 4; i++) { m_V[i * 4 + i] = diagonal; } return *this; }

		// Set the matrix to have all zero components
		inline matrix4x4& SetZeros() { for (size_t i = 0; i < 16; i++) { m_V[i] = 0; } return *this; }

		// Set the matrix to be an identity matrix
		inline matrix4x4& SetIdentity() { for (size_t i = 0; i < 16; i++) { m_V[i] = (i % 4 == i / 4) ? 1 : 0; } return *this; }

		// Transposes the matrix
		inline matrix4x4& Transpose()
		{
			valuetype temp;
			for (int i = 1; i < 4; i++)
			{
				for (int j = 0; j < i; j++)
				{
					temp = m_V[i * 4 + j];
					m_V[i * 4 + j] = m_V[j * 4 + i];
					m_V[j * 4 + i] = temp;
				}
			}
		}

		// Calculates the inverse matrix
		inline matrix4x4 GetInverse() const
		{
			glm::mat4 m = *this;
			return glm::inverse(m);
		}

		// Multiplies the matrix by another matrix (mat * mat = mat)
		// TODO: check if the result is correct
		inline matrix4x4 Multiply(const matrix4x4& other) const
		{
			matrix4x4 m(InitializationType::e_Zeros);
			for (int i = 0; i < 4; i++)
				for (int k = 0; k < 4; k++)
					for (int j = 0; j < 4; j++)
						m[i * 4 + j] += Get(i, k) * other.Get(k, j);
			return m;
		}

		// Multiplies the matrix by a vector (mat * vec = vec)
		// TODO: check if the result is correct
		inline vector2D<valuetype> Multiply(const vector2D<valuetype>& other) const
		{
			vector2D<valuetype> v();
			for (int i = 0; i < 4; i++)
				for (int k = 0; k < 4; k++)
					v[i] += Get(i, k) * other[i];
			return v;
		}

	};

	typedef matrix4x4<int> matrix4x4i, mat4i, int4x4, i4x4;
	typedef matrix4x4<float> matrix4x4f, mat4f, float4x4, f4x4;
}

#endif
