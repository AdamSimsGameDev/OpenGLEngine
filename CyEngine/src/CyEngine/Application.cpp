#include "cypch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "CyEngine/Layers/EditorLayer.h"

#include "Renderer/Renderer.h"

namespace Cy
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

		// Push default layers.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		m_EditorLayer = new EditorLayer();
		PushOverlay(m_EditorLayer);

		m_Shader.reset(Shader::CreateFromFiles("resources/Shader.vert", "resources/Shader.frag"));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		OnStart();

		uint32_t frame = 0;
		while (m_Running)
		{
			OnRunBegin();

			Input::Update();

			m_EditorLayer->GetFrameBuffer()->Bind();

			Renderer::BeginScene(m_Scenes[0], m_Shader.get());

			Renderer::EndScene();

			m_EditorLayer->GetFrameBuffer()->Unbind();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			frame++;

			OnRunEnd();
		}
	}

	void Application::OnRunBegin()
	{
		for (auto scene : m_Scenes)
		{
			scene->Tick();
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

	void Application::AddScene(Scene* scene)
	{
		m_Scenes.push_back(scene);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}