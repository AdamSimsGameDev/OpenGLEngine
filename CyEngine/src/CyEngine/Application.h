#pragma once
#include "Core.h"
#include "Window.h"
#include "Layers/Layer.h"
#include "Layers/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include <CyEngine/Renderer/Shader.h>
#include <CyEngine/Renderer/Buffer.h>
#include <CyEngine/Renderer/VertexArray.h>

namespace Cy
{
	class EditorLayer;

	class CY_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();

		void OnEvent(Event& e);

		template<typename LayerType>
		void PushLayer() { PushLayer(new LayerType()); }
		void PushLayer(Layer* layer);

		template<typename LayerType>
		void PushOverlay() { PushOverlay(new LayerType()); }
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(class WindowCloseEvent& e);

		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		EditorLayer* m_EditorLayer;
		float m_LastFrameTime;
		bool m_Running = true;

	private:
		static Application* s_Instance;
	};

	// Should be defined by projects.
	Application* CreateApplication();
}
