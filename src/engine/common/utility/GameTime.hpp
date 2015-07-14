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
		unsigned long long m_TotalTimeMicros;
		unsigned long long m_FrameCount;

		std::chrono::time_point<std::chrono::high_resolution_clock> time;

	public: 

		// Constructors
		GameTime() : m_DeltaTimeMicros(0), m_TotalTimeMicros(0), m_FrameCount(0) { time = std::chrono::high_resolution_clock::now(); }

		// Getters
		inline unsigned int GetDeltaTimeMicros() const { return m_DeltaTimeMicros; }
		inline float GetDeltaTimeSeconds() const { return (float)m_DeltaTimeMicros / 1000000.0f; }
		inline unsigned long long GetTotalTimeMicros() const { return m_TotalTimeMicros; }
		inline double GetTotalTimeSeconds() const { return (float)m_TotalTimeMicros / 1000000.0f; }
		inline unsigned long long GetFrameCount() const { return m_FrameCount; }

		// Updates the timing information and continues (variable framerate)
		inline void update() 
		{ 
			auto now = std::chrono::high_resolution_clock::now();
			m_DeltaTimeMicros = (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(now - time).count();
			m_TotalTimeMicros += m_DeltaTimeMicros;
			m_FrameCount++;
			time = now;
		}

		// Updates the timing information and sleeps until the next update (fixed framerate)
		inline void updateAndSleep(unsigned int frameDurationMicros)
		{
			auto now = std::chrono::high_resolution_clock::now();
			m_DeltaTimeMicros = frameDurationMicros;
			m_TotalTimeMicros += m_DeltaTimeMicros;
			m_FrameCount++;
			std::this_thread::sleep_until(time + std::chrono::microseconds(frameDurationMicros));
		}
	};
}
#endif