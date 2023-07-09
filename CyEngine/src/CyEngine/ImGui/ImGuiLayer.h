#pragma once

#include "CyEngine/Layers/Layer.h"

namespace Cy
{
	class CY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnMousePressEvent(class MousePressedEvent& e);
		bool OnMouseReleaseEvent(class MouseReleasedEvent& e);
		bool OnMouseScrollEvent(class MouseScrollEvent& e);
		bool OnMouseMoveEvent(class MouseMoveEvent& e);

		bool OnKeyPressEvent(class KeyPressEvent& e);
		bool OnKeyReleaseEvent(class KeyReleaseEvent& e);
		bool OnKeyRepeatEvent(class KeyRepeatEvent& e);
		bool OnKeyCharEvent(class KeyCharEvent& e);

	private:
		float m_Time = 0.0f;
	};
}

