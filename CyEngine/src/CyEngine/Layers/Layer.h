#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Events/Event.h"

namespace Cy
{
	class CY_API Layer
	{
	public:
		Layer(const String& name = "layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const String& GetName() const { return m_DebugName; }
	protected:
		String m_DebugName;
	};
}