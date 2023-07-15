#include "cypch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
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
		m_EditorLayer = new EditorLayer();
		PushOverlay(m_EditorLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[] = {
			-0.5f,	-0.5f,	 0.5f,
			 0.5f,	-0.5f,	 0.5f,
			-0.5f,	 0.5f,	 0.5f,
			 0.5f,	 0.5f,	 0.5f,
			-0.5f,	-0.5f,	-0.5f,
			 0.5f,	-0.5f,	-0.5f,
			-0.5f,	 0.5f,	-0.5f,
			 0.5f,	 0.5f,	-0.5f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = 
		{
			{ ShaderDataType::Float3, "a_Position" }
		};

		m_VertexBuffer->SetLayout(layout);

		uint32_t indices[] = 
		{ 
			//Top
			2, 6, 7,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			0, 1, 5,

			//Left
			0, 2, 6,
			0, 4, 6,

			//Right
			1, 3, 7,
			1, 5, 7,

			//Front
			0, 2, 3,
			0, 1, 3,

			//Back
			4, 6, 7,
			4, 5, 7
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader.reset(Shader::CreateFromFiles("resources/Shader.vert", "resources/Shader.frag"));

		m_Camera.reset(new PerspectiveCamera(45.0f, 1280, 720, 0.1f, 150.0f));
		//m_Camera.reset(new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f));
		m_Camera->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
		m_Camera->SetRotation(Quat::Identity);
	}

	Application::~Application()
	{
	}

	void rotateAround(Vector3& pos, Quat& rot, const Vector3& point, float rad, const Vector3& axis)
	{
		// create the rotation matrix
		Matrix4x4 rot_mat = Matrix4x4::Rotate(Matrix4x4(1.f), rad, axis);
		// get the rotation quat
		Quat act_rot = Matrix4x4::QuatCast(rot_mat);
		// get the position relative to the point
		Vector3 pos_rel = pos - point;
		// rotate both the relative position and rot
		rot = rot * Quat::Inverse(act_rot);
		pos = (pos_rel * act_rot) + point;
	}

	void Application::Run()
	{
		uint32_t frame = 0;
		while (m_Running)
		{
			Input::Update();

			Vector3 pos = m_Camera->GetPosition();
			Quat rot = m_Camera->GetRotation();
			rotateAround(pos, rot, Vector3::Zero, DEG_TO_RAD(0.1f), Vector3::Up);

			m_Camera->SetPosition(pos);
			m_Camera->SetRotation(rot);

			CY_CORE_LOG("Pos: {0}, Rot: {1}", pos.ToString(), rot.ToString());

			m_EditorLayer->GetFrameBuffer()->Bind();

			RenderCommand::SetClearColour({0.2f, 0.2f, 0.2f, 1.0f});
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Matrix4x4 matrix = m_Camera->GetProjectionViewMatrix();

			m_Shader->UploadUniformMat4("u_ViewProjection", matrix);
			Renderer::Submit(m_VertexArray);

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