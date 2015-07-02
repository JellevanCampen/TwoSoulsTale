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
#include "../common/utility/ShapeTypes.hpp" // For representing primitive shapes
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

	private:

		// Settings for the window
		int m_WindowWidth = 256 * 4;
		int m_WindowHeight = 240 * 4;
		std::string m_WindowTitle = "Two Souls Tale";

		// The GLFW window object corresponding to the main window
		GLFWwindow* m_Window;

		// Settings for primitives
		static const size_t s_NumCircleSegments = 32;

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

		GLuint m_ShaderCircle;
		GLuint m_ShaderCircle_uColor;
		GLuint m_ShaderCircle_uPosition;
		GLuint m_ShaderCircle_uRadius;
		GLuint m_ShaderCircle_uMatView;
		GLuint m_ShaderCircle_uMatProjection;
		GLuint m_ShaderCircle_VAO;
		GLuint m_ShaderCircle_VBO;

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

	public:

		////////////////////////////////////////////////////////////////
		// Primitives                                                 //
		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////// Lines

		// Draws a line
		template<typename valuetype>
		void DrawLine(ray2D<valuetype> line, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f))
		{
			// Use the sprite sheet shader program
			glUseProgram(m_ShaderLine);

			// Pass the start- and endpoints of the line
			glUniform2f(m_ShaderLine_uStart, line.x1(), line.y1());
			glUniform2f(m_ShaderLine_uEnd, line.x2(), line.y2());

			// Pass the color of the line
			glUniform4f(m_ShaderLine_uColor, color.x(), color.y(), color.z(), color.w());

			// Pass the transformation matrices
			glUniformMatrix4fv(m_ShaderLine_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
			glUniformMatrix4fv(m_ShaderLine_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

			// Draw the line
			glBindVertexArray(m_ShaderLine_VAO);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		}

		// Draws a line
		template<typename valuetype>
		inline void DrawLine(vector2D<valuetype> p1, vector2D<valuetype> p2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawLine(ray2D<valuetype>(p1, p2), color); }

		// Draws a line
		template<typename valuetype>
		inline void DrawLine(valuetype x1, valuetype x2, valuetype y1, valuetype y2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawLine(ray2D<valuetype>(x1, x2, y1, y2), color); }

		///////////////////////////////////////////////////// Rectangles

		// Draws a rectangle
		template<typename valuetype>
		void DrawRectangle(rectangle<valuetype> rectangle, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f))
		{
			// Use the sprite sheet shader program
			glUseProgram(m_ShaderRectangle);

			// Pass the start- and endpoints of the line
			glUniform2f(m_ShaderRectangle_uBottomLeft, rectangle.x1(), rectangle.y1());
			glUniform2f(m_ShaderRectangle_uTopRight, rectangle.x2(), rectangle.y2());

			// Pass the color of the line
			glUniform4f(m_ShaderRectangle_uColor, color.x(), color.y(), color.z(), color.w());

			// Pass the transformation matrices
			glUniformMatrix4fv(m_ShaderRectangle_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
			glUniformMatrix4fv(m_ShaderRectangle_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

			// Draw the line
			glBindVertexArray(m_ShaderRectangle_VAO);
			glDrawArrays(GL_LINE_LOOP, 0, 4);
			glBindVertexArray(0);
		}

		// Draws a rectangle
		template<typename valuetype>
		inline void DrawRectangle(vector2D<valuetype> p1, vector2D<valuetype> p2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawRectangle(rectangle<valuetype>(p1, p2), color); }

		// Draws a rectangle
		template<typename valuetype>
		inline void DrawRectangle(valuetype x1, valuetype x2, valuetype y1, valuetype y2, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawRectangle(rectangle<valuetype>(x1, x2, y1, y2), color); }

		//////////////////////////////////////////////////////// Circles

		template<typename valuetype>
		void DrawCircle(circle<valuetype> circle, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f))
		{
			// Use the sprite sheet shader program
			glUseProgram(m_ShaderCircle);

			// Pass the start- and endpoints of the line
			glUniform2f(m_ShaderCircle_uPosition, circle.x(), circle.y());
			glUniform1f(m_ShaderCircle_uRadius, circle.r());

			// Pass the color of the line
			glUniform4f(m_ShaderCircle_uColor, color.x(), color.y(), color.z(), color.w());

			// Pass the transformation matrices
			glUniformMatrix4fv(m_ShaderCircle_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
			glUniformMatrix4fv(m_ShaderCircle_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

			// Draw the line
			glBindVertexArray(m_ShaderCircle_VAO);
			glDrawArrays(GL_LINE_LOOP, 0, s_NumCircleSegments);
			glBindVertexArray(0);
		}

		// Draws a circle
		template<typename valuetype>
		inline void DrawCircle(vector2D<valuetype> p, valuetype r, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawCircle(circle<valuetype>(p, r), color); }

		// Draws a circle
		template<typename valuetype>
		inline void DrawCircle(valuetype x, valuetype y, valuetype r, f4 color = f4(0.0f, 0.0f, 0.0f, 1.0f)) { DrawCircle(circle<valuetype>(x, y, r), color); }

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

		friend class InputManager;

	};
}

#endif