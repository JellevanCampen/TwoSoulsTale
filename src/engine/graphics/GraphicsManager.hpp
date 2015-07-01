#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICSMANAGER_H
#define ENGINE_GRAPHICS_GRAPHICSMANAGER_H

#include "glew\glew.h"
#include "glfw\glfw3.h"

#include "../input/InputManager.hpp" // InputManager to make the callback hookup a friend function
#include "../resources/ResourceManager.hpp" // Resourcemanager for managing graphics resources
#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "../common/utility/VectorTypes.hpp" // For representing positions
#include "../common/utility/MatrixTypes.hpp" // For representing transformation matrices
#include "../common/utility/TransformTypes.hpp" // For representing a 3D transform
#include "../common/utility/IntervalTypes.hpp" // For representing a rectangle
#include <string> // For representing filenames and the window title

namespace Engine{
	class GraphicsManager : public Singleton<GraphicsManager>{

	public:

		// Initializes GLEW, GLFW and creates a window for rendering
		void Initialize();

		// Destroys the window for rendering and GLEW and GLFW
		void Terminate();

		// Swaps the buffers of the main window
		void SwapWindowBuffers();

		////////////////////////////////////////////////////////////////
		// Primitives                                                 //
		////////////////////////////////////////////////////////////////

		// Draws a line
		void DrawLine(f2 p1, f2 p2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f));
		inline void DrawLine(d2 p1, d2 p2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawLine(f2(p1.x(), p1.y()), f2(p2.x(), p2.y()), color); };

		// Draws a rectangle
		void DrawRectangle(f2 p1, f2 p2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f));

		// Draws a rectangle
		inline void DrawRectangle(aabb2Df rect, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawRectangle(f2(rect.x1(), rect.y1()), f2(rect.x2(), rect.y2()), color); }

		////////////////////////////////////////////////////////////////
		// Sprite sheets                                              //
		////////////////////////////////////////////////////////////////

		// Draws a frame of the specified sprite sheet
		void DrawSpriteSheetFrame(SpriteSheet spriteSheet, unsigned int frame, double x, double y, double z);

		// Draws a frame of the specified sprite sheet using the specified transformation
		void DrawSpriteSheetFrameTransformed(SpriteSheet spriteSheet, unsigned int frame, double x, double y, double z, double rotation, double scaleX, double scaleY);

		// Draws a frame of the specified sprite sheet using the specified transformation (transform 2D)
		inline void DrawSpriteSheetFrameTransformed(SpriteSheet spriteSheet, unsigned int frame, transform2D transform, float z = 0.0f)
		{
			DrawSpriteSheetFrameTransformed(spriteSheet, frame, transform.t().x(), transform.t().y(), z, transform.r(), transform.s().x(), transform.s().y());
		}

		// Draws a frame of the specified sprite sheet using the specified transformation (transform 3D)
		inline void DrawSpriteSheetFrameTransformed(SpriteSheet spriteSheet, unsigned int frame, transform3D transform)
		{
			DrawSpriteSheetFrameTransformed(spriteSheet, frame, transform.t().x(), transform.t().y(), transform.t().z(), transform.r().z(), transform.s().x(), transform.s().y());
		}

	private:

		// Settings for the window
		int m_WindowWidth = 256 * 4;
		int m_WindowHeight = 240 * 4;
		std::string m_WindowTitle = "Two Souls Tale";

		// The GLFW window object corresponding to the main window
		GLFWwindow* m_Window;

		// Shaders
		GLuint m_ShaderSpriteSheet;
		GLuint m_ShaderSpriteSheet_uTransparancyColor;
		GLuint m_ShaderSpriteSheet_uSpriteUV1;
		GLuint m_ShaderSpriteSheet_uSpriteUV2;
		GLuint m_ShaderSpriteSheet_uMatModel;
		GLuint m_ShaderSpriteSheet_uMatView;
		GLuint m_ShaderSpriteSheet_uMatProjection;

		GLuint m_ShaderLine;
		GLuint m_ShaderLine_uColor;
		GLuint m_ShaderLine_uStart;
		GLuint m_ShaderLine_uEnd;
		GLuint m_ShaderLine_uMatView;
		GLuint m_ShaderLine_uMatProjection;
		GLuint m_ShaderLine_VAO;
		GLuint m_ShaderLine_VBO;

		GLuint m_ShaderRectangle;
		GLuint m_ShaderRectangle_uColor;
		GLuint m_ShaderRectangle_uBottomLeft;
		GLuint m_ShaderRectangle_uTopRight;
		GLuint m_ShaderRectangle_uMatView;
		GLuint m_ShaderRectangle_uMatProjection;
		GLuint m_ShaderRectangle_VAO;
		GLuint m_ShaderRectangle_VBO;

		// Initializes GLFW
		bool InitializeGLFW();

		// Terminates GLFW
		void TerminateGLFW();

		// Initializes GLEW
		bool InitializeGLEW();

		// Terminates GLEW
		void TerminateGLEW();

		// Initializes standard shader programs
		void InitializeShaderPrograms();

		// Destroys standard shader programs
		void TerminateShaderPrograms();

		// Initializes standard buffers
		void InitializeBuffers();

		// Destroys standard buffers
		void TerminateBuffers();

		// GLFW error callback
		static void GLFWErrorCallback(int error, const char* description);

		// Loads and compiles a shader program
		GLuint LoadShaderProgram(std::string vertexShader, std::string fragmentShader);

		// Loads and compiles a single shader stage
		GLuint LoadShaderStage(std::string filename, GLenum shaderStage);

		// Path to the shaders
		std::string m_ShaderPath;

		////////////////////////////////////////////////////////////////
		// Camera													  //
		////////////////////////////////////////////////////////////////

		// Camera focal position
		f2 m_CameraPosition;

		// Camera zoom factor
		float m_CameraZoom;

		// Cached version of the view matrix
		mat4f m_CameraViewMatrix;

		// Whether or not the view matrix should be recalculated
		bool m_CameraViewMatrixDirty;

		// Cached version of the projection matrix
		mat4f m_CameraProjectionMatrix;

		// Whether or not the projection matrix should be recalculated
		bool m_CameraProjectionMatrixDirty;
		
		// Near z-plane
		const float m_ZNear = -1000.0f;

		// Far z-plane
		const float m_ZFar = 1000.0f;

	public:

		// Sets the camera position
		void SetCameraPosition(f2 position);

		// Gets the camera position
		f2 GetCameraPosition();

		// Sets the camera zoom
		void SetCameraZoom(float zoom);

		// Gets the camera zoom
		float GetCameraZoom();

		// Gets the camera's view matrix
		const mat4f& GetCameraViewMatrix();

		// Gets the camera's projection matrix
		const mat4f& GetCameraProjectionMatrix();

		friend class InputManager;

	};
}

#endif