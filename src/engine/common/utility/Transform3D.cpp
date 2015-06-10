#include "Transform3D.hpp"

#include "glm\gtc\matrix_transform.hpp" // For calculating the transformation matrix

// Constructor (from vectors)
Engine::Transform3D::Transform3D(f3 translation, f3 rotation, f3 scale, RotationOrder rotationOrder)
{
	m_Translation = translation;
	m_Rotation = rotation;
	m_Scale = scale;

	m_RotationOrder = rotationOrder;

	m_TransformationMatrixIsDirty = true;
}

// Constructor (from individual components)
Engine::Transform3D::Transform3D(
	float translationX, float translationY, float translationZ,
	float rotationX, float rotationY, float rotationZ,
	float scaleX, float scaleY, float scaleZ,
	RotationOrder rotationOrder)
{
	m_Translation.x = translationX;
	m_Translation.y = translationY;
	m_Translation.z = translationZ;

	m_Rotation.x = rotationX;
	m_Rotation.y = rotationY;
	m_Rotation.z = rotationZ;

	m_Scale.x = scaleX;
	m_Scale.y = scaleY;
	m_Scale.z = scaleZ;

	m_RotationOrder = rotationOrder;

	m_TransformationMatrixIsDirty = true;
}

////////////////////////////////////////////////////////////////
// Transformation component getters and setters               //
////////////////////////////////////////////////////////////////

// Gets the translation component
Engine::f3 Engine::Transform3D::GetTranslation() const
{
	return m_Translation;
}

// Sets the translation component (from a vector)
void Engine::Transform3D::SetTranslation(f3 translation)
{
	m_Translation = translation;
}

// Sets the translation component (from individual components)
void Engine::Transform3D::SetTranslation(float x, float y, float z)
{
	m_Translation.x = x;
	m_Translation.y = y;
	m_Translation.z = z;
}

// Gets the rotation component
Engine::f3 Engine::Transform3D::GetRotation() const
{
	return m_Rotation;
}

// Sets the rotation component (from a vector)
void Engine::Transform3D::SetRotation(f3 rotation)
{
	m_Rotation = rotation;
}

// Sets the rotation component (from individual components)
void Engine::Transform3D::SetRotation(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

// Gets the scale component
Engine::f3 Engine::Transform3D::GetScale() const
{
	return m_Scale;
}

// Sets the scale component (from a vector)
void Engine::Transform3D::SetScale(f3 scale)
{
	m_Scale = scale;
}

// Sets the scale component (from individual components)
void Engine::Transform3D::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

////////////////////////////////////////////////////////////////
// Transformation matrix calculation                          //
////////////////////////////////////////////////////////////////

// Gets the transformation matrix for this transform
const Engine::mat4f& Engine::Transform3D::GetTransformationMatrix()
{
	if (!m_TransformationMatrixIsDirty)
	{
		return m_TransformationMatrix;
	}

	m_TransformationMatrix.Identity();

	if (m_Translation != f3(0.0f, 0.0f, 0.0f))
	{
		m_TransformationMatrix = glm::translate(m_TransformationMatrix, m_Translation);
	}

	if (m_Rotation != f3(0.0f, 0.0f, 0.0f))
	{
		switch (m_RotationOrder)
		{
			
		}

		m_TransformationMatrix = glm::rotate(m_TransformationMatrix, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_TransformationMatrix = glm::rotate(m_TransformationMatrix, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		m_TransformationMatrix = glm::rotate(m_TransformationMatrix, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	
	if (m_Scale != f3(1.0f, 1.0f, 1.0f))
	{
		m_TransformationMatrix = glm::scale(m_TransformationMatrix, m_Scale);
	}
	
	return m_TransformationMatrix;
}