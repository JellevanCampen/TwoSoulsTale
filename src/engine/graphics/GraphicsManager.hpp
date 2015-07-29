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
#include "../common/utility/ColorTypes.hpp" // For representing colors
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
		// Shaders, uniform locations and buffers					  //
		////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////// Line Shader
		GLuint m_ShaderLine;
		GLuint m_ShaderLine_uColor;
		GLuint m_ShaderLine_uStart;
		GLuint m_ShaderLine_uEnd;
		GLuint m_ShaderLine_uMatView;
		GLuint m_ShaderLine_uMatProjection;
		GLuint m_ShaderLine_VAO;
		GLuint m_ShaderLine_VBO;

		/////////////////////////////////////////////// Rectangle Shader
		GLuint m_ShaderRectangle;
		GLuint m_ShaderRectangle_uColor;
		GLuint m_ShaderRectangle_uBottomLeft;
		GLuint m_ShaderRectangle_uTopRight;
		GLuint m_ShaderRectangle_uMatView;
		GLuint m_ShaderRectangle_uMatProjection;
		GLuint m_ShaderRectangle_VAO;
		GLuint m_ShaderRectangle_VBO;

		////////////////////////////////////////////////// Circle Shader
		GLuint m_ShaderCircle;
		GLuint m_ShaderCircle_uColor;
		GLuint m_ShaderCircle_uPosition;
		GLuint m_ShaderCircle_uRadius;
		GLuint m_ShaderCircle_uMatView;
		GLuint m_ShaderCircle_uMatProjection;
		GLuint m_ShaderCircle_VAO;
		GLuint m_ShaderCircle_VBO;

		//////////////////////////////////////////// Sprite Sheet Shader
		GLuint m_ShaderSpriteSheet;
		GLuint m_ShaderSpriteSheet_uTransparancyColor;
		GLuint m_ShaderSpriteSheet_uPosBottomLeft;
		GLuint m_ShaderSpriteSheet_uPosTopRight;
		GLuint m_ShaderSpriteSheet_uUVBottomLeft;
		GLuint m_ShaderSpriteSheet_uUVTopRight;
		GLuint m_ShaderSpriteSheet_uMatModel;
		GLuint m_ShaderSpriteSheet_uMatView;
		GLuint m_ShaderSpriteSheet_uMatProjection;
		GLuint m_ShaderSpriteSheet_VAO;
		GLuint m_ShaderSpriteSheet_VBO;

		//////////////////////////////////////// Bitmap Font Text Shader
		GLuint m_ShaderTextBitmapFont;
		GLuint m_ShaderTextBitmapFont_uGlyphSize;
		GLuint m_ShaderTextBitmapFont_uGlyphOrigin;
		GLuint m_ShaderTextBitmapFont_uSpriteSheetSize;
		GLuint m_ShaderTextBitmapFont_uSpriteSheetGridSize;
		GLuint m_ShaderTextBitmapFont_uSpriteSheetSeparation;
		GLuint m_ShaderTextBitmapFont_uSpriteSheetOrigin;
		GLuint m_ShaderTextBitmapFont_uMatModel;
		GLuint m_ShaderTextBitmapFont_uMatView;
		GLuint m_ShaderTextBitmapFont_uMatProjection;
		GLuint m_ShaderTextBitmapFont_uSpriteSampler;
		GLuint m_ShaderTextBitmapFont_uColor;
		GLuint m_ShaderTextBitmapFont_VAO;
		GLuint m_ShaderTextBitmapFont_VBO;
		GLuint m_ShaderTextBitmapFont_VBO_CharacterPosition;
		GLuint m_ShaderTextBitmapFont_VBO_GlyphIndex;

		/////////////////////////////// Advanced Bitmap Font Text Shader
		GLuint m_ShaderTextBitmapFontAdvanced;
		GLuint m_ShaderTextBitmapFontAdvanced_uGlyphSize;
		GLuint m_ShaderTextBitmapFontAdvanced_uGlyphOrigin;
		GLuint m_ShaderTextBitmapFontAdvanced_uSpriteSheetSize;
		GLuint m_ShaderTextBitmapFontAdvanced_uSpriteSheetGridSize;
		GLuint m_ShaderTextBitmapFontAdvanced_uSpriteSheetSeparation;
		GLuint m_ShaderTextBitmapFontAdvanced_uSpriteSheetOrigin;
		GLuint m_ShaderTextBitmapFontAdvanced_uMatModel;
		GLuint m_ShaderTextBitmapFontAdvanced_uMatView;
		GLuint m_ShaderTextBitmapFontAdvanced_uMatProjection;
		GLuint m_ShaderTextBitmapFontAdvanced_uSpriteSampler;
		GLuint m_ShaderTextBitmapFontAdvanced_VAO;
		GLuint m_ShaderTextBitmapFontAdvanced_VBO;
		GLuint m_ShaderTextBitmapFontAdvanced_VBO_CharacterPosition;
		GLuint m_ShaderTextBitmapFontAdvanced_VBO_GlyphIndex;
		GLuint m_ShaderTextBitmapFontAdvanced_VBO_GlyphColor;

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
		// Primitive drawing                                          //
		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////// Lines

		// Draws a line
		template<typename valuetype>
		void DrawLine(ray2D<valuetype> line, colorRGBA color = colorRGBA())
		{
			// Use the sprite sheet shader program
			glUseProgram(m_ShaderLine);

			// Pass the start- and endpoints of the line
			glUniform2f(m_ShaderLine_uStart, line.x1(), line.y1());
			glUniform2f(m_ShaderLine_uEnd, line.x2(), line.y2());

			// Pass the color of the line
			glUniform4f(m_ShaderLine_uColor, color.r(), color.g(), color.b(), color.a());

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
		inline void DrawLine(vector2D<valuetype> p1, vector2D<valuetype> p2, colorRGBA color = colorRGBA()) { DrawLine(ray2D<valuetype>(p1, p2), color); }

		// Draws a line
		template<typename valuetype>
		inline void DrawLine(valuetype x1, valuetype x2, valuetype y1, valuetype y2, colorRGBA color = colorRGBA()) { DrawLine(ray2D<valuetype>(x1, x2, y1, y2), color); }

		///////////////////////////////////////////////////// Rectangles

		// Draws a rectangle
		template<typename valuetype>
		void DrawRectangle(interval2D<valuetype> rectangle, colorRGBA color = colorRGBA())
		{
			// Use the sprite sheet shader program
			glUseProgram(m_ShaderRectangle);

			// Pass the start- and endpoints of the line
			glUniform2f(m_ShaderRectangle_uBottomLeft, rectangle.x1(), rectangle.y1());
			glUniform2f(m_ShaderRectangle_uTopRight, rectangle.x2(), rectangle.y2());

			// Pass the color of the line
			glUniform4f(m_ShaderRectangle_uColor, color.r(), color.g(), color.b(), color.a());

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
		inline void DrawRectangle(vector2D<valuetype> p1, vector2D<valuetype> p2, colorRGBA color = colorRGBA()) { DrawRectangle(interval2D<valuetype>(p1, p2), color); }

		// Draws a rectangle
		template<typename valuetype>
		inline void DrawRectangle(valuetype x1, valuetype x2, valuetype y1, valuetype y2, colorRGBA color = colorRGBA()) { DrawRectangle(interval2D<valuetype>(x1, x2, y1, y2), color); }

		//////////////////////////////////////////////////////// Circles

		template<typename valuetype>
		void DrawCircle(circle<valuetype> circle, colorRGBA color = colorRGBA())
		{
			// Use the sprite sheet shader program
			glUseProgram(m_ShaderCircle);

			// Pass the start- and endpoints of the line
			glUniform2f(m_ShaderCircle_uPosition, circle.x(), circle.y());
			glUniform1f(m_ShaderCircle_uRadius, circle.r());

			// Pass the color of the line
			glUniform4f(m_ShaderCircle_uColor, color.r(), color.g(), color.b(), color.a());

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
		inline void DrawCircle(vector2D<valuetype> p, valuetype r, colorRGBA color = colorRGBA()) { DrawCircle(circle<valuetype>(p, r), color); }

		// Draws a circle
		template<typename valuetype>
		inline void DrawCircle(valuetype x, valuetype y, valuetype r, colorRGBA color = colorRGBA()) { DrawCircle(circle<valuetype>(x, y, r), color); }

		////////////////////////////////////////////////////////////////
		// Sprite sheet drawing                                       //
		////////////////////////////////////////////////////////////////

		// Draws a frame of the specified sprite sheet
		void DrawSpriteSheetFrame(SpriteSheet spriteSheet, unsigned int frame, f3 translation, float rotation = 0.0f, f2 scale = f2(1.0f, 1.0f));

		// Draws a frame of the specified sprite sheet
		inline void DrawSpriteSheetFrame(SpriteSheet spriteSheet, unsigned int frame, transform2D transform, float z = 0.0f)
		{
			DrawSpriteSheetFrame(spriteSheet, frame, f3(transform.t().xy(), z), transform.r(), transform.s());
		}

		////////////////////////////////////////////////////////////////
		// Text drawing												  //
		////////////////////////////////////////////////////////////////

		// Draws a text message using the specified bitmap font
		void DrawText(std::string text, BitmapFont font, transform2D transform, float z = 0.0f, colorRGBA color = colorRGBA());

		// Draws a text message using the specified bitmap font (supports color tags)
		void DrawTextAdvanced(std::string text, BitmapFont font, transform2D transform, float z = 0.0f, colorRGBA defaultColor = colorRGBA());

		friend class InputManager;

	};
}

#endif