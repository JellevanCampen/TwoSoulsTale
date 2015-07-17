#include "TimingManager.hpp"

#include "../debugging/LoggingManager.hpp" // For logging warning messages

#include <algorithm> // For finding listeners in listener lists

// Initializes the timing manager
void Engine::TimingManager::Initialize()
{
	
}

// Terminates the timing manager
void Engine::TimingManager::Terminate()
{

}

// Updates the timing manager to find the new game time
void Engine::TimingManager::Update(const GameTime& gameTime)
{
	// Cache the game time
	m_GameTime = gameTime;

	// Queue the frame duration for frame-rate calculation
	m_FrameDurationsMicros.push_back(gameTime.GetMeasuredDeltaTimeMicros());
	if (m_FrameDurationsMicros.size() > s_FramerateWindowSize) { m_FrameDurationsMicros.pop_front(); }

	// Launch alarm events for expired alarms
	for (auto i_Timestamp = m_AlarmsByTimestamp.begin(); i_Timestamp != m_AlarmsByTimestamp.end();)
	{
		// If the current timestamp is not expired, break as all following timestamps won't have expired either (ordered map)
		if (i_Timestamp->first > m_GameTime.GetTotalTimeMicros()) { break; }

		// Trigger alarms that have expired timestamps
		std::list<Alarm*> alarmsToReschedule;
		for (Alarm* i_Alarm : i_Timestamp->second)
		{
			for (AlarmListener* l : i_Alarm->m_Listeners) { l->ProcessAlarmEvent(i_Alarm->m_AlarmID, i_Alarm->m_Timestamp); }
			alarmsToReschedule.push_back(i_Alarm);
		}

		// Reschedule alarms that have been triggered
		bool rescheduled = false;
		for (Alarm* i_Alarm : alarmsToReschedule) { RescheduleAlarm(i_Alarm); }
		if (alarmsToReschedule.size() > 0) { rescheduled = true; }
		alarmsToReschedule.clear();

		// If alarms have been rescheduled, restart iterating the map
		if (rescheduled) { i_Timestamp = m_AlarmsByTimestamp.begin(); } 
		else { i_Timestamp++; }
	}
}

////////////////////////////////////////////////////////////////
// Game time querying										  //
////////////////////////////////////////////////////////////////

// Gets the current game time
const Engine::GameTime& Engine::TimingManager::GetGameTime() const
{
	return m_GameTime;
}

// Gets the current framerate
float Engine::TimingManager::GetFrameRate() const
{
	unsigned long cumulativeFrameDuration = 0;
	for (unsigned int fd : m_FrameDurationsMicros) { cumulativeFrameDuration += fd; }
	float temp = (float)m_FrameDurationsMicros.size() / (float)(cumulativeFrameDuration / 1000000.0f);

	return (float)m_FrameDurationsMicros.size() / (float)(cumulativeFrameDuration / 1000000.0f);
}

////////////////////////////////////////////////////////////////
// Timing-based events										  //
////////////////////////////////////////////////////////////////

// Sets an alarm that (periodically) launches timing-based events
Engine::AlarmID Engine::TimingManager::SetAlarm(TimeDelta timeDelta, unsigned int repetitions)
{
	Timestamp timestamp = m_GameTime.GetTotalTimeMicros() + timeDelta;
	Alarm* alarm(new Alarm(s_AlarmIDCounter++, timestamp, timeDelta, repetitions));
	m_AlarmsByID.insert(std::pair<AlarmID, Alarm*>(alarm->m_AlarmID, alarm));
	if (m_AlarmsByTimestamp.count(timestamp) == 0)
	{ 
		std::list<Alarm*> alarmList;
		alarmList.push_back(alarm);
		m_AlarmsByTimestamp.insert(std::pair<Timestamp, std::list<Alarm*>>(timestamp, alarmList)); 
	}
	else
	{
		m_AlarmsByTimestamp[timestamp].push_back(alarm);
	}

	return alarm->m_AlarmID;
}

// Unsets the alarm
void Engine::TimingManager::UnsetAlarm(AlarmID alarmID)
{
	if (m_AlarmsByID.count(alarmID) == 0) { return; }
	Alarm* alarm = m_AlarmsByID[alarmID];

	// Remove from the by-ID list
	m_AlarmsByID.erase(alarmID);

	// Remove from the by-timetamp list
	auto it = std::find(m_AlarmsByTimestamp[alarm->m_Timestamp].begin(), m_AlarmsByTimestamp[alarm->m_Timestamp].end(), alarm);
	if (it != m_AlarmsByTimestamp[alarm->m_Timestamp].end()) { m_AlarmsByTimestamp[alarm->m_Timestamp].erase(it); }
	if (m_AlarmsByTimestamp[alarm->m_Timestamp].size() == 0) { m_AlarmsByTimestamp.erase(alarm->m_Timestamp); }
}

// Register as a listener for an alarm
void Engine::TimingManager::RegisterAlarmListener(AlarmID alarmID, AlarmListener* alarmListener)
{
	if (m_AlarmsByID.count(alarmID) != 0)
	{
		m_AlarmsByID[alarmID]->m_Listeners.push_back(alarmListener);
	}
	else
	{
		Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Warning, "[TimingManager] Tried to register as a listener to a non-existant alarm <" + std::to_string(alarmID) + ">");
	}
}

// Deregister as a listener for an alarm
void Engine::TimingManager::DeregisterAlarmListener(AlarmID alarmID, AlarmListener* alarmListener)
{
	if (m_AlarmsByID.count(alarmID) != 0)
	{
		auto it = std::find(m_AlarmsByID[alarmID]->m_Listeners.begin(), m_AlarmsByID[alarmID]->m_Listeners.end(), alarmListener);
		if (it != m_AlarmsByID[alarmID]->m_Listeners.end()) { m_AlarmsByID[alarmID]->m_Listeners.erase(it); }
	}
}

// Reschedules a periodic alarm
bool Engine::TimingManager::RescheduleAlarm(Alarm* alarm)
{
	// No rescheduling needed
	if (alarm->m_Repetitions == 0) { UnsetAlarm(alarm->m_AlarmID); return false; }

	// Remove from the timestamp list
	auto it = std::find(m_AlarmsByTimestamp[alarm->m_Timestamp].begin(), m_AlarmsByTimestamp[alarm->m_Timestamp].end(), alarm);
	if (it != m_AlarmsByTimestamp[alarm->m_Timestamp].end()) { m_AlarmsByTimestamp[alarm->m_Timestamp].erase(it); }
	else { Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Warning, "[TimingManager] Tried to reschedule an alarm that was not registered by timestamp."); }
	if (m_AlarmsByTimestamp[alarm->m_Timestamp].size() == 0) { m_AlarmsByTimestamp.erase(alarm->m_Timestamp); }

	// Update the alarm
	alarm->m_Timestamp += alarm->m_TimeDelta;
	if (alarm->m_Repetitions != (unsigned int)(-1)) { alarm->m_Repetitions--; }
	
	// Add the updated alar mto the timestamp list
	if (m_AlarmsByTimestamp.count(alarm->m_Timestamp) == 0)
	{
		std::list<Alarm*> alarmList;
		alarmList.push_back(alarm);
		m_AlarmsByTimestamp.insert(std::pair<Timestamp, std::list<Alarm*>>(alarm->m_Timestamp, alarmList));
	}
	else
	{
		m_AlarmsByTimestamp[alarm->m_Timestamp].push_back(alarm);
	}

	return true;
}

// Incrementing alarm ID counter
Engine::AlarmID Engine::TimingManager::s_AlarmIDCounter = 0;