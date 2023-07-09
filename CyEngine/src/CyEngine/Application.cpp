#include "cypch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Input.h"
#include "Log.h"
#include "KeyCode.h"
#include <glad/glad.h>

namespace Cy
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			Input::Update();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			if (Input::IsKeyPressed(CY_KEY_SPACE))
			{
				CY_CORE_TRACE("Space Pressed");
			}
			if (Input::IsKeyDown(CY_KEY_SPACE))
			{
				CY_CORE_TRACE("Space Down");
			}
			if (Input::IsKeyReleased(CY_KEY_SPACE))
			{
				CY_CORE_TRACE("Space Released");
			}			
			
			if (Input::IsMouseButtonPressed(CY_MOUSE_BUTTON_LEFT))
			{
				CY_CORE_TRACE("LMB Pressed");
			}
			if (Input::IsMouseButtonDown(CY_MOUSE_BUTTON_LEFT))
			{
				CY_CORE_TRACE("LMB Down");
			}
			if (Input::IsMouseButtonReleased(CY_MOUSE_BUTTON_LEFT))
			{
				CY_CORE_TRACE("LMB Released");
			}


			m_Window->OnUpdate();
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

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}