#include "LoggingManager.hpp"

#include <Windows.h>
#include <iostream>

// Initializes the logging manager
void Engine::LoggingManager::Initialize()
{

}

// Terminates the logging manager
void Engine::LoggingManager::Terminate()
{

}

// Logs a message
void Engine::LoggingManager::Log(LogType logType, const std::string& message)
{
	// Set the color of the logged message
	switch (logType)
	{
	case LogType::Status:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		break;
	case LogType::Warning:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		break;
	case LogType::Error:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		break;
	default:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		break;
	}

	// Log the message to the windows terminal
	std::cout << message << std::endl;
}