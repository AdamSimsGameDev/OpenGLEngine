#pragma once
#include "Core.h"
#include "Window.h"
#include "Layers/Layer.h"
#include "Layers/LayerStack.h"

namespace Cy
{
	class CY_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(class WindowCloseEvent& e);

		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// Should be defined by projects.
	Application* CreateApplication();
}
