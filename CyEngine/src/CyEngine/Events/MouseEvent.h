#pragma once
#include "Event.h"

namespace Cy
{
	class CY_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(int x, int y)
			: m_MouseX(x), m_MouseY(y)
		{
		}

		inline int GetX() const { return m_MouseX; }
		inline int GetY() const { return m_MouseY; }
	
		EVENT_TYPE(MouseMove);

	private:
		int m_MouseX, m_MouseY;
	};

	class CY_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }

	protected:
		MouseButtonEvent(int button)
			: m_Button(button)
		{
		}

		int m_Button;
	};

	class CY_API MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button) : MouseButtonEvent(button)
		{
		}

		EVENT_TYPE(MousePressed);
	};

	class CY_API MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button) : MouseButtonEvent(button)
		{
		}

		EVENT_TYPE(MouseReleased);
	};

	class CY_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float delta)
			: m_Delta(delta)
		{
		}

		inline int GetDelta() const { return m_Delta; }

		EVENT_TYPE(MouseScroll);

	private:
		float m_Delta;
	};
}