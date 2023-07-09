#include "cypch.h"
#include "CyEngine/Application.h"
#include "CyEngine/Events/MouseEvent.h"
#include "CyEngine/Events/KeyEvent.h"
#include "ImGuiLayer.h"
#include "Platform/OpenGL/ImGuiRenderer.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.cpp>

namespace Cy
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		io.KeyMods |= ImGuiModFlags_Ctrl;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		// Bind mouse event dispatchers.
		dispatcher.Dispatch<MousePressedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMousePressEvent));
		dispatcher.Dispatch<MouseReleasedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseReleaseEvent));
		dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseMoveEvent));
	
		// Bind key event dispatchers.
		dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyPressEvent));
		dispatcher.Dispatch<KeyReleaseEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyReleaseEvent));
		dispatcher.Dispatch<KeyRepeatEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyRepeatEvent));
		dispatcher.Dispatch<KeyCharEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyCharEvent));
	}

	bool ImGuiLayer::OnMousePressEvent(MousePressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetButton(), true);
		return true;
	}

	bool ImGuiLayer::OnMouseReleaseEvent(MouseReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetButton(), false);
		return false;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetOffsetX(), e.GetOffsetY());
		return false;
	}

	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnKeyPressEvent(KeyPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode()), true);
		return false;
	}

	bool ImGuiLayer::OnKeyReleaseEvent(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode()), false);
		return false;
	}

	bool ImGuiLayer::OnKeyRepeatEvent(KeyRepeatEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode()), true);
		return false;
	}

	bool ImGuiLayer::OnKeyCharEvent(KeyCharEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());
		return false;
	}
}
