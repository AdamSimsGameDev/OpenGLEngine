#include <CyEngine.h>
#include "CyEngine/Objects/CameraObject.h"
#include "CyEngine/Objects/CubeObject.h"
#include <CyEngine/Objects/PlaneObject.h>
#include <CyEngine/Serialization/Serialization.h>

using namespace Cy;

class MainLayer : public Layer
{
public:
	MainLayer() : Layer("Main Layer") 
	{ 
		m_Scene = nullptr;
		m_Camera = nullptr;
	}
	~MainLayer()
	{
		delete m_Scene;
	}

	virtual void OnAttach() override
	{
		m_Scene = new Scene();
		m_Scene->Start();
		m_Camera = m_Scene->CreateSceneObject<CameraObject>(Vector3(0, 0.5f, 4), Quat::Identity);
		m_Camera->InitPerspectiveCamera({ 45.0f, 1280, 720, 0.1f, 150.0f });
		m_Scene->CreateSceneObject<CubeObject>(Vector3::Zero, Quat::Identity, Vector3::One);
	
		Array<int> arr;
		arr.Add(1);
		CopyTest(arr);
	}

	void CopyTest(Array<int> arr)
	{
		for (size_t i = 0; i < arr.Count(); i++)
			CY_LOG("{0}", arr[i]);
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
