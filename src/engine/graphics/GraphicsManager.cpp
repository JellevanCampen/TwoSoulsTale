#include "GraphicsManager.hpp"

#include "../debugging/LoggingManager.hpp" // Logging manager for reporting statuses
#include "SpriteSheetResource.hpp" // Sprite sheet resources

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

////////////////////////////////////////////////////////////////
// Primitives                                                 //
////////////////////////////////////////////////////////////////

// Draws a line
void Engine::GraphicsManager::DrawLine(f2 p1, f2 p2, f4 color)
{
	// Use the sprite sheet shader program
	glUseProgram(m_ShaderLine);

	// Pass the start- and endpoints of the line
	glUniform2f(m_ShaderLine_uStart, p1.x(), p1.y());
	glUniform2f(m_ShaderLine_uEnd, p2.x(), p2.y());

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

// Draws a rectangle
void Engine::GraphicsManager::DrawRectangle(f2 p1, f2 p2, f4 color)
{
	// Use the sprite sheet shader program
	glUseProgram(m_ShaderRectangle);

	// Pass the start- and endpoints of the line
	glUniform2f(m_ShaderRectangle_uBottomLeft, p1.x(), p1.y());
	glUniform2f(m_ShaderRectangle_uTopRight, p2.x(), p2.y());

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

////////////////////////////////////////////////////////////////
// Sprite sheets                                              //
////////////////////////////////////////////////////////////////

// Draws a frame of the specified sprite sheet
void Engine::GraphicsManager::DrawSpriteSheetFrame(SpriteSheet spriteSheet, unsigned int frame, double x, double y, double z)
{
	// Retrieve the sprite sheet resource from the ResourceManager
	SpriteSheetResource& spriteSheetResource = ResourceManager::GetInstance().GetSpriteSheetResource(spriteSheet);

	// Use the sprite sheet shader program
	glUseProgram(m_ShaderSpriteSheet);

	// Bind the sprite sheet texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_ShaderSpriteSheet, "spriteSampler"), 0);
	glBindTexture(GL_TEXTURE_2D, spriteSheetResource.m_Texture);

	// Calculate and pass the UVs of the sprite within the sprite sheet
	float left = (float)(spriteSheetResource.m_Descriptor.m_SheetLeft + (frame % spriteSheetResource.m_Descriptor.m_SheetColumns) * (spriteSheetResource.m_Descriptor.m_SheetSeparationX + spriteSheetResource.m_Descriptor.m_SpriteWidth));
	float right = (float)(left + spriteSheetResource.m_Descriptor.m_SpriteWidth);
	float top = (float)(spriteSheetResource.m_Descriptor.m_SheetTop + (int)(frame / spriteSheetResource.m_Descriptor.m_SheetColumns) * (spriteSheetResource.m_Descriptor.m_SheetSeparationY + spriteSheetResource.m_Descriptor.m_SpriteHeight));
	float bottom = (float)(top + spriteSheetResource.m_Descriptor.m_SpriteHeight);
	left /= spriteSheetResource.m_Descriptor.m_SheetWidth;
	right /= spriteSheetResource.m_Descriptor.m_SheetWidth;
	top /= spriteSheetResource.m_Descriptor.m_SheetHeight;
	bottom /= spriteSheetResource.m_Descriptor.m_SheetHeight;
	glUniform2f(m_ShaderSpriteSheet_uSpriteUV1, left, top);
	glUniform2f(m_ShaderSpriteSheet_uSpriteUV2, right, bottom);

	// Pass the transparancy color information
	glUniform4f(m_ShaderSpriteSheet_uTransparancyColor,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyRed / 255.0f,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyGreen / 255.0f,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyBlue / 255.0f,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyAlpha / 255.0f);

	// Pass the transformation matrices
	glm::mat4x4 matModel = glm::translate(glm::mat4x4(), glm::vec3(x, y, z));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatModel, 1, GL_FALSE, glm::value_ptr(matModel));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

	// Draw the sprite sheet frame
	glBindVertexArray(spriteSheetResource.m_VertexAttributes);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

// Draws a frame of the specified sprite sheet using the specified transformation
void Engine::GraphicsManager::DrawSpriteSheetFrameTransformed(SpriteSheet spriteSheet, unsigned int frame, double x, double y, double z, double rotation, double scaleX, double scaleY)
{
	// Retrieve the sprite sheet resource from the ResourceManager
	SpriteSheetResource& spriteSheetResource = ResourceManager::GetInstance().GetSpriteSheetResource(spriteSheet);

	// Use the sprite sheet shader program
	glUseProgram(m_ShaderSpriteSheet);

	// Bind the sprite sheet texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_ShaderSpriteSheet, "spriteSampler"), 0);
	glBindTexture(GL_TEXTURE_2D, spriteSheetResource.m_Texture);

	// Calculate and pass the UVs of the sprite within the sprite sheet
	float left = (float)(spriteSheetResource.m_Descriptor.m_SheetLeft + (frame % spriteSheetResource.m_Descriptor.m_SheetColumns) * (spriteSheetResource.m_Descriptor.m_SheetSeparationX + spriteSheetResource.m_Descriptor.m_SpriteWidth));
	float right = (float)(left + spriteSheetResource.m_Descriptor.m_SpriteWidth);
	float top = (float)(spriteSheetResource.m_Descriptor.m_SheetTop + (int)(frame / spriteSheetResource.m_Descriptor.m_SheetColumns) * (spriteSheetResource.m_Descriptor.m_SheetSeparationY + spriteSheetResource.m_Descriptor.m_SpriteHeight));
	float bottom = (float)(top + spriteSheetResource.m_Descriptor.m_SpriteHeight);
	left /= spriteSheetResource.m_Descriptor.m_SheetWidth;
	right /= spriteSheetResource.m_Descriptor.m_SheetWidth;
	top /= spriteSheetResource.m_Descriptor.m_SheetHeight;
	bottom /= spriteSheetResource.m_Descriptor.m_SheetHeight;
	glUniform2f(m_ShaderSpriteSheet_uSpriteUV1, left, top);
	glUniform2f(m_ShaderSpriteSheet_uSpriteUV2, right, bottom);

	// Pass the transparancy color information
	glUniform4f(m_ShaderSpriteSheet_uTransparancyColor,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyRed / 255.0f,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyGreen / 255.0f,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyBlue / 255.0f,
		spriteSheetResource.m_Descriptor.m_ColorTransparancyAlpha / 255.0f);

	// Pass the transformation matrices
	glm::mat4x4 matModel = glm::translate(glm::mat4x4(), glm::vec3(x, y, z));
	matModel = glm::rotate(matModel, (float)rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	matModel = glm::scale(matModel, glm::vec3(scaleX, scaleY, 1.0f));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatModel, 1, GL_FALSE, glm::value_ptr(matModel));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatView, 1, GL_FALSE, (GLfloat*)(&GetCameraViewMatrix()));
	glUniformMatrix4fv(m_ShaderSpriteSheet_uMatProjection, 1, GL_FALSE, (GLfloat*)(&GetCameraProjectionMatrix()));

	// Draw the sprite sheet frame
	glBindVertexArray(spriteSheetResource.m_VertexAttributes);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
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
	//////////////////////////////////////////// Sprite Sheet Shader

	m_ShaderSpriteSheet = LoadShaderProgram("spritesheet", "spritesheet"); 
	m_ShaderSpriteSheet_uTransparancyColor = glGetUniformLocation(m_ShaderSpriteSheet, "uTransparancyColor");
	m_ShaderSpriteSheet_uSpriteUV1 = glGetUniformLocation(m_ShaderSpriteSheet, "spriteUV1");
	m_ShaderSpriteSheet_uSpriteUV2 = glGetUniformLocation(m_ShaderSpriteSheet, "spriteUV2");
	m_ShaderSpriteSheet_uMatModel = glGetUniformLocation(m_ShaderSpriteSheet, "matModel");
	m_ShaderSpriteSheet_uMatView = glGetUniformLocation(m_ShaderSpriteSheet, "matView");
	m_ShaderSpriteSheet_uMatProjection = glGetUniformLocation(m_ShaderSpriteSheet, "matProjection");

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
}

// Destroys standard shader programs
void Engine::GraphicsManager::TerminateShaderPrograms()
{
	glDeleteProgram(m_ShaderSpriteSheet); 
	glDeleteProgram(m_ShaderLine); 
	glDeleteProgram(m_ShaderRectangle); 
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

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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
}

// Loads and compiles a shader program
GLuint Engine::GraphicsManager::LoadShaderProgram(std::string vertexShader, std::string fragmentShader)
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
GLuint Engine::GraphicsManager::LoadShaderStage(std::string filename, GLenum shaderStage)
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
void Engine::GraphicsManager::SetCameraPosition(f2 position)
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