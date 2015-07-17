#pragma once
#ifndef ENGINE_COMMON_UTILITY_GAMETIME_H
#define ENGINE_COMMON_UTILITY_GAMETIME_H

#include <chrono> // For measuring time between frames
#include <thread> // For sleeping the thread until the next update time

namespace Engine{

	// Structure for storing timing information
	struct GameTime
	{

	private: 

		unsigned int m_DeltaTimeMicros;
		unsigned int m_MeasuredDeltaTimeMicros;
		unsigned long long m_TotalTimeMicros;
		unsigned int m_MeasuredTotalTimeMicros;
		unsigned long long m_FrameCount;

		std::chrono::time_point<std::chrono::high_resolution_clock> time;
		std::chrono::time_point<std::chrono::high_resolution_clock> timeFixedSynchronization;

	public: 

		// Constructors
		GameTime() : m_DeltaTimeMicros(0), m_MeasuredDeltaTimeMicros(0), m_TotalTimeMicros(0), m_MeasuredTotalTimeMicros(0), m_FrameCount(0)
		{ 
			time = std::chrono::high_resolution_clock::now(); 
			timeFixedSynchronization = std::chrono::high_resolution_clock::now();
		}

		// Getters
		inline unsigned int GetDeltaTimeMicros() const { return m_DeltaTimeMicros; }
		inline float GetDeltaTimeSeconds() const { return (float)m_DeltaTimeMicros / 1000000.0f; }
		inline unsigned long long GetTotalTimeMicros() const { return m_TotalTimeMicros; }
		inline double GetTotalTimeSeconds() const { return (float)m_TotalTimeMicros / 1000000.0f; }
		inline unsigned int GetMeasuredDeltaTimeMicros() const { return m_MeasuredDeltaTimeMicros; }
		inline float GetMeasuredDeltaTimeSeconds() const { return (float)m_MeasuredDeltaTimeMicros / 1000000.0f; }
		inline unsigned long long GetMeasuredTotalTimeMicros() const { return m_MeasuredTotalTimeMicros; }
		inline double GetMeasuredTotalTimeSeconds() const { return (float)m_MeasuredTotalTimeMicros / 1000000.0f; }
		inline unsigned long long GetFrameCount() const { return m_FrameCount; }

		// Updates the timing information and continues (variable framerate)
		inline void update() 
		{ 
			auto now = std::chrono::high_resolution_clock::now();
			m_DeltaTimeMicros = (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(now - time).count();
			m_TotalTimeMicros += m_DeltaTimeMicros;
			m_MeasuredDeltaTimeMicros = m_DeltaTimeMicros;
			m_MeasuredTotalTimeMicros += m_MeasuredDeltaTimeMicros;
			m_FrameCount++;
			time = now;
		}

		// Updates the timing information and sleeps until the next update (fixed framerate)
		inline void updateAndSleep(unsigned int frameDurationMicros)
		{
			auto now = std::chrono::high_resolution_clock::now();
			m_MeasuredDeltaTimeMicros = (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(now - time).count();
			m_MeasuredTotalTimeMicros += m_MeasuredDeltaTimeMicros;
			m_DeltaTimeMicros = frameDurationMicros;
			m_TotalTimeMicros += m_DeltaTimeMicros;
			m_FrameCount++;
			time = now;
			timeFixedSynchronization += std::chrono::microseconds(frameDurationMicros);
			std::this_thread::sleep_until(timeFixedSynchronization);
		}
	};
}
#endif