#pragma once
#include "Event.h"

namespace Cy
{
	class CY_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y)
		{
		}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
	
		EVENT_TYPE(MouseMove);

	private:
		float m_MouseX, m_MouseY;
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
		MouseScrollEvent(float offsetX, float offsetY)
			: m_OffsetX(offsetX), m_OffsetY(offsetY)
		{
		}

		inline int GetOffsetX() const { return m_OffsetX; }
		inline int GetOffsetY() const { return m_OffsetY; }

		EVENT_TYPE(MouseScroll);

	private:
		float m_OffsetX;
		float m_OffsetY;
	};
}