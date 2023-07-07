#pragma once

#include "Core.h"

namespace Cy
{
	enum class EventType
	{
		None = 0,
		GameTick,
		GameUpdate,
		GameRender,

		WindowClose,
		WindowResize,
		WindowMove,
		WindowFocus,
		WindowFocusLost,

		KeyPressed,
		KeyReleased,
		KeyRepeat,

		MousePressed,
		MouseReleased,
		MouseMove,
		MouseScroll
	};

	enum EventCategory
	{
		None = 0,
		Application		= BIT(0),
		Input			= BIT(1),
		Keyboard		= BIT(1),
		Mouse			= BIT(3),
		MouseButton		= BIT(4)
	};

#define EVENT_TYPE(type)\
	static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetDisplayName() const override { return #type; }

	class CY_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetDisplayName() const = 0;

		virtual std::string ToString() const { return GetDisplayName(); }

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}
