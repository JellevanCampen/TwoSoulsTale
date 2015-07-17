#pragma once
#ifndef ENGINE_TIMING_TIMINGMANAGER_H
#define ENGINE_TIMING_TIMINGMANAGER_H

#include "../common/utility/GameTime.hpp" // For representing the game time
#include "../common/patterns/Singleton.hpp" // Singleton pattern
#include "AlarmListener.hpp" // Interface for alarm listeners

#include <map> // For storing alarms by timestamp, sorted from nearest to furthest timestamp
#include <unordered_map> // For storing alarms by ID
#include <list> // For storing all listeners to an alarms
#include <deque> // For storing past frame durations to calculate the framerate

namespace Engine{

	class TimingManager : public Singleton<TimingManager>
	{

	public:

		// Initializes the timing manager
		void Initialize();

		// Terminates the timing manager
		void Terminate();

		// Updates the timing manager to find the new game time
		void Update(const GameTime& gameTime);

		////////////////////////////////////////////////////////////////
		// Game time querying										  //
		////////////////////////////////////////////////////////////////

		// Gets the current game time
		const GameTime& GetGameTime() const;

		// Gets the current framerate
		float GetFrameRate() const;

	private:

		// Cached version of the game time information for the current frame
		GameTime m_GameTime;

		// Number of frames durations to average to obtain the framerate
		static const size_t s_FramerateWindowSize = 500;

		// Queue for storing past frame durations to calculate the frame rate
		std::deque<unsigned int> m_FrameDurationsMicros;

	public:

		////////////////////////////////////////////////////////////////
		// Timing-based events										  //
		////////////////////////////////////////////////////////////////

		// Sets an alarm that (periodically) launches timing-based events
		AlarmID SetAlarm(TimeDelta timeDelta, unsigned int repetitions = 1);

		// Sets an alarm that infinitely, periodically launches timing-based events
		inline AlarmID SetInfinitePeriodicAlarm(TimeDelta timeDelta) { return SetAlarm(timeDelta, (unsigned int)(-1)); }

		// Unsets the alarm
		void UnsetAlarm(AlarmID alarmID);

		// Register as a listener for an alarm
		void RegisterAlarmListener(AlarmID alarmID, AlarmListener* alarmListener);

		// Deregister as a listener for an alarm
		void DeregisterAlarmListener(AlarmID alarmID, AlarmListener* alarmListener);

	private:

		typedef struct Alarm
		{
			AlarmID m_AlarmID;
			Timestamp m_Timestamp;
			TimeDelta m_TimeDelta;
			unsigned int m_Repetitions;
			std::list<AlarmListener*> m_Listeners;

			Alarm(AlarmID alarmID, Timestamp timestamp, TimeDelta timeDelta, unsigned int repetitions)
				: m_AlarmID(alarmID), m_Timestamp(timestamp), m_TimeDelta(timeDelta), m_Repetitions(repetitions) { }
		};

		// Reschedules a periodic alarm (returns whether or not the event was rescheduled)
		bool RescheduleAlarm(Alarm* alarm);

		// Holds all alarms (mapped by ID)
		std::unordered_map<AlarmID, Alarm*> m_AlarmsByID;

		// Holds all alarms (mapped by timestamp)
		std::map<Timestamp, std::list<Alarm*>> m_AlarmsByTimestamp;

		// Incrementing alarm ID counter
		static AlarmID s_AlarmIDCounter;

	};
}

#endif