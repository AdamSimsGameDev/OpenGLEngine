#pragma once
#include "Event.h"

namespace Cy
{
	class CY_API WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(WindowClose);
	};

	class CY_API WindowFocusEvent : public Event
	{
	public:
		EVENT_TYPE(WindowFocus);
	};

	class CY_API WindowFocusLostEvent : public Event
	{
	public:
		EVENT_TYPE(WindowFocusLost);
	};

	class CY_API WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int x, int y)
			: m_WindowX(x), m_WindowY(y)
		{
		}

		inline int GetX() const { return m_WindowX; }
		inline int GetY() const { return m_WindowY; }

		EVENT_TYPE(WindowMove);

	private:
		int m_WindowX, m_WindowY;
	};

	class CY_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_WindowWidth(width), m_WindowHeight(height)
		{
		}

		inline int GetWidth() const { return m_WindowWidth; }
		inline int GetHeight() const { return m_WindowHeight; }

		EVENT_TYPE(WindowResize);

	private:
		int m_WindowWidth, m_WindowHeight;
	};
}