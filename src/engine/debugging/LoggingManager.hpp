#pragma once
#ifndef ENGINE_DEBUGGING_LOGGINGMANAGER_H
#define ENGINE_DEBUGGING_LOGGINGMANAGER_H

#include <string>

#include "../common/patterns/Singleton.hpp" // Singleton pattern

namespace Engine{
	class LoggingManager : public Singleton<LoggingManager>{

	public:

		enum LogType
		{
			Status, 
			Warning, 
			Error
		};

		// Initializes the logging manager
		void Initialize();

		// Terminates the logging manager
		void Terminate();

		// Logs a message
		void Log(LogType logType, const std::string& message);

	private:

		

	};
}

#endif