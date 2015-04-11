#pragma once
#ifndef ENGINE_INPUT_MOUSELISTENER_H
#define ENGINE_INPUT_MOUSELISTENER_H

namespace Engine{

	// Interface for objects that listen to mouse events
	class MouseListener{

	public:

		virtual ~MouseListener() {}
		virtual void ProcessMousePositionEvent(int xPos, int yPos) = 0;
		virtual void ProcessMouseEnterLeaveEvent(bool entered) = 0;
		virtual void ProcessMouseButtonEvent(int button, int action) = 0;
		virtual void ProcessMouseScrollEvent(int xOffset, int yOffset) = 0;

	};
}

#endif