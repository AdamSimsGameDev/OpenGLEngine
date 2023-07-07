#pragma once
#include "Event.h"

namespace Cy
{
	class CY_API GameTickEvent : public Event
	{
	public:
		EVENT_TYPE(GameTick);
	};

	class CY_API GameUpdateEvent : public Event
	{
	public:
		EVENT_TYPE(GameUpdate);
	};

	class CY_API GameRenderEvent : public Event
	{
	public:
		EVENT_TYPE(GameRender);
	};
}