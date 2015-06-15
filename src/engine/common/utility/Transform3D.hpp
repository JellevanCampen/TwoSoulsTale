#ifndef ENGINE_COMMON_UTILITY_TRANSFORM3D_H
#define ENGINE_COMMON_UTILITY_TRANSFORM3D_H

#include "VectorTypes.hpp" // For representing transformation components as vectors
#include "MatrixTypes.hpp" // For representing the transformation matrix

namespace Engine
{
	class Transform3D
	{

	public:

		// Struct for representing the order of rotations
		enum class RotationOrder
		{
			XYZ,
			XZY,
			YXZ,
			YZX,
			ZXY,
			ZYX
		};

	public:

		// Constructor (from vectors)
		Transform3D(
			f3 translation = f3(0.0f, 0.0f, 0.0f),
			f3 rotation = f3(0.0f, 0.0f, 0.0f), 
			f3 scale = f3(1.0f, 1.0f, 1.0f),
			RotationOrder rotationOrder = RotationOrder::ZXY);

		// Constructor (from individual components)
		Transform3D(
			float translationX, float translationY, float translationZ,
			float rotationX = 0.0f, float rotationY = 0.0f, float rotationZ = 0.0f,
			float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f, 
			RotationOrder rotationOrder = RotationOrder::ZXY);

		////////////////////////////////////////////////////////////////
		// Transformation component getters and setters               //
		////////////////////////////////////////////////////////////////

		// Gets the translation component
		f3 GetTranslation() const;

		// Sets the translation component (from a vector)
		void SetTranslation(f3 translation);

		// Sets the translation component (from individual components)
		void SetTranslation(float x, float y, float z);

		// Gets the rotation component
		f3 GetRotation() const;

		// Sets the rotation component (from a vector)
		void SetRotation(f3 rotation);

		// Sets the rotation component (from individual components)
		void SetRotation(float x, float y, float z);

		// Gets the scale component
		f3 GetScale() const;

		// Sets the scale component (from a vector)
		void SetScale(f3 scale);

		// Sets the scale component (from individual components)
		void SetScale(float x, float y, float z);

		////////////////////////////////////////////////////////////////
		// Transformation matrix calculation                          //
		////////////////////////////////////////////////////////////////

		// Gets the transformation matrix for this transform
		const mat4f& GetTransformationMatrix();

	private:

		// Translation component
		f3 m_Translation;

		// Rotation component
		f3 m_Rotation;

		// Scale component
		f3 m_Scale;

		// Order of rotations
		RotationOrder m_RotationOrder;

		// Transformation matrix
		mat4f m_TransformationMatrix;

		// Dirty flag for the transformation matrix
		bool m_TransformationMatrixIsDirty;

	};
}

#endif
