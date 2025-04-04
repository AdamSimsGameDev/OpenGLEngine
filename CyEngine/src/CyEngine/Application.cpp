#include "cypch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "CyEngine/Layers/EditorLayer.h"
#include "Renderer/Renderer.h"
#include "CyEngine/AssetManager/AssetManager.h"
#include "CyEngine/Threads/AsyncLoadingThread.h"
#include "CyEngine/Threads/ThreadManager.h"

namespace Cy
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

		// Initialise threads
		ThreadManager::Get().CreateThread<AsyncLoadingThread>("AsyncLoading");

		// Fetch assets
		AssetManager::Get();

		// Push default layers.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		m_EditorLayer = new EditorLayer();
		PushOverlay(m_EditorLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Input::Update();

			float time = m_Window->GetTime();
			const float deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Bind the frame buffer, to capture visuals for the editor layer.
			m_EditorLayer->GetFrameBuffer()->Bind();

			// Update each layer on the stack
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			// Unbind the frame buffer, since we finished rendering the frame in OnUpdate
			m_EditorLayer->GetFrameBuffer()->Unbind();

			// Handle ImGui for each of the layers.
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// Update the window itself.
			m_Window->OnUpdate();
		}

		if (!m_Running)
		{
			ThreadManager::StopAllThreads();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::ThreadTest(String inStr)
	{
		int c = 0;
		while (true)
		{
			if (c % 1000 == 1)
			{
				CY_LOG("Ran on thread, {0}", *inStr);
			}
			c++;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}