#include <CyEngine.h>
#include "CyEngine/Components/CameraComponent.h"
#include "CyEngine/Components/LightComponent.h"
#include "CyEngine/Components/MeshComponent.h"
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
		m_Scene = new World();
		m_Scene->SetIsEditorWorld();
		m_Scene->Start();

		// Create starting camera
		SceneObject* cam = m_Scene->CreateSceneObject<SceneObject>(Vector3(0, 0.5f, 4), Quat::Identity);
		cam->Name = "Main Camera";
		m_Camera = cam->CreateAndAddComponent<CameraComponent>();
		m_Camera->InitPerspectiveCamera({ 45.0f, 1280, 720, 0.1f, 150.0f });

		// Create default cube
		SceneObject* cube = m_Scene->CreateSceneObject<SceneObject>(Vector3::Zero, Quat::Identity, Vector3::One);
		cube->Name = "Cube";
		MeshComponent* cubeMesh = cube->CreateAndAddComponent<MeshComponent>();
		cubeMesh->SetMeshType(MeshComponentType::Cube);

		// Create light
		SceneObject* mainLight = m_Scene->CreateSceneObject<SceneObject>(Vector3(5, 5, 5), Quat::FromEuler(-30.0f, 45.0f, 0.0f));
		mainLight->Name = "Main Light";
		LightComponent* lightComp = mainLight->CreateAndAddComponent<LightComponent>();

		Array<int> arr;
		arr.Add(1);
		CopyTest(arr);
	}

	void CopyTest(Array<int> arr)
	{
		for (int i = 0; i < arr.Count(); i++)
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
	World* m_Scene;
	CameraComponent* m_Camera;
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
