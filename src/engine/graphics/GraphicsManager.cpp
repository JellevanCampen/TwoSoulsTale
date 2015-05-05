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

	// Initialize OpenGL settings
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

/**************************************************************/
/* Sprite sheets                                              */
/**************************************************************/

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
	float left = spriteSheetResource.m_SheetLeft + (frame % spriteSheetResource.m_SheetColumns) * (spriteSheetResource.m_SheetSeparationX + spriteSheetResource.m_SpriteWidth);
	float right = left + spriteSheetResource.m_SpriteWidth;
	float top = spriteSheetResource.m_SheetTop + (int)(frame / spriteSheetResource.m_SheetColumns) * (spriteSheetResource.m_SheetSeparationY + spriteSheetResource.m_SpriteHeight);
	float bottom = top + spriteSheetResource.m_SpriteHeight;
	left /= spriteSheetResource.m_SheetWidth;
	right /= spriteSheetResource.m_SheetWidth;
	top /= spriteSheetResource.m_SheetHeight;
	bottom /= spriteSheetResource.m_SheetHeight;
	glUniform2f(glGetUniformLocation(m_ShaderSpriteSheet, "spriteUV1"), left, top);
	glUniform2f(glGetUniformLocation(m_ShaderSpriteSheet, "spriteUV2"), right, bottom);

	glm::mat4x4 matModel = glm::translate(glm::mat4x4(), glm::vec3(x, y, z));
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderSpriteSheet, "matModel"), 1, GL_FALSE, glm::value_ptr(matModel));

	glm::mat4x4 matView = glm::ortho(0.0f, 256.0f, 0.0f, 240.0f, -1000.0f, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderSpriteSheet, "matView"), 1, GL_FALSE, glm::value_ptr(matView));

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
	m_ShaderSpriteSheet = LoadShaderProgram("spritesheet", "spritesheet"); // Sprite sheet shader
}

// Destroys standard shader programs
void Engine::GraphicsManager::TerminateShaderPrograms()
{
	glDeleteProgram(m_ShaderSpriteSheet); // Sprite sheet shader
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
	GLint shaderCodeLength = shaderCodeString.size();
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