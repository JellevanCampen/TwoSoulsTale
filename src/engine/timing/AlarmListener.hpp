#pragma once
#ifndef ENGINE_TIMING_ALARMLISTENER_H
#define ENGINE_TIMING_ALARMLISTENER_H

namespace Engine{

	// Typedef for alarm IDs
	typedef unsigned int AlarmID;

	// Typedef for timestamps
	typedef unsigned long long Timestamp;

	// Typedef for time deltas
	typedef unsigned long long TimeDelta;

	// Interface for objects that listen to alarm events
	class AlarmListener{

	public:

		virtual ~AlarmListener() { };
		virtual void ProcessAlarmEvent(AlarmID alarmID, Timestamp timestamp) { };

	};
}

#endif