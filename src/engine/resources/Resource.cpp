#include "Resource.hpp"

/**************************************************************/
/* Reference counting                                         */
/**************************************************************/

// Gets the number of reservations of this resource
unsigned int Engine::Resource::GetNumReservations()
{
	return m_NumReservations;
}

// Adds a new reservation to the resource
void Engine::Resource::AddReservation()
{
	m_NumReservations++;
}

// Removes a reservation from the resource
void Engine::Resource::RemoveReservation()
{
	m_NumReservations--;
}