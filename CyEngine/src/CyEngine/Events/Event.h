#pragma once
#include "../Core.h"
#include <string>
#include <functional>

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
		KeyChar,

		MousePressed,
		MouseReleased,
		MouseMove,
		MouseScroll
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

		virtual String ToString() const { return GetDisplayName(); }
		inline bool IsHandled() const { return m_Handled; }

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
