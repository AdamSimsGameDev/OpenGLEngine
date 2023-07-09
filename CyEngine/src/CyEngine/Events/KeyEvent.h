#pragma once
#include "Event.h"

namespace Cy
{
	class CY_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode) 
		{
		}

		int m_KeyCode;
	};

	class CY_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keyCode) : KeyEvent(keyCode)
		{
		}

		EVENT_TYPE(KeyPressed);
	};

	class CY_API KeyRepeatEvent : public KeyEvent
	{
	public:
		KeyRepeatEvent(int keyCode) : KeyEvent(keyCode)
		{
		}

		EVENT_TYPE(KeyRepeat);
	};


	class CY_API KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keyCode) : KeyEvent(keyCode)
		{
		}

		EVENT_TYPE(KeyReleased);
	};

	class CY_API KeyCharEvent : public KeyEvent
	{
	public:
		KeyCharEvent(int keyCode) : KeyEvent(keyCode)
		{
		}

		EVENT_TYPE(KeyChar);
	};
}