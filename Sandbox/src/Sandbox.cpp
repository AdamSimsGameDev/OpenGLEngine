#include <CyEngine.h>
#include "CyEngine/Objects/CameraObject.h"
#include "CyEngine/Objects/CubeObject.h"

using namespace Cy;

class MainLayer : public Layer
{
public:
	MainLayer() : Layer("Main Layer") 
	{ 
		m_Scene = nullptr;
		m_Camera = nullptr;
	}

	virtual void OnAttach() override
	{
		m_Scene = new Scene();
		m_Camera = m_Scene->CreateSceneObject<CameraObject>(Vector3(0, 0, 2), Quat::Identity);
		m_Camera->InitPerspectiveCamera({ 45.0f, 1280, 720, 0.1f, 150.0f });
		m_Scene->CreateSceneObject<CubeObject>(Vector3::Zero, Quat::Identity);
	}

	virtual void OnUpdate(float deltaTime) override
	{
		// tick the scene.
		m_Scene->Tick(deltaTime);

		Renderer::BeginScene(m_Scene);

		Renderer::EndScene();
	}

private:
	Scene* m_Scene;
	CameraObject* m_Camera;
};

class Sandbox : public Application
{
public:
	Sandbox()
	{
		PushLayer<MainLayer>();
	}
};

Cy::Application* Cy::CreateApplication()
{
	return new Sandbox();
}
