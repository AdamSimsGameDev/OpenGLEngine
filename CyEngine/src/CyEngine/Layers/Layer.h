#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Events/Event.h"

namespace Cy
{
	class CY_API Layer
	{
	public:
		Layer(const std::string& name = "layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}