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
	class Scene;

	class CY_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();

		virtual void OnStart() {}
		virtual void OnRunBegin();
		virtual void OnRunEnd() {}

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void AddScene(Scene* scene);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(class WindowCloseEvent& e);

		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		EditorLayer* m_EditorLayer;
		bool m_Running = true;

		std::shared_ptr<Shader> m_Shader;

		std::vector<Scene*> m_Scenes;

	private:
		static Application* s_Instance;
	};

	// Should be defined by projects.
	Application* CreateApplication();
}
