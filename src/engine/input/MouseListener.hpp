#pragma once
#ifndef ENGINE_INPUT_MOUSELISTENER_H
#define ENGINE_INPUT_MOUSELISTENER_H

namespace Engine{

	// Interface for objects that listen to mouse events
	class MouseListener{

	public:

		// Describes the action performed for a mouse button event
		typedef enum MouseButtonAction
		{
			PRESSED,
			RELEASED
		};

		virtual ~MouseListener() { };
		virtual void ProcessMousePositionEvent(double xPos, double yPos) { };
		virtual void ProcessMouseEnterLeaveEvent(bool entered) { };
		virtual void ProcessMouseButtonEvent(int button, MouseButtonAction action) { };
		virtual void ProcessMouseScrollEvent(int xOffset, int yOffset) { };

	};
}

#endif