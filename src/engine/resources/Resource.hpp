#pragma once
#ifndef ENGINE_RESOURCES_RESOURCE_H
#define ENGINE_RESOURCES_RESOURCE_H

namespace Engine
{
	class ResourceManager;

	class Resource
	{

	private:

		// Loads the resource
		virtual bool Load() = 0;

		// Unloads the resource
		virtual bool Unload() = 0;

		/**************************************************************/
		/* Reference counting                                         */
		/**************************************************************/

		// Gets the number of reservations of this resource
		unsigned int GetNumReservations();

		// Adds a new reservation to the resource
		void AddReservation();

		// Removes a reservation from the resource
		void RemoveReservation();

		// Number of reservations for this resource
		unsigned int m_NumReservations;

	public:

		friend class ResourceManager;

	};
}

#endif

