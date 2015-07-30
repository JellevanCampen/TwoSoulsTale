#include "GraphicsManager.hpp"

#include "../debugging/LoggingManager.hpp" // Logging manager for reporting statuses
#include "SpriteSheetResource.hpp" // Sprite sheet resources
#include "../timing/TimingManager.hpp" // For sending the time to shaders for animation

#include <glm.hpp> // For vector and matrix data types
#include <glm\gtc\matrix_transform.hpp> // For matrix transforms
#include <glm\gtc\type_ptr.hpp> // For retrieving a pointer to glm data

#include <fstream> // For reading shaders from file
#include <sstream> // String streams for parsing shader files

// Initializes GLFW, GLEW and creates a window for rendering
void Engine::GraphicsManager::Initialize()
{
	// Specify the shader path
	m_ShaderPath = "../shaders/";

	// Initialize GLFW (for window creation and event handling) and GLEW (for crossplatform OpenGL compatibility)
	InitializeGLFW();
	InitializeGLEW();

	// Hook up the GLFW error callback function
	glfwSetErrorCallback(GLFWErrorCallback);

	// Load standard shader programs
	InitializeShaderPrograms();

	// Load standard buffers
	InitializeBuffers();

	// Initialize OpenGL settings
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Initialize camera settings
	m_CameraPosition = f2(m_WindowWidth / 2.0f, m_WindowHeight / 2.0f);
	m_CameraZoom = 1.0f;
	m_CameraViewMatrixDirty = true;
	m_CameraProjectionMatrixDirty = true;
}

// Destroys the window for rendering and GLEW and GLFW
void Engine::GraphicsManager::Terminate()
{
	// Destroy standard shader programs
	TerminateShaderPrograms();

	TerminateGLEW();
	TerminateGLFW();
}

// Swaps the buffers of the main window
void Engine::GraphicsManager::SwapWindowBuffers()
{
	glfwSwapBuffers(m_Window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Initializes GLFW
bool Engine::GraphicsManager::InitializeGLFW()
{
	if (!glfwInit())
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to initialize GLFW");
		return false;
	}

	// Set the window hints for the creation of the main window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE); // Prevent screen tearing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Prevent the use of deprecated OpenGL functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Prevent the use of non-core functionality

	// Create the window (in non-fullscreen mode, with no shared resources)
	m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowTitle.c_str(), NULL, NULL);

	// Use the OpenGL context of the main window for future rendering
	glfwMakeContextCurrent(m_Window);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

// Terminates GLFW
void Engine::GraphicsManager::TerminateGLFW()
{
	// Destroy the main window
	glfwDestroyWindow(m_Window);

	// Terminate GLFW
	glfwTerminate();
}

// Initializes GLEW
bool Engine::GraphicsManager::InitializeGLEW()
{
	glewExperimental = true; // Required for OpenGL core profile

	if (glewInit() != GLEW_OK)
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to initialize GLEW");
		return false;
	}

	return true;
}

// Terminates GLEW
void Engine::GraphicsManager::TerminateGLEW()
{

}

// GLFW error callback
void Engine::GraphicsManager::GLFWErrorCallback(int error, const char* description)
{
	LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "GLFW error " + std::to_string(error) + ": " + std::string(description));
}

// Initializes standard shader programs
void Engine::GraphicsManager::InitializeShaderPrograms()
{
	//////////////////////////////////////////////////// Line Shader
	m_ShaderLine = LoadShaderProgram("line", "flatColor");
	m_ShaderLine_uColor = glGetUniformLocation(m_ShaderLine, "uColor");
	m_ShaderLine_uStart = glGetUniformLocation(m_ShaderLine, "uStart");
	m_ShaderLine_uEnd = glGetUniformLocation(m_ShaderLine, "uEnd");
	m_ShaderLine_uMatView = glGetUniformLocation(m_ShaderLine, "matView");
	m_ShaderLine_uMatProjection = glGetUniformLocation(m_ShaderLine, "matProjection");

	/////////////////////////////////////////////// Rectangle Shader
	m_ShaderRectangle = LoadShaderProgram("rectangle", "flatColor");
	m_ShaderRectangle_uColor = glGetUniformLocation(m_ShaderRectangle, "uColor");
	m_ShaderRectangle_uBottomLeft = glGetUniformLocation(m_ShaderRectangle, "uBottomLeft");
	m_ShaderRectangle_uTopRight = glGetUniformLocation(m_ShaderRectangle, "uTopRight");
	m_ShaderRectangle_uMatView = glGetUniformLocation(m_ShaderRectangle, "matView");
	m_ShaderRectangle_uMatProjection = glGetUniformLocation(m_ShaderRectangle, "matProjection");

	////////////////////////////////////////////////// Circle Shader
	m_ShaderCircle = LoadShaderProgram("circle", "flatColor");
	m_ShaderCircle_uColor = glGetUniformLocation(m_ShaderCircle, "uColor");
	m_ShaderCircle_uPosition = glGetUniformLocation(m_ShaderCircle, "uPosition");
	m_ShaderCircle_uRadius = glGetUniformLocation(m_ShaderCircle, "uRadius");
	m_ShaderCircle_uMatView = glGetUniformLocation(m_ShaderCircle, "matView");
	m_ShaderCircle_uMatProjection = glGetUniformLocation(m_ShaderCircle, "matProjection");

	//////////////////////////////////////////// Sprite Sheet Shader
	m_ShaderSpriteSheet = LoadShaderProgram("spritesheet", "spritesheet");
	m_ShaderSpriteSheet_uTransparancyColor = glGetUniformLocation(m_ShaderSpriteSheet, "uTransparancyColor");
	m_ShaderSpriteSheet_uPosBottomLeft = glGetUniformLocation(m_ShaderSpriteSheet, "uPosBottomLeft");
	m_ShaderSpriteSheet_uPosTopRight = glGetUniformLocation(m_ShaderSpriteSheet, "uPosTopRight");
	m_ShaderSpriteSheet_uUVBottomLeft = glGetUniformLocation(m_ShaderSpriteSheet, "uUVBottomLeft");
	m_ShaderSpriteSheet_uUVTopRight = glGetUniformLocation(m_ShaderSpriteSheet, "uUVTopRight");
	m_ShaderSpriteSheet_uMatModel = glGetUniformLocation(m_ShaderSpriteSheet, "matModel");
	m_ShaderSpriteSheet_uMatView = glGetUniformLocation(m_ShaderSpriteSheet, "matView");
	m_ShaderSpriteSheet_uMatProjection = glGetUniformLocation(m_ShaderSpriteSheet, "matProjection");

	//////////////////////////////////////// Bitmap Font Text Shader
	m_ShaderTextBitmapFont = LoadShaderProgram("textBitmapFont", "textBitmapFont");
	m_ShaderTextBitmapFont_uGlyphSize = glGetUniformLocation(m_ShaderTextBitmapFont, "uGlyphSize");
	m_ShaderTextBitmapFont_uGlyphOrigin = glGetUniformLocation(m_ShaderTextBitmapFont, "uGlyphOrigin");
	m_ShaderTextBitmapFont_uSpriteSheetSize = glGetUniformLocation(m_ShaderTextBitmapFont, "uSpriteSheetSize");
	m_ShaderTextBitmapFont_uSpriteSheetGridSize = glGetUniformLocation(m_ShaderTextBitmapFont, "uSpriteSheetGridSize");
	m_ShaderTextBitmapFont_uSpriteSheetSeparation = glGetUniformLocation(m_ShaderTextBitmapFont, "uSpriteSheetSeparation");
	m_ShaderTextBitmapFont_uSpriteSheetOrigin = glGetUniformLocation(m_ShaderTextBitmapFont, "uSpriteSheetOrigin");
	m_ShaderTextBitmapFont_uMatModel = glGetUniformLocation(m_ShaderTextBitmapFont, "matModel");
	m_ShaderTextBitmapFont_uMatView = glGetUniformLocation(m_ShaderTextBitmapFont, "matView");
	m_ShaderTextBitmapFont_uMatProjection = glGetUniformLocation(m_ShaderTextBitmapFont, "matProjection");
	m_ShaderTextBitmapFont_uSpriteSampler = glGetUniformLocation(m_ShaderTextBitmapFont, "uSpriteSampler");
	m_ShaderTextBitmapFont_uColor = glGetUniformLocation(m_ShaderTextBitmapFont, "uColor");

	////////////////////////////////Advanced Bitmap Font Text Shader
	m_ShaderTextBitmapFontAdvanced = LoadShaderProgram("textBitmapFontAdvanced", "textBitmapFontAdvanced");
	m_ShaderTextBitmapFontAdvanced_uGlyphSize = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uGlyphSize");
	m_ShaderTextBitmapFontAdvanced_uGlyphOrigin = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uGlyphOrigin");
	m_ShaderTextBitmapFontAdvanced_uSpriteSheetSize = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uSpriteSheetSize");
	m_ShaderTextBitmapFontAdvanced_uSpriteSheetGridSize = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uSpriteSheetGridSize");
	m_ShaderTextBitmapFontAdvanced_uSpriteSheetSeparation = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uSpriteSheetSeparation");
	m_ShaderTextBitmapFontAdvanced_uSpriteSheetOrigin = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uSpriteSheetOrigin");
	m_ShaderTextBitmapFontAdvanced_uTimeSeconds = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uTimeSeconds");
	m_ShaderTextBitmapFontAdvanced_uAnimWaveXYOffset = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimWaveOffset");
	m_ShaderTextBitmapFontAdvanced_uAnimWaveLength = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimWaveLength");
	m_ShaderTextBitmapFontAdvanced_uAnimWaveFrequency = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimWaveFrequency");
	m_ShaderTextBitmapFontAdvanced_uAnimShakeWaveLength = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimShakeWaveLength");
	m_ShaderTextBitmapFontAdvanced_uAnimShakeFrequency = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimShakeFrequency");
	m_ShaderTextBitmapFontAdvanced_uAnimHueCycleWaveLength = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimHueCycleWaveLength");
	m_ShaderTextBitmapFontAdvanced_uAnimHueCycleFrequency = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimHueCycleFrequency");
	m_ShaderTextBitmapFontAdvanced_uAnimIntensityPulseWaveLength = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimIntensityPulseWaveLength");
	m_ShaderTextBitmapFontAdvanced_uAnimIntensityPulseFrequency = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimIntensityPulseFrequency");
	m_ShaderTextBitmapFontAdvanced_uAnimAlphaPulseWaveLength = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimAlphaPulseWaveLength");
	m_ShaderTextBitmapFontAdvanced_uAnimAlphaPulseFrequency = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uAnimAlphaPulseFrequency");
	m_ShaderTextBitmapFontAdvanced_uMatModel = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "matModel");
	m_ShaderTextBitmapFontAdvanced_uMatView = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "matView");
	m_ShaderTextBitmapFontAdvanced_uMatProjection = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "matProjection");
	m_ShaderTextBitmapFontAdvanced_uSpriteSampler = glGetUniformLocation(m_ShaderTextBitmapFontAdvanced, "uSpriteSampler");
}

// Destroys standard shader programs
void Engine::GraphicsManager::TerminateShaderPrograms()
{
	glDeleteProgram(m_ShaderLine);
	glDeleteProgram(m_ShaderRectangle);
	glDeleteProgram(m_ShaderCircle);
	glDeleteProgram(m_ShaderSpriteSheet);
	glDeleteProgram(m_ShaderTextBitmapFont);
	glDeleteProgram(m_ShaderTextBitmapFontAdvanced);
}

// Initializes standard buffers
void Engine::GraphicsManager::InitializeBuffers()
{
	//////////////////////////////////////////////////// Line shader
	glGenVertexArrays(1, &m_ShaderLine_VAO);
	glBindVertexArray(m_ShaderLine_VAO);

	// Generate and bind the vertex buffer
	glGenBuffers(1, &m_ShaderLine_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderLine_VBO);

	// Buffer vertex data
	GLfloat vertexDataLine[2] = { 0.0f, 1.0f };
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(GLfloat), &vertexDataLine[0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position

	/////////////////////////////////////////////// Rectangle shader
	glGenVertexArrays(1, &m_ShaderRectangle_VAO);
	glBindVertexArray(m_ShaderRectangle_VAO);

	// Generate and bind the vertex buffer
	glGenBuffers(1, &m_ShaderRectangle_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderRectangle_VBO);

	// Buffer vertex data
	GLfloat vertexDataRectangle[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), &vertexDataRectangle[0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position

	////////////////////////////////////////////////// Circle shader
	glGenVertexArrays(1, &m_ShaderCircle_VAO);
	glBindVertexArray(m_ShaderCircle_VAO);

	// Generate and bind the vertex buffer
	glGenBuffers(1, &m_ShaderCircle_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderCircle_VBO);

	// Buffer vertex data
	GLfloat vertexDataCircle[s_NumCircleSegments];
	for (int i = 0; i < s_NumCircleSegments; i++) { vertexDataCircle[i] = (float)i / (float)s_NumCircleSegments; }
	glBufferData(GL_ARRAY_BUFFER, s_NumCircleSegments * sizeof(GLfloat), &vertexDataCircle[0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position

	//////////////////////////////////////////// Sprite sheet shader
	glGenVertexArrays(1, &m_ShaderSpriteSheet_VAO);
	glBindVertexArray(m_ShaderSpriteSheet_VAO);

	// Generate and bind the vertex buffer (positions and UVs)
	glGenBuffers(1, &m_ShaderSpriteSheet_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderSpriteSheet_VBO);

	// Buffer vertex data (positions and UVs)
	GLfloat vertexDataSpriteSheet[2 * 6 + 2 * 6] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, ((2 * 6) + (2 * 6)) * sizeof(GLfloat), &vertexDataSpriteSheet[0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position and UVs)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(2 * 6 * sizeof(GLfloat))); // UVs

	//////////////////////////////////////// Bitmap font text shader
	glGenVertexArrays(1, &m_ShaderTextBitmapFont_VAO);
	glBindVertexArray(m_ShaderTextBitmapFont_VAO);

	// Generate and bind the vertex buffer (positions and UVs)
	glGenBuffers(1, &m_ShaderTextBitmapFont_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFont_VBO);

	// Buffer vertex data (positions and UVs)
	GLfloat vertexDataBitmapFont[2 * 6 + 2 * 6] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, ((2 * 6) + (2 * 6)) * sizeof(GLfloat), &vertexDataBitmapFont[0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position and UVs)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(2 * 6 * sizeof(GLfloat))); // UVs

	// Generate and bind the character position buffer (character position)
	glGenBuffers(1, &m_ShaderTextBitmapFont_VBO_CharacterPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFont_VBO_CharacterPosition);

	// Specify the character position attribute (character position)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Character position
	glVertexAttribDivisor(2, 1);

	// Generate and bind the glyph index buffer (glyph index)
	glGenBuffers(1, &m_ShaderTextBitmapFont_VBO_GlyphIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFont_VBO_GlyphIndex);

	// Specify the glyph index attribute (glyph index)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, 0, (void*)(0)); // Glyph position
	glVertexAttribDivisor(3, 1);

	/////////////////////////////// Advanced bitmap font text shader
	glGenVertexArrays(1, &m_ShaderTextBitmapFontAdvanced_VAO);
	glBindVertexArray(m_ShaderTextBitmapFontAdvanced_VAO);

	// Generate and bind the vertex buffer (positions and UVs)
	glGenBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO);

	// Buffer vertex data (positions and UVs)
	GLfloat vertexDataBitmapFontAdvanced[2 * 6 + 2 * 6] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, ((2 * 6) + (2 * 6)) * sizeof(GLfloat), &vertexDataBitmapFontAdvanced[0], GL_STATIC_DRAW);

	// Specify the vertex attributes (position and UVs)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(2 * 6 * sizeof(GLfloat))); // UVs

	// Generate and bind the character position buffer (character position)
	glGenBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_CharacterPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_CharacterPosition);

	// Specify the character position attribute (character position)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Character position
	glVertexAttribDivisor(2, 1);

	// Generate and bind the glyph index buffer (glyph index)
	glGenBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_GlyphIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_GlyphIndex);

	// Specify the glyph index attribute (glyph index)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, 0, (void*)(0)); // Glyph position
	glVertexAttribDivisor(3, 1);

	// Generate and bind the glyph color buffer (glyph color)
	glGenBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_GlyphColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_GlyphColor);

	// Specify the glyph color attribute (glyph color)
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // Glyph color
	glVertexAttribDivisor(4, 1);

	// Generate and bind the animation parameters buffer (wave amplitude + shake amplitude)
	glGenBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_AnimationParameters);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_AnimationParameters);
	
	// Specify the animation parameter attributes (wave amplitude + shake amplitude)
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(BitmapFontResource::AnimationParameters), (void*)(0)); // Wave amplitude
	glVertexAttribDivisor(5, 1);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(BitmapFontResource::AnimationParameters), (void*)(2 * sizeof(GLfloat))); // Shake amplitude
	glVertexAttribDivisor(6, 1);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(BitmapFontResource::AnimationParameters), (void*)(4 * sizeof(GLfloat))); // Hue cycle amplitude
	glVertexAttribDivisor(7, 1);
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, sizeof(BitmapFontResource::AnimationParameters), (void*)(5 * sizeof(GLfloat))); // Intensity pulse amplitude
	glVertexAttribDivisor(8, 1);
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(9, 1, GL_FLOAT, GL_FALSE, sizeof(BitmapFontResource::AnimationParameters), (void*)(6 * sizeof(GLfloat))); // Alpha pulse amplitude
	glVertexAttribDivisor(9, 1);

	////////////////////////////////////////////////////////////////

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Destroys standard buffers
void Engine::GraphicsManager::TerminateBuffers()
{
	glDeleteBuffers(1, &m_ShaderLine_VBO);
	glDeleteVertexArrays(1, &m_ShaderLine_VAO);

	glDeleteBuffers(1, &m_ShaderRectangle_VBO);
	glDeleteVertexArrays(1, &m_ShaderRectangle_VAO);

	glDeleteBuffers(1, &m_ShaderCircle_VBO);
	glDeleteVertexArrays(1, &m_ShaderCircle_VAO);

	glDeleteBuffers(1, &m_ShaderSpriteSheet_VBO);
	glDeleteVertexArrays(1, &m_ShaderSpriteSheet_VAO);

	glDeleteBuffers(1, &m_ShaderTextBitmapFont_VBO);
	glDeleteBuffers(1, &m_ShaderTextBitmapFont_VBO_CharacterPosition);
	glDeleteBuffers(1, &m_ShaderTextBitmapFont_VBO_GlyphIndex);
	glDeleteVertexArrays(1, &m_ShaderTextBitmapFont_VBO);

	glDeleteBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO);
	glDeleteBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_CharacterPosition);
	glDeleteBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_GlyphIndex);
	glDeleteBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_GlyphColor);
	glDeleteBuffers(1, &m_ShaderTextBitmapFontAdvanced_VBO_AnimationParameters);
	glDeleteVertexArrays(1, &m_ShaderTextBitmapFontAdvanced_VBO);
}

// Loads and compiles a shader program
GLuint Engine::GraphicsManager::LoadShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Compile the individual shader stages
	GLuint vertexShaderStage = LoadShaderStage(m_ShaderPath + vertexShader + ".vert", GL_VERTEX_SHADER);
	GLuint fragmentShaderStage = LoadShaderStage(m_ShaderPath + fragmentShader + ".frag", GL_FRAGMENT_SHADER);

	// Link the shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderStage);
	glAttachShader(shaderProgram, fragmentShaderStage);
	glLinkProgram(shaderProgram);

	// Check for errors
	GLint result;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int infoLogLength;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderProgramErrorMessage(infoLogLength);
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, &shaderProgramErrorMessage[0]);
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to compile shader program using <" + vertexShader + "> and <" + fragmentShader + ">. Error: ");
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, std::string(&shaderProgramErrorMessage[0]));
		return 0;
	}

	// Delete the individual shader stages
	glDeleteShader(vertexShaderStage);
	glDeleteShader(fragmentShaderStage);

	return shaderProgram;
}

// Loads and compiles a single shader stage
GLuint Engine::GraphicsManager::LoadShaderStage(const std::string& filename, GLenum shaderStage)
{
	// Create the shader stage
	GLuint shader = glCreateShader(shaderStage);

	// Read the shader file
	std::ifstream shaderStream(filename, std::ios::in);
	std::stringstream shaderCode;

	if (shaderStream)
	{
		shaderCode << shaderStream.rdbuf();
		shaderStream.close();
	}
	else
	{
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to read shader file <" + filename + ">");
		return 0;
	}

	// Compile the shader stage
	const std::string &shaderCodeString = shaderCode.str();
	const char* shaderCodePointer = shaderCodeString.c_str();
	GLint shaderCodeLength = (GLint)shaderCodeString.size();
	glShaderSource(shader, 1, (const GLchar**)&shaderCodePointer, (GLint*)&shaderCodeLength);
	glCompileShader(shader);

	// Check for errors
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderErrorMessage[0]);
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, "Failed to compile shader file <" + filename + ">. Error: ");
		LoggingManager::GetInstance().Log(LoggingManager::LogType::Error, std::string(&shaderErrorMessage[0]));
		return 0;
	}

	return shader;
}

////////////////////////////////////////////////////////////////
// Camera													  //
////////////////////////////////////////////////////////////////

// Sets the camera position
void Engine::GraphicsManager::SetCameraPosition(const f2& position)
{
	m_CameraPosition = position;
	m_CameraViewMatrixDirty = true;
}

// Gets the camera position
Engine::f2 Engine::GraphicsManager::GetCameraPosition()
{
	return m_CameraPosition;
}

// Sets the camera zoom
void Engine::GraphicsManager::SetCameraZoom(float zoom)
{
	m_CameraZoom = zoom;
	m_CameraViewMatrixDirty = true;
}

// Gets the camera zoom
float Engine::GraphicsManager::GetCameraZoom()
{
	return m_CameraZoom;
}

// Gets the camera's view matrix
const Engine::mat4f& Engine::GraphicsManager::GetCameraViewMatrix()
{
	if (!m_CameraViewMatrixDirty)
	{
		return m_CameraViewMatrix;
	}

	// Calculate the view matrix if needed
	m_CameraViewMatrix = glm::ortho(
		m_CameraPosition.x() - ((m_WindowWidth / 2.0f) / m_CameraZoom),
		m_CameraPosition.x() + ((m_WindowWidth / 2.0f) / m_CameraZoom),
		m_CameraPosition.y() - ((m_WindowHeight / 2.0f) / m_CameraZoom),
		m_CameraPosition.y() + ((m_WindowHeight / 2.0f) / m_CameraZoom),
		m_ZNear, m_ZFar);
	m_CameraViewMatrixDirty = false;

	return m_CameraViewMatrix;
}

// Gets the camera's projection matrix
const Engine::mat4f& Engine::GraphicsManager::GetCameraProjectionMatrix()
{
	if (!m_CameraProjectionMatrixDirty)
	{
		return m_CameraProjectionMatrix;
	}

	// Calculate the projection matrix if needed
	m_CameraProjectionMatrix.SetZeros();
	m_CameraProjectionMatrix.SetDiagonal(f4(1, 1, 1, 1));
	m_CameraProjectionMatrixDirty = false;

	return m_CameraProjectionMatrix;
}

////////////////////////////////////////////////////////////////
// Sprite sheets                                              //
////////////////////////////////////////////////////////////////

// Draws a frame of the specified sprite sheet
void Engine::GraphicsManager::DrawSpriteSheetFrame(SpriteSheet spriteSheet, unsigned int frame, const f3& translation, float rotation, const f2& scale)
{
	// Retrieve the sprite sheet resource from the ResourceManager
	SpriteSheetResource& spriteSheetResource = ResourceManager::GetInstance().GetSpriteSheetResource(spriteSheet);

	// Use the sprite sheet shader program
	glUseProgram(m_ShaderSpriteSheet);

	// Bind the sprite sheet texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_ShaderSpriteSheet, "spriteSampler"), 0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetInstance().GetImageResource(spriteSheetResource.m_Image).GetTexture());

	// Calculate and pass the local coordinates of the sprite
	f2 posBottomLeft, posTopRight;
	spriteSheetResource.CalculatePositions(posBottomLeft, posTopRight);
	glUniform2f(m_ShaderSpriteSheet_uPosBottomLeft, posBottomLeft.x(), posBottomLeft.y());
	glUniform2f(m_ShaderSpriteSheet_uPosTopRight, posTopRight.x(), posTopRight.y());

	// Calculate and pass the UVs of the sprite within the sprite sheet
	f2 uvBottomLeft, uvTopRight;
	spriteSheetResource.CalculateUVs(frame, uvBottomLeft, uvTopRight);
	glUniform2f(m_ShaderSpriteSheet_uUVBottomLeft, uvBottomLeft.x(), uvBottomLeft.y());
	glUniform2f(m_ShaderSpriteSheet_uUVTopRight, uvTopRight.x(), uvTopRight.y());

	// Pass the transparancy color information
	glUniform4f(m_ShaderSpriteSheet_uTransparancyColor,
		spriteSheetResource.m_Metadata.m_ColorTransparancyRed / 255.0f,
		spriteSheetResource.m_Metadata.m_ColorTransparancyGreen / 255.0f,
		spriteSheetResource.m_Metadata.m_ColorTransparancyBlue / 255.0f,
		spriteSheetResource.m_Metadata.m_ColorTransparancyAlpha / 255.0f);

	// Pass the transformation matrices
	glm::mat4x4 matModel = glm::translate(glm::mat4x4(), (glm::vec3)translation);
	if (rotation != 0.0f) { matModel = glm::rotate(matModel, (float)rotation, glm::vec3(0.0f, 0.0f, 1.0f)); }
	if (scale != f2(1.0f, 1.0f)) { matModel = glm::scale(matModel, glm::vec3(scale.x(), scale.y(), 1.0f)); }
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatModel, 1, GL_FALSE, glm::value_ptr(matModel));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

	// Draw the sprite sheet frame
	// glBindVertexArray(spriteSheetResource.m_VertexAttributes);
	glBindVertexArray(m_ShaderSpriteSheet_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////
// Text drawing												  //
////////////////////////////////////////////////////////////////

// Draws a text message using the specified bitmap font
void Engine::GraphicsManager::DrawText(const std::string& text, BitmapFont font, transform2D transform, float z, const colorRGBA& color)
{
	// Retrieve the bitmap font resource from the ResourceManager
	BitmapFontResource& bitmapFontResource = ResourceManager::GetInstance().GetBitmapFontResource(font);

	// Retrieve the sprite sheet resource from the ResourceManager
	SpriteSheetResource& spriteSheetResource = ResourceManager::GetInstance().GetSpriteSheetResource(bitmapFontResource.m_SpriteSheet);

	// Use the sprite sheet shader program
	glUseProgram(m_ShaderTextBitmapFont);

	// Bind the sprite sheet texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_ShaderTextBitmapFont_uSpriteSampler, 0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetInstance().GetImageResource(spriteSheetResource.m_Image).GetTexture());

	// Pass the bitmap font data
	glUniform2i(m_ShaderTextBitmapFont_uGlyphSize, spriteSheetResource.m_Metadata.m_SpriteWidth, spriteSheetResource.m_Metadata.m_SpriteHeight);
	glUniform2i(m_ShaderTextBitmapFont_uGlyphOrigin, spriteSheetResource.m_Metadata.m_SpriteOriginX, spriteSheetResource.m_Metadata.m_SpriteOriginY);
	glUniform2i(m_ShaderTextBitmapFont_uSpriteSheetGridSize, spriteSheetResource.m_Metadata.m_SheetColumns, spriteSheetResource.m_Metadata.m_SheetRows);
	glUniform2i(m_ShaderTextBitmapFont_uSpriteSheetSize, spriteSheetResource.m_Metadata.m_SheetWidth, spriteSheetResource.m_Metadata.m_SheetHeight);
	glUniform2i(m_ShaderTextBitmapFont_uSpriteSheetSeparation, spriteSheetResource.m_Metadata.m_SheetSeparationX, spriteSheetResource.m_Metadata.m_SheetSeparationY);
	glUniform2i(m_ShaderTextBitmapFont_uSpriteSheetOrigin, spriteSheetResource.m_Metadata.m_SheetLeft, spriteSheetResource.m_Metadata.m_SheetTop);

	// Calculate and pass the transformation matrices
	glUniformMatrix4fv(m_ShaderTextBitmapFont_uMatModel, 1, GL_FALSE, (GLfloat*)(&transform.GetTransformationMatrix()));
	glUniformMatrix4fv(m_ShaderTextBitmapFont_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
	glUniformMatrix4fv(m_ShaderTextBitmapFont_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

	// Pass the text color
	glUniform4f(m_ShaderTextBitmapFont_uColor, color.r(), color.g(), color.b(), color.a());

	// Calculate and pass the character data
	std::vector<f2> characterPositions;
	std::vector<unsigned int> glyphIndices;
	bitmapFontResource.GetCharacterData(text, characterPositions, glyphIndices);
	size_t numCharacters = characterPositions.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFont_VBO_CharacterPosition);
	glBufferData(GL_ARRAY_BUFFER, numCharacters * 2 * sizeof(GLfloat), &characterPositions[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFont_VBO_GlyphIndex);
	glBufferData(GL_ARRAY_BUFFER, numCharacters * 1 * sizeof(GLuint), &glyphIndices[0], GL_DYNAMIC_DRAW);

	// Draw the text
	glBindVertexArray(m_ShaderTextBitmapFont_VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numCharacters);
	glBindVertexArray(0);
}

// Draws a text message using the specified bitmap font
void Engine::GraphicsManager::DrawTextAdvanced(const std::string& text, BitmapFont font, transform2D transform, float z, const colorRGBA& defaultColor)
{
	// Retrieve the bitmap font resource from the ResourceManager
	BitmapFontResource& bitmapFontResource = ResourceManager::GetInstance().GetBitmapFontResource(font);

	// Retrieve the sprite sheet resource from the ResourceManager
	SpriteSheetResource& spriteSheetResource = ResourceManager::GetInstance().GetSpriteSheetResource(bitmapFontResource.m_SpriteSheet);

	// Use the sprite sheet shader program
	glUseProgram(m_ShaderTextBitmapFontAdvanced);

	// Bind the sprite sheet texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_ShaderTextBitmapFontAdvanced_uSpriteSampler, 0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetInstance().GetImageResource(spriteSheetResource.m_Image).GetTexture());

	// Pass the bitmap font data
	glUniform2i(m_ShaderTextBitmapFontAdvanced_uGlyphSize, spriteSheetResource.m_Metadata.m_SpriteWidth, spriteSheetResource.m_Metadata.m_SpriteHeight);
	glUniform2i(m_ShaderTextBitmapFontAdvanced_uGlyphOrigin, spriteSheetResource.m_Metadata.m_SpriteOriginX, spriteSheetResource.m_Metadata.m_SpriteOriginY);
	glUniform2i(m_ShaderTextBitmapFontAdvanced_uSpriteSheetGridSize, spriteSheetResource.m_Metadata.m_SheetColumns, spriteSheetResource.m_Metadata.m_SheetRows);
	glUniform2i(m_ShaderTextBitmapFontAdvanced_uSpriteSheetSize, spriteSheetResource.m_Metadata.m_SheetWidth, spriteSheetResource.m_Metadata.m_SheetHeight);
	glUniform2i(m_ShaderTextBitmapFontAdvanced_uSpriteSheetSeparation, spriteSheetResource.m_Metadata.m_SheetSeparationX, spriteSheetResource.m_Metadata.m_SheetSeparationY);
	glUniform2i(m_ShaderTextBitmapFontAdvanced_uSpriteSheetOrigin, spriteSheetResource.m_Metadata.m_SheetLeft, spriteSheetResource.m_Metadata.m_SheetTop);

	// TEMP HARDCODED
	float m_TextAnimWaveXYOffset = 0.25f;
	f2 m_TextAnimWaveLength(16.0f, 8.0f);
	f2 m_TextAnimWaveFrequency(1.5f, 1.0f);
	f2 m_TextAnimShakeWaveLength(1.3f, 1.2f);
	f2 m_TextAnimShakeFrequency(9.0f, 11.0f);
	f2 m_TextAnimHueCycleWaveLength(64.0f, 16.0f);
	float m_TextAnimHueCycleFrequency(1.0f);
	f2 m_TextAnimIntensityPulseWaveLength(128.0f, 32.0f);
	float m_TextAnimIntensityPulseFrequency(1.5f);
	f2 m_TextAnimAlphaPulseWaveLength(16.0f, 8.0f);
	float m_TextAnimAlphaPulseFrequency(1.0f);
	// TEMP HARDCODED

	// Pass the animation parameters
	glUniform1f(m_ShaderTextBitmapFontAdvanced_uTimeSeconds, Engine::TimingManager::GetInstance().GetGameTime().GetTotalTimeSeconds());
	glUniform1f(m_ShaderTextBitmapFontAdvanced_uAnimWaveXYOffset, m_TextAnimWaveXYOffset);
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimWaveLength, m_TextAnimWaveLength.x(), m_TextAnimWaveLength.y());
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimWaveFrequency, m_TextAnimWaveFrequency.x(), m_TextAnimWaveFrequency.y());
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimShakeWaveLength, m_TextAnimShakeWaveLength.x(), m_TextAnimShakeWaveLength.y());
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimShakeFrequency, m_TextAnimShakeFrequency.x(), m_TextAnimShakeFrequency.y());
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimHueCycleWaveLength, m_TextAnimHueCycleWaveLength.x(), m_TextAnimHueCycleWaveLength.y());
	glUniform1f(m_ShaderTextBitmapFontAdvanced_uAnimHueCycleFrequency, m_TextAnimHueCycleFrequency);
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimIntensityPulseWaveLength, m_TextAnimIntensityPulseWaveLength.x(), m_TextAnimIntensityPulseWaveLength.y());
	glUniform1f(m_ShaderTextBitmapFontAdvanced_uAnimIntensityPulseFrequency, m_TextAnimIntensityPulseFrequency);
	glUniform2f(m_ShaderTextBitmapFontAdvanced_uAnimAlphaPulseWaveLength, m_TextAnimAlphaPulseWaveLength.x(), m_TextAnimAlphaPulseWaveLength.y());
	glUniform1f(m_ShaderTextBitmapFontAdvanced_uAnimAlphaPulseFrequency, m_TextAnimAlphaPulseFrequency);

	// Calculate and pass the transformation matrices
	glUniformMatrix4fv(m_ShaderTextBitmapFontAdvanced_uMatModel, 1, GL_FALSE, (GLfloat*)(&transform.GetTransformationMatrix()));
	glUniformMatrix4fv(m_ShaderTextBitmapFontAdvanced_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
	glUniformMatrix4fv(m_ShaderTextBitmapFontAdvanced_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

	// Calculate and pass the character data
	std::vector<f2> characterPositions;
	std::vector<unsigned int> glyphIndices;
	std::vector<colorRGBA> glyphColors;
	std::vector<BitmapFontResource::AnimationParameters> animParameters;
	bitmapFontResource.GetCharacterDataAdvanced(text, characterPositions, glyphIndices, glyphColors, animParameters, defaultColor);
	size_t numCharacters = characterPositions.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_CharacterPosition);
	glBufferData(GL_ARRAY_BUFFER, numCharacters * sizeof(f2), &characterPositions[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_GlyphIndex);
	glBufferData(GL_ARRAY_BUFFER, numCharacters * sizeof(unsigned int), &glyphIndices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_GlyphColor);
	glBufferData(GL_ARRAY_BUFFER, numCharacters * sizeof(colorRGBA), &glyphColors[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShaderTextBitmapFontAdvanced_VBO_AnimationParameters);
	glBufferData(GL_ARRAY_BUFFER, numCharacters * sizeof(BitmapFontResource::AnimationParameters), &animParameters[0], GL_DYNAMIC_DRAW);

	// Draw the text
	glBindVertexArray(m_ShaderTextBitmapFontAdvanced_VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numCharacters);
	glBindVertexArray(0);
}