#include "cypch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Input.h"
#include "Log.h"
#include "KeyCode.h"
#include "CyEngine/Layers/EditorLayer.h"

#include "CyEngine/Renderer/OrthographicCamera.h"
#include "CyEngine/Renderer/PerspectiveCamera.h"
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
		// PushOverlay(new EditorLayer());

		m_VertexArray.reset(VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = 
		{
			{ ShaderDataType::Float3, "a_Position" }
		};

		m_VertexBuffer->SetLayout(layout);

		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader.reset(Shader::CreateFromFiles("resources/Shader.vert", "resources/Shader.frag"));

		m_Camera.reset(new PerspectiveCamera(45.0f, 1280, 720, 0.1f, 150.0f));
		//m_Camera.reset(new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f));
		m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
		m_Camera->SetRotation(glm::quat(1, 0, 0, 0));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		uint32_t frame = 0;
		while (m_Running)
		{
			Input::Update();

			float sin = sinf(frame / 120.0f);
			CY_CORE_LOG("{0}", sin);
			m_Camera->SetPosition(glm::vec3(sin, 0.0f, 2.0f));

			RenderCommand::SetClearColour({0.2f, 0.2f, 0.2f, 1.0f});
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			glm::mat4 matrix = m_Camera->GetProjectionViewMatrix();

			m_Shader->UploadUniformMat4("u_ViewProjection", matrix);
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			frame++;
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