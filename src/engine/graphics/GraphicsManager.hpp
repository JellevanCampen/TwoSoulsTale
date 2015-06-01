#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICSMANAGER_H
#define ENGINE_GRAPHICS_GRAPHICSMANAGER_H

#include "glew\glew.h"
#include "glfw\glfw3.h"
#include <string>

#include "../input/InputManager.hpp" // InputManager to make the callback hookup a friend function
#include "../resources/ResourceManager.hpp" // Resourcemanager for managing graphics resources
#include "../common/patterns/Singleton.hpp" // Singleton pattern

namespace Engine{
	class GraphicsManager : public Singleton<GraphicsManager>{

	public:

		// Initializes GLEW, GLFW and creates a window for rendering
		void Initialize();

		// Destroys the window for rendering and GLEW and GLFW
		void Terminate();

		// Swaps the buffers of the main window
		void SwapWindowBuffers();

		/**************************************************************/
		/* Sprite sheets                                              */
		/**************************************************************/

		// Draws a frame of the specified sprite sheet
		void DrawSpriteSheetFrame(SpriteSheet spriteSheet, unsigned int frame, double x, double y, double z);

		// Draws a frame of the specified sprite sheet using the specified transformation
		void DrawSpriteSheetFrameTransformed(SpriteSheet spriteSheet, unsigned int frame, double x, double y, double z, double rotation, double scaleX, double scaleY);

	private:

		// Settings for the window
		int m_WindowWidth = 256 * 4;
		int m_WindowHeight = 240 * 4;
		std::string m_WindowTitle = "Two Souls Tale";

		// The GLFW window object corresponding to the main window
		GLFWwindow* m_Window;

		// Shaders
		GLuint m_ShaderSpriteSheet;
		GLuint m_ShaderSpriteSheet_uSpriteUV1;
		GLuint m_ShaderSpriteSheet_uSpriteUV2;
		GLuint m_ShaderSpriteSheet_uMatModel;
		GLuint m_ShaderSpriteSheet_uMatView;

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

		// GLFW error callback
		static void GLFWErrorCallback(int error, const char* description);

		// Loads and compiles a shader program
		GLuint LoadShaderProgram(std::string vertexShader, std::string fragmentShader);

		// Loads and compiles a single shader stage
		GLuint LoadShaderStage(std::string filename, GLenum shaderStage);

		// Path to the shaders
		std::string m_ShaderPath;

		friend class InputManager;

	};
}

#endif