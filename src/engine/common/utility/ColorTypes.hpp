#ifndef ENGINE_COMMON_UTILITY_COLORTYPES_H
#define ENGINE_COMMON_UTILITY_COLORTYPES_H

#include "glm.hpp" // As base type for representing vectors
#include "VectorTypes.hpp" // For representing colors as vectors

namespace Engine
{
	////////////////////////////////////////////////////////////////
	// RGBA color                                                 //
	////////////////////////////////////////////////////////////////

	struct colorRGBA
	{

	private:

		float m_R, m_G, m_B, m_A;

	public:

		// Constructors
		colorRGBA() : m_R(0.0f), m_G(0.0f), m_B(0.0f), m_A(1.0f) { }
		colorRGBA(float v) : m_R(fmin(fmax(v, 0.0f), 1.0f)), m_G(fmin(fmax(v, 0.0f), 1.0f)), m_B(fmin(fmax(v, 0.0f), 1.0f)), m_A(1.0f) { }
		colorRGBA(int v) : colorRGBA(fmin(fmax(v / 255.0f, 0.0f), 1.0f)) { }
		colorRGBA(vector3D<float> rgb, float a) : m_R(fmin(fmax(rgb.x(), 0.0f), 1.0f)), m_G(fmin(fmax(rgb.y(), 0.0f), 1.0f)), m_B(fmin(fmax(rgb.z(), 0.0f), 1.0f)), m_A(fmin(fmax(a, 0.0f), 1.0f)) { }
		colorRGBA(vector3D<int> rgb, int a) : m_R(fmin(fmax(rgb.x() / 255.0f, 0.0f), 1.0f)), m_G(fmin(fmax(rgb.y() / 255.0f, 0.0f), 1.0f)), m_B(fmin(fmax(rgb.z() / 255.0f, 0.0f), 1.0f)), m_A(fmin(fmax(a / 255.0f, 0.0f), 1.0f)) { }
		colorRGBA(float r, float g, float b, float a = 1.0f) : m_R(fmin(fmax(r, 0.0f), 1.0f)), m_G(fmin(fmax(g, 0.0f), 1.0f)), m_B(fmin(fmax(b, 0.0f), 1.0f)), m_A(fmin(fmax(a, 0.0f), 1.0f)) { }
		colorRGBA(int r, int g, int b, int a = 255) : m_R(fmin(fmax(r / 255.0f, 0.0f), 1.0f)), m_G(fmin(fmax(g / 255.0f, 0.0f), 1.0f)), m_B(fmin(fmax(b / 255.0f, 0.0f), 1.0f)), m_A(fmin(fmax(a / 255.0f, 0.0f), 1.0f)) { }

		// Getters
		inline float& r() { return m_R; }
		inline float& g() { return m_G; }
		inline float& b() { return m_B; }
		inline float& a() { return m_A; }
		inline const float& r() const { return m_R; }
		inline const float& g() const { return m_G; }
		inline const float& b() const { return m_B; }
		inline const float& a() const { return m_A; }

		// Setters
		inline colorRGBA& r(float r) { m_R = fmin(fmax(r, 0.0f), 1.0f); return *this; }
		inline colorRGBA& g(float g) { m_G = fmin(fmax(g, 0.0f), 1.0f); return *this; }
		inline colorRGBA& b(float b) { m_B = fmin(fmax(b, 0.0f), 1.0f); return *this; }
		inline colorRGBA& a(float a) { m_A = fmin(fmax(a, 0.0f), 1.0f); return *this; }
		inline colorRGBA& r(int r) { m_R = fmin(fmax(r / 255.0f, 0.0f), 1.0f); return *this; }
		inline colorRGBA& g(int g) { m_G = fmin(fmax(g / 255.0f, 0.0f), 1.0f); return *this; }
		inline colorRGBA& b(int b) { m_B = fmin(fmax(b / 255.0f, 0.0f), 1.0f); return *this; }
		inline colorRGBA& a(int a) { m_A = fmin(fmax(a / 255.0f, 0.0f), 1.0f); return *this; }

		// Operators
		inline colorRGBA operator+ (const colorRGBA& other) const { return colorRGBA(fmin(fmax(m_R + other.m_R, 0.0f), 1.0f), fmin(fmax(m_G + other.m_G, 0.0f), 1.0f), fmin(fmax(m_B + other.m_B, 0.0f), 1.0f), fmin(fmax(m_A + other.m_A, 0.0f), 1.0f)); }
		inline colorRGBA operator- (const colorRGBA& other) const { return colorRGBA(fmin(fmax(m_R - other.m_R, 0.0f), 1.0f), fmin(fmax(m_G - other.m_G, 0.0f), 1.0f), fmin(fmax(m_B - other.m_B, 0.0f), 1.0f), fmin(fmax(m_A - other.m_A, 0.0f), 1.0f)); }
		inline colorRGBA operator* (float scalar) const { return colorRGBA(fmin(fmax(m_R * scalar, 0.0f), 1.0f), fmin(fmax(m_G * scalar, 0.0f), 1.0f), fmin(fmax(m_B * scalar, 0.0f), 1.0f), fmin(fmax(m_A * scalar, 0.0f), 1.0f)); }
		inline colorRGBA operator/ (float scalar) const { return colorRGBA(fmin(fmax(m_R / scalar, 0.0f), 1.0f), fmin(fmax(m_G / scalar, 0.0f), 1.0f), fmin(fmax(m_B / scalar, 0.0f), 1.0f), fmin(fmax(m_A / scalar, 0.0f), 1.0f)); }
	};

	typedef colorRGBA colRGBA, cRGBA;
}

#endif
